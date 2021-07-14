
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections;
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex{

    public class CameraTargetComponent : ExComponent{

        // curve
        public AnimationCurve speedCurve = null;

        // state
        private bool continueMoving = false;
        private bool movementStarted = false;

        private float movementFactor = 0f;
        private Vector3 movementOffset = Vector3.zero;
        private bool doLoop = false;


        // trajectories
        private Queue<Trajectory> savedTrajectories = new Queue<Trajectory>();        

        protected override bool initialize() {
            add_slot("set factor", (factor) => {
                movementFactor = (float)factor;
            });
            add_slot("set offset", (offset) => {
                movementOffset = (Vector3)offset;
            });
            return true;
        }

        protected override void start_routine() {
            movementStarted = false;
            speedCurve      = currentC.get_curve("speed_curve");
            movementFactor = 0f;
            movementOffset = Vector3.zero;
        }

        protected override void stop_routine() {
            doLoop = false;
        }

        protected override void set_update_state(bool doUpdate) {
            continueMoving = doUpdate;
        }
        protected override void update() {
            if (is_updating() && !movementStarted) {
                apply_movement();
            }
        }

        private void apply_movement() {

            movementStarted = true;

            float duration = currentC.get<float>("duration");
            if (currentC.get<bool>("move_to_target")) {

                bool pitch = currentC.get<bool>("pitch");
                bool yaw = currentC.get<bool>("yaw");
                bool roll = currentC.get<bool>("roll");

                string targetComponent = currentC.get<string>("target_component");

                Vector3 targetEuler;
                Vector3 targetPosition;

                if (targetComponent.Length == 0) { // no component traget to follow, move to defined position/rotation

                    if (currentC.get<bool>("absolute")) {
                        targetPosition = currentC.get_vector3("target_pos");
                        targetEuler    = currentC.get_vector3("target_rot");
                    } else {
                        var positionOffset = currentC.get_vector3("target_pos");
                        targetPosition = 
                            CameraUtility.eye_camera_position() + 
                            CameraUtility.eye_camera_forward() * positionOffset.z +
                            CameraUtility.eye_camera_up()      * positionOffset.y +
                            CameraUtility.eye_camera_right()   * positionOffset.x;

                        var rotOffset = currentC.get_vector3("target_rot");
                        targetEuler =
                            (CameraUtility.start_neutral_camera_rotation() *
                            Quaternion.AngleAxis(rotOffset.x, CameraUtility.eye_camera_right()) *
                            Quaternion.AngleAxis(rotOffset.y, CameraUtility.eye_camera_up()) *
                            Quaternion.AngleAxis(rotOffset.z, CameraUtility.eye_camera_forward())).eulerAngles;
                    }
                } else {
                    var go = get(targetComponent);
                    if (go == null) {
                        log_error(string.Format("Component not found: {0}", targetComponent));
                        return;
                    }
                    targetPosition = go.transform.position;
                    targetEuler = go.transform.eulerAngles;
                }

                // remove inused axies from rotation
                var o = CameraUtility.start_neutral_camera_rotation().eulerAngles;
                var targetRotation = Quaternion.Euler(new Vector3(
                    pitch ? targetEuler.x : o.x,
                    yaw   ? targetEuler.y : o.y,
                    roll  ? targetEuler.z : o.z)
                );
                
                int nbInterpolations = currentC.get<int>("nb_inter_pos");

                if (nbInterpolations > 1) {

                    List<Vector3> positions = new List<Vector3>(nbInterpolations);
                    List<Quaternion> rotations = new List<Quaternion>(nbInterpolations);

                    // move
                    bool sphericalInterpolation = currentC.get<bool>("spherical_linear_interpolation");
                    var originPosition = CameraUtility.start_neutral_camera_position();// + movementOffset;
                    var originRotation = CameraUtility.start_neutral_camera_rotation();
                    for (int ii = 0; ii < nbInterpolations; ++ii) {
                        float factor = 1f * ii / (nbInterpolations - 1);
                        positions.Add(Interpolate.vector(originPosition, targetPosition, factor, sphericalInterpolation));
                        rotations.Add(Interpolate.rotation(originRotation, targetRotation, factor, sphericalInterpolation));
                    }

                    // start coroutine
                    ExVR.Coroutines().start(move_to_target(
                        currentC.get<bool>("use_time"),
                        currentC.get<bool>("use_neutral"),
                        sphericalInterpolation,
                        duration,
                        positions,
                        rotations
                    ));

                } else {

                    // start coroutine
                    ExVR.Coroutines().start(stay_to_target(
                        currentC.get<bool>("use_time"),
                        currentC.get<bool>("use_neutral"),
                        duration,
                        targetPosition,
                        targetRotation
                    ));
                } 

            } else if (currentC.get<bool>("move_back")) { // use the last trajectory to move back
                if (savedTrajectories.Count == 0) {
                    log_error("No previous trajectories to follow in the queue.");
                    return;
                }
                ExVR.Coroutines().start(move_back(
                    currentC.get<bool>("use_time"),
                    currentC.get<bool>("use_neutral"),
                    duration
                ));
            }
        }

        IEnumerator stay_to_target(bool useTime, bool neutral, float duration, Vector3 targetPosition, Quaternion targetRotation) {

            Trajectory trajectory = new Trajectory();
            
            float journey = 0f;
            if (useTime) {
                doLoop = journey < duration;
            } else {
                doLoop = movementFactor < 1f;
            }

            if(doLoop == false) {
                if (neutral) {
                    CameraUtility.set_start_experiment_neutral_transform(targetPosition + movementOffset, targetRotation);
                } else {
                    CameraUtility.set_eye_camera_transform(targetPosition + movementOffset, targetRotation);
                }
                // save point to trajectory
                trajectory.add_trajectory_point(targetPosition, targetRotation);
            }

            while (doLoop) {

                if (!continueMoving) {
                    break;
                }

                if (useTime) {
                    doLoop = journey < duration;
                    journey += Time.deltaTime;
                } else {
                    doLoop = movementFactor < 1f;
                }

                if (neutral) {
                    CameraUtility.set_start_experiment_neutral_transform(targetPosition + movementOffset, targetRotation);
                } else {
                    CameraUtility.set_eye_camera_transform(targetPosition + movementOffset, targetRotation);
                }

                // save point to trajectory
                trajectory.add_trajectory_point(targetPosition, targetRotation);

                yield return null;
            }

            savedTrajectories.Enqueue(trajectory);
        }

        IEnumerator move_to_target(bool useTime, bool neutral, bool sphericalInterpolation, float duration, List<Vector3> targetPositions, List<Quaternion> targetRotations) {

            Trajectory trajectory = new Trajectory();

            int size = targetPositions.Count;

            float journey = 0f;
            if (useTime) {
                doLoop = journey < duration;
            } else {
                doLoop = movementFactor < 1f;
            }

            while (doLoop) {

                if (!continueMoving) {
                    break;
                }

                float percent;
                if (useTime) {
                    doLoop = journey < duration;
                    journey += Time.deltaTime;
                    percent = Mathf.Clamp01(journey / duration);
                } else {
                    doLoop = movementFactor < 1f;
                    percent = movementFactor;
                }

                float speedT    = speedCurve.Evaluate(percent);
                float factor    = speedT * size;
                int integerPart = Mathf.FloorToInt(factor);
                float floatPart = speedT - Mathf.Floor(factor);

                Vector3 pos;
                Quaternion rot;
                if (integerPart < size - 1) {
                    pos = Interpolate.vector(targetPositions[integerPart], targetPositions[integerPart + 1], floatPart, sphericalInterpolation);
                    rot = Interpolate.rotation(targetRotations[integerPart], targetRotations[integerPart + 1], floatPart, sphericalInterpolation);
                } else {
                    break;
                }

                if (neutral) {
                    CameraUtility.set_start_experiment_neutral_transform(pos + movementOffset, rot);
                } else {
                    CameraUtility.set_eye_camera_transform(pos + movementOffset, rot);
                }

                // save point to trajectory
                trajectory.add_trajectory_point(pos, rot);

                yield return null;
            }

            savedTrajectories.Enqueue(trajectory);
        }

        IEnumerator move_back(bool useTime, bool neutral, float duration) {

            Trajectory previousTrajectory = savedTrajectories.Dequeue();

            float journey = 0f;
            if (useTime) {
                doLoop = journey < duration;
            } else {
                doLoop = movementFactor < 1f;
            }

            while (doLoop) {

                if (!continueMoving) {
                    break;
                }

                float percent;
                if (useTime) {
                    doLoop = journey < duration;
                    journey += Time.deltaTime;
                    percent = Mathf.Clamp01(journey / duration);
                } else {
                    doLoop = movementFactor < 1f;
                    percent = movementFactor;
                }
                float speedT = speedCurve.Evaluate(percent);

                var pos = previousTrajectory.get_position(1f-speedT);
                var rot = previousTrajectory.get_rotation(1f-speedT);
                if (neutral) {
                    CameraUtility.set_start_experiment_neutral_transform(pos + movementOffset, rot);
                } else {
                    CameraUtility.set_eye_camera_transform(pos + movementOffset, rot);
                }

                yield return null;
            }            
        }
    }
}