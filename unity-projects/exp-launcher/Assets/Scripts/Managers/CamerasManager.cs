/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{


    public class CamerasManager : MonoBehaviour {

        // camera rig
        public Transform cameraRig = null;
        // cameras
        public Camera bothEyesCamera = null;
        public Camera leftEyeCamera = null;
        public Camera rightEyeCamera = null;
        public Camera leftEyeStereoCamera = null;
        public Camera rightEyeStereoCamera = null;
        // transforms
        public Transform startExperimentNeutral = null;
        public Transform eyeCameraRelative = null;

        private Vector3 initStartExperimentNeutralPosition = Vector3.zero;
        private Quaternion initStartExperimentNeutralRotation = Quaternion.identity;

        public void reset() {

            //Valve.VR.OpenVR.System.ResetSeatedZeroPose();
            //Valve.VR.OpenVR.Compositor.SetTrackingSpace(Valve.VR.ETrackingUniverseOrigin.TrackingUniverseRawAndUncalibrated);
            //Valve.VR.ETrackingUniverseOrigin.TrackingUniverseSeated);

            // reset camera rig
            set_camera_rig_transform(Vector3.zero, Quaternion.identity);

            // store neutral eye camera direction
            startExperimentNeutral.localPosition = bothEyesCamera.transform.localPosition;

            Debug.LogError("ExVR.GuiSettings().useCameraXAxixAsNeutral " + ExVR.GuiSettings().useCameraXAxixAsNeutral);
            Debug.LogError("ExVR.GuiSettings().useCameraYAxixAsNeutral " + ExVR.GuiSettings().useCameraYAxixAsNeutral);
            Debug.LogError("ExVR.GuiSettings().useCameraZAxixAsNeutral " + ExVR.GuiSettings().useCameraZAxixAsNeutral);

            var angles = bothEyesCamera.transform.localEulerAngles;
            startExperimentNeutral.localEulerAngles = new Vector3(
                ExVR.GuiSettings().useCameraXAxixAsNeutral ? angles.x : 0f,
                ExVR.GuiSettings().useCameraYAxixAsNeutral ? angles.y : 0f,
                ExVR.GuiSettings().useCameraZAxixAsNeutral ? angles.z : 0f
            );
            Debug.LogError("angles " + angles);
            Debug.LogError("startExperimentNeutral.localEulerAngles " + startExperimentNeutral.localEulerAngles);

            initStartExperimentNeutralPosition = startExperimentNeutral.localPosition;
            initStartExperimentNeutralRotation = startExperimentNeutral.localRotation;

            update_eye_camera_relative();
        }

        // transform
        public Transform get_start_experiment_neutral_transform() {
            return startExperimentNeutral;
        }

        public Transform get_eye_camera_transform() {
            return bothEyesCamera.transform;
        }

        public Transform get_eye_camera_relative_transform() {
            return eyeCameraRelative;
        }


        public Camera get_eye_camera() {
            return bothEyesCamera;
        }

        public Transform get_camera_rig() {
            return cameraRig;
        }

        // move camera rig
        // # move  horizontally
        public void move_target_horizontally_by_modifying_camera_rig_transform(Transform target, float amount) {
            get_camera_rig().position += target.right.normalized * amount;
        }

        public void move_start_neutral_camera_horizontally_by_modifying_camera_rig_transform(float amount) {
            move_target_horizontally_by_modifying_camera_rig_transform(get_start_experiment_neutral_transform(), amount);
        }

        public void move_eye_camera_horizontally_by_modifying_camera_rig_transform(float amount) {
            move_target_horizontally_by_modifying_camera_rig_transform(get_eye_camera_transform(), amount);
        }

        // # move  vertically
        public void move_target_vertically_by_modifying_camera_rig_transform(Transform target, float amount) {
            get_camera_rig().position += target.up.normalized * amount;
        }

        public void move_start_neutral_camera_vertically_by_modifying_camera_rig_transform(float amount) {
            move_target_vertically_by_modifying_camera_rig_transform(get_eye_camera_transform(), amount);
        }

        public void move_eye_camera_vertically_by_modifying_camera_rig_transform(float amount) {
            move_target_vertically_by_modifying_camera_rig_transform(get_start_experiment_neutral_transform(), amount);
        }

        // # move  forward
        public void move_target_forward_by_modifying_camera_rig_transform(Transform target, float amount) {
            get_camera_rig().position += target.forward * amount;
        }

        public void move_start_neutral_camera_forward_by_modifying_camera_rig_transform(float amount) {
            move_target_forward_by_modifying_camera_rig_transform(get_start_experiment_neutral_transform(), amount);
        }

        public void move_eye_camera_forward_by_modifying_camera_rig_transform(float amount) {
            move_target_forward_by_modifying_camera_rig_transform(get_eye_camera_transform(), amount);
        }

        // # move backward
        private void move_target_backward_by_modifying_camera_rig_transform(Transform target, float amount) {
            get_camera_rig().position -= target.forward * amount;
        }

        public void move_start_neutral_camera_backward_by_modifying_camera_rig_transform(float amount) {
            move_target_backward_by_modifying_camera_rig_transform(get_start_experiment_neutral_transform(), amount);
        }

        public void move_eye_camera_backward_by_modifying_camera_rig_transform(float amount) {
            move_target_backward_by_modifying_camera_rig_transform(get_eye_camera_transform(), amount);
        }

        // # translate 

        public void translate_start_neutral_camera_referential_by_modifying_camera_rig_transform(Vector3 vector) {
            move_start_neutral_camera_forward_by_modifying_camera_rig_transform(vector.x);
            move_start_neutral_camera_vertically_by_modifying_camera_rig_transform(vector.y);
            move_start_neutral_camera_horizontally_by_modifying_camera_rig_transform(vector.z);
        }

        public void translate_eye_camera_referential_by_modifying_camera_rig_transform(Vector3 vector) {
            move_eye_camera_forward_by_modifying_camera_rig_transform(vector.x);
            move_eye_camera_vertically_by_modifying_camera_rig_transform(vector.y);
            move_eye_camera_horizontally_by_modifying_camera_rig_transform(vector.z);
        }

        // # rotate
        private void rotate_target_by_modifying_camera_rig_transform(Transform target, Quaternion rotation) {

            // !!!  use only with targets from camera rig hierarchy !!!
            var targetWorldPosition = target.position;
            var rig = get_camera_rig();
            rig.rotation = (target.rotation * rotation) * Quaternion.Inverse(target.localRotation);
            rig.position += targetWorldPosition - target.position;
        }

        public void rotate_start_neutral_camera_by_modifying_camera_rig_transform(Quaternion rotation) {
            rotate_target_by_modifying_camera_rig_transform(get_start_experiment_neutral_transform(), rotation);
        }

        public void rotate_eye_camera_by_modifying_camera_rig_transform(Quaternion rotation) {
            rotate_target_by_modifying_camera_rig_transform(get_eye_camera_transform(), rotation);
        }

        // # move
        public void apply_vector_to_camera_rig_position(Vector3 vector) {
            get_camera_rig().position += vector;
        }

        // # set 

        // ## position
        public void set_start_neutral_camera_position_by_modifying_camera_rig_transform(Vector3 worldPosition) {
            apply_vector_to_camera_rig_position(worldPosition - get_start_experiment_neutral_transform().position);
        }

        public void set_eye_camera_position_by_modifying_camera_rig_transform(Vector3 worldPosition) {
            apply_vector_to_camera_rig_position(worldPosition - get_eye_camera_transform().position);
        }

        // ## rotation
        private void set_target_rotation_by_modifying_camera_rig_transform(Transform target, Quaternion worldRotation) {

            // !!!  use only with targets from camera rig hierarchy !!!
            var targetWorldPosition = target.position;
            var rig = get_camera_rig();
            rig.rotation = worldRotation * Quaternion.Inverse(target.localRotation);
            rig.position += targetWorldPosition - target.position;
        }

        public void set_start_neutral_camera_rotation_by_modifying_camera_rig_transform(Quaternion worldRotation) {
            set_target_rotation_by_modifying_camera_rig_transform(get_start_experiment_neutral_transform(), worldRotation);
        }

        public void set_eye_camera_rotation_by_modifying_camera_rig_transform(Quaternion worldRotation) {
            set_target_rotation_by_modifying_camera_rig_transform(get_eye_camera_transform(), worldRotation);
        }

        // ## transform

        public void set_camera_rig_transform(Vector3 worldPosition, Quaternion worldRotation) {
            var rig = get_camera_rig();
            rig.rotation = worldRotation;
            rig.position = worldPosition;
        }

        public void set_start_experiment_neutral_transform_by_modifying_camera_rig_transform(Vector3 worldPosition, Quaternion worldRotation) {

            var target = get_start_experiment_neutral_transform();
            var rig = get_camera_rig();
            rig.rotation = worldRotation * Quaternion.Inverse(target.localRotation);
            rig.position += worldPosition - target.position;
        }


        public void set_eye_camera_transform_by_modifying_camera_rig_transform(Vector3 worldPosition, Quaternion worldRotation) {
            var target = get_eye_camera_transform();
            var rig = get_camera_rig();
            rig.rotation = worldRotation * Quaternion.Inverse(target.localRotation);
            rig.position += worldPosition - target.position;
        }

        // screen
        public bool mouse_on_screen() {
            var view = bothEyesCamera.ScreenToViewportPoint(UnityEngine.Input.mousePosition);
            return view.x < 0 || view.x > 1 || view.y < 0 || view.y > 1;
        }

        private void update_eye_camera_relative() {
            if (eyeCameraRelative != null) {
                var tr = get_eye_camera_transform();
                eyeCameraRelative.localPosition    = tr.localPosition - startExperimentNeutral.localPosition;
                eyeCameraRelative.localEulerAngles = tr.localEulerAngles - startExperimentNeutral.localEulerAngles;
            }
        }
        public void Update() {
            update_eye_camera_relative();
        }
    }
}