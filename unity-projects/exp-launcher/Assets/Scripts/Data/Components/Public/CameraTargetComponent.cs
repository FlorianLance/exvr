
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

    public struct TargetSettings {
        public bool sphericalInterpolation;
        public bool useTime;
        public bool teleport;
        public bool neutral;
        public bool pitch;
        public bool yaw;
        public bool roll;
        public float duration;
        public Vector3 posTarget;
        public Vector3 eulerTarget;
        public Quaternion rotTarget;
        public Transform trTarget;        
    }

    public class CameraTargetComponent : ExComponent{

        // curve
        public AnimationCurve speedCurve = null;

        // state
        private bool continueMoving = false;
        private bool movementStarted = false;

        private float movementFactor = 0f;
        private bool doLoop = false;

        public Vector3 offset = Vector3.zero;

        // trajectories
        private Queue<Trajectory> savedTrajectories = new Queue<Trajectory>();        

        public void set_factor(float factor) {
            movementFactor = Mathf.Clamp01(factor);            
        }

        protected override bool initialize() {
            add_slot("set factor", (factor) => {
                set_factor(Mathf.Clamp01((float)factor));
            });
            return true;
        }

        protected override void pre_start_routine() {
            movementStarted = false;
            speedCurve      = currentC.get_curve("speed_curve");
            movementFactor  = 0f;
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

            TargetSettings settings = new TargetSettings();
            settings.duration = currentC.get<float>("duration");
            settings.pitch = currentC.get<bool>("pitch");
            settings.yaw = currentC.get<bool>("yaw");
            settings.roll = currentC.get<bool>("roll");
            settings.sphericalInterpolation = currentC.get<bool>("spherical_linear_interpolation");
            settings.useTime = currentC.get<bool>("use_time");
            settings.neutral = currentC.get<bool>("use_neutral");
            settings.teleport = currentC.get<bool>("teleport");

            string targetComponent = currentC.get<string>("target_component");
            if (targetComponent.Length == 0) { // no component traget to follow, move to defined position/rotation
                if (currentC.get<bool>("absolute")) {
                    settings.posTarget = currentC.get_vector3("target_pos");
                    settings.eulerTarget = currentC.get_vector3("target_rot");
                } else {

                    var posOffset = currentC.get_vector3("target_pos");
                    var rotOffset = currentC.get_vector3("target_rot");

                    settings.posTarget =
                        CameraUtility.eye_camera_position() +
                        CameraUtility.eye_camera_forward() * posOffset.z +
                        CameraUtility.eye_camera_up() * posOffset.y +
                        CameraUtility.eye_camera_right() * posOffset.x;
                    settings.eulerTarget =
                        (CameraUtility.calibration_rotation() *
                        Quaternion.AngleAxis(rotOffset.x, CameraUtility.eye_camera_right()) *
                        Quaternion.AngleAxis(rotOffset.y, CameraUtility.eye_camera_up()) *
                        Quaternion.AngleAxis(rotOffset.z, CameraUtility.eye_camera_forward())).eulerAngles;
                }
                settings.trTarget = null;
            } else {
                var go = components().get_from_name(targetComponent);
                if (go == null) {
                    log_error(string.Format("Component not found: {0}", targetComponent));
                    return;
                }
                settings.trTarget = go.transform;
            }


            if (currentC.get<bool>("move_to_target")) {
                ExVR.Coroutines().start(move_to_target(settings));
            } else if (currentC.get<bool>("move_back")) {

                // use the last trajectory to move back
                if (savedTrajectories.Count == 0) {
                    log_error("No previous trajectories to follow in the queue.");
                    return;
                }
                ExVR.Coroutines().start(move_back(settings));
            }
        }

        IEnumerator move_to_target(TargetSettings s) {

            Trajectory trajectory = new Trajectory();

            if (s.useTime) {
                doLoop = s.duration > 0f;
            } else {
                doLoop = movementFactor < 1f;
            }

            float totalPercent = 0f;
            float totalFactor = 0f;
            float previousFactor = 0f;

            float value = 0f;
            Vector3 pos = Vector3.zero;
            Quaternion rot = Quaternion.identity;

            while (doLoop) {

                if (!continueMoving) {
                    break;
                }

                // update current value
                if (s.useTime) {
                    float percent = Time.deltaTime / s.duration;
                    totalPercent += percent;

                    if (totalPercent >= 1f) {
                        doLoop = false;
                        value = 1f;
                    } else {
                        value = percent / (1f - speedCurve.Evaluate(totalPercent));
                    }
                } else {

                    float deltaFactor = Mathf.Clamp01(speedCurve.Evaluate(movementFactor) - previousFactor);
                    totalFactor += deltaFactor;
                    previousFactor = movementFactor;

                    if (movementFactor >= 1f) {
                        doLoop = false;
                        value = 1f;
                    } else {
                        value = deltaFactor / (1f - speedCurve.Evaluate(totalFactor));
                    }  
                }

                if (s.teleport) {
                    value = 1f;
                }

                // get current                
                var cPos = s.neutral ? CameraUtility.calibration_position() : CameraUtility.eye_camera_position();
                var cRos = s.neutral ? CameraUtility.calibration_rotation() : CameraUtility.eye_camera_rotation();

                //if (s.neutral) {
                //    cPos +=
                //        CameraUtility.calibration_forward() * offset.z +
                //        CameraUtility.calibration_up()      * offset.y +
                //        CameraUtility.calibration_right()   * offset.x;
                //}

                // compute current target
                if (s.trTarget == null) { // use pos and rot as target

                    pos = Interpolate.vector(cPos, s.posTarget, value, s.sphericalInterpolation);
                    //Debug.Log("p_target " + Converter.to_string(s.posTarget) + " pos: " + Converter.to_string(pos) + " v " + (CameraUtility.calibration_up() * offset.y));

                    // remove inused axies from rotation
                    if (!s.pitch || !s.yaw || !s.roll) {

                        var cEuler = cRos.eulerAngles;
                        rot = Interpolate.rotation(cRos,
                            Quaternion.Euler(new Vector3(
                                s.pitch ? s.eulerTarget.x : cEuler.x, 
                                s.yaw   ? s.eulerTarget.y : cEuler.y, 
                                s.roll  ? s.eulerTarget.z : cEuler.z)),
                            value, s.sphericalInterpolation);

                    } else {
                        rot = Interpolate.rotation(cRos, s.rotTarget, value, s.sphericalInterpolation);
                    }
                        
                } else { // using transform as target

                    pos = Interpolate.vector(cPos, s.trTarget.position, value, s.sphericalInterpolation);
                    //Debug.Log("tr_target " + Converter.to_string(s.trTarget.position) + " pos: " + Converter.to_string(pos) + " v " + (CameraUtility.calibration_up() * offset.y));

                    // remove inused axies from rotation
                    if (!s.pitch || !s.yaw || !s.roll) {
                        var trEuler = s.trTarget.eulerAngles;
                        var cEuler = cRos.eulerAngles;
                        rot = Interpolate.rotation(cRos, 
                            Quaternion.Euler(new Vector3(
                                s.pitch ? trEuler.x : cEuler.x, 
                                s.yaw   ? trEuler.y : cEuler.y, 
                                s.roll  ? trEuler.z : cEuler.z)), 
                            value, s.sphericalInterpolation);
                    } else {
                        rot = Interpolate.rotation(cRos, s.trTarget.rotation, value, s.sphericalInterpolation);
                    }
                }

                // update camera
                if (s.neutral) {
                    //var f =
                    //    pos +
                    //    CameraUtility.calibration_forward() * offset.z +
                    //    CameraUtility.calibration_up()      * offset.y +
                    //    CameraUtility.calibration_right()   * offset.x;

                    CameraUtility.set_calibration_transform(pos, rot);

                } else {
                    CameraUtility.set_eye_camera_transform(pos, rot);
                }

                // save point to trajectory
                trajectory.add_trajectory_point(pos, rot);
                yield return new WaitForEndOfFrame();
            }

            savedTrajectories.Enqueue(trajectory);
        }
  
        IEnumerator move_back(TargetSettings s) {

            Trajectory previousTrajectory = savedTrajectories.Dequeue();

            if (s.useTime) {
                doLoop = s.duration > 0f;
            } else {
                doLoop = movementFactor < 1f;
            }

            float totalPercent = 0f;
            float totalFactor = 0f;
            float previousFactor = 0f;

            while (doLoop) {

                if (!continueMoving) {
                    break;
                }

                //// update current value
                //if (s.useTime) {
                //    float percent = Time.deltaTime / s.duration;
                //    totalPercent += percent;

                //    if (totalPercent >= 1f) {
                //        doLoop = false;
                //    }
                //} else {

                //    float deltaFactor = Mathf.Clamp01(speedCurve.Evaluate(movementFactor) - previousFactor);
                //    totalFactor += deltaFactor;
                //    previousFactor = movementFactor;

                //    if (movementFactor >= 1f) {
                //        doLoop = false;
                //    } 
                //}


                //float percent;
                //if (useTime) {
                //    doLoop = journey < duration;
                //    journey += Time.deltaTime;
                //    percent = Mathf.Clamp01(journey / duration);
                //} else {
                //    doLoop = movementFactor < 1f;
                //    percent = movementFactor;
                //}

                //float speedT = speedCurve.Evaluate(percent);
                //var pos = previousTrajectory.get_position(1f-speedT);
                //var rot = previousTrajectory.get_rotation(1f-speedT);
                //if (s.neutral) {
                //    CameraUtility.set_calibration_transform(pos + movementOffset, rot);
                //} else {
                //    CameraUtility.set_eye_camera_transform(pos + movementOffset, rot);
                //}

                yield return null;
            }            
        }
    }
}


//IEnumerator move_to_target(bool useTime, bool neutral, bool sphericalInterpolation, float duration, List<Vector3> targetPositions, List<Quaternion> targetRotations) {

//    Trajectory trajectory = new Trajectory();

//    int size = targetPositions.Count;

//    float journey = 0f;
//    if (useTime) {
//        doLoop = journey < duration;
//    } else {
//        doLoop = movementFactor < 1f;
//    }

//    while (doLoop) {

//        if (!continueMoving) {
//            break;
//        }

//        float percent;
//        if (useTime) {
//            doLoop = journey < duration;
//            journey += Time.deltaTime;
//            percent = Mathf.Clamp01(journey / duration);
//        } else {
//            doLoop = movementFactor < 1f;
//            percent = movementFactor;
//        }

//        float speedT    = speedCurve.Evaluate(percent);
//        float factor    = speedT * size;
//        int integerPart = Mathf.FloorToInt(factor);
//        float floatPart = speedT - Mathf.Floor(factor);

//        Vector3 pos;
//        Quaternion rot;
//        if (integerPart < size - 1) {
//            pos = Interpolate.vector(targetPositions[integerPart], targetPositions[integerPart + 1], floatPart, sphericalInterpolation);
//            rot = Interpolate.rotation(targetRotations[integerPart], targetRotations[integerPart + 1], floatPart, sphericalInterpolation);
//        } else {
//            break;
//        }

//        if (neutral) {
//            CameraUtility.set_calibration_transform(pos + movementOffset, rot);
//        } else {
//            CameraUtility.set_eye_camera_transform(pos + movementOffset, rot);
//        }

//        // save point to trajectory
//        trajectory.add_trajectory_point(pos, rot);

//        yield return null;
//    }

//    savedTrajectories.Enqueue(trajectory);
//}
