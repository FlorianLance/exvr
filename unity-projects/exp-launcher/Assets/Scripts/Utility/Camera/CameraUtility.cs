
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex {

    public class CameraUtility {        

        // camera rig
        // # get
        public static Vector3 camera_rig_position() {
            return ExVR.Display().cameras().get_camera_rig_transform().position;
        }
        public static Quaternion camera_rig_rotation() {
            return ExVR.Display().cameras().get_camera_rig_transform().rotation;
        }

        public static void translate_camera_rig(Vector3 vector) {
            ExVR.Display().cameras().apply_vector_to_camera_rig_position(vector);
        }
        
        public static void rotate_camera_rig_around(Vector3 pivot, Vector3 axis, float value) {
            ExVR.Display().cameras().get_camera_rig_transform().RotateAround(pivot, axis, value);
        }

        // calibration
        // # get
        public static Quaternion calibration_rotation() {
            return ExVR.Display().cameras().get_calibration_transform().rotation;
        }

        public static Vector3 calibration_position() {
            return ExVR.Display().cameras().get_calibration_transform().position;
        }

        public static Vector3 calibration_forward() {
            return ExVR.Display().cameras().get_calibration_transform().forward;
        }
        // # move
        public static void move_calibration_forward(float amount) {
            ExVR.Display().cameras().move_calibration_forward_by_modifying_camera_rig(amount);
        }
        public static void move_calibration_backward(float amount) {
            ExVR.Display().cameras().move_calibration_backward_by_modifying_camera_rig(amount);
        }
        public static void move_calibration_horizontally(float amount) {
            ExVR.Display().cameras().move_calibration_horizontally_by_modifying_camera_rig(amount);
        }
        public static void move_calibration_vertically(float amount) {
            ExVR.Display().cameras().move_calibration_vertically_by_modifying_camera_rig(amount);
        }
        public static void translate_calibration_referential(Vector3 vector) {
            ExVR.Display().cameras().translate_calibration_referential_by_modifying_camera_rig(vector);
        }
        // # rotate
        public static void rotate_calibration(Quaternion rotation) {
            ExVR.Display().cameras().rotate_calibration_by_modifying_camera_rig(rotation);
        }
        public static void rotate_calibration(Vector3 rotation) {
            rotate_calibration(rotation);
        }
        // # set
        // ## transform
        public static void set_calibration_transform(Vector3 worldPosition, Quaternion worldRotation) {
            ExVR.Display().cameras().set_calibration_transform_by_modifying_camera_rig(worldPosition, worldRotation);
        }
        public static void set_calibration_transform(Vector3 worldPosition, Vector3 worldRotation) {
            set_calibration_transform(worldPosition, Quaternion.Euler(worldRotation));
        }
        public static void set_calibration_from_target(Transform target, Vector3 positionOffset, Quaternion rotationOffset) {
            set_calibration_transform(
                target.position + (target.forward * positionOffset.z + target.up * positionOffset.y + target.right * positionOffset.x),
                target.rotation * rotationOffset
            );
        }

        // eye camera
        // # get
        public static Quaternion eye_camera_rotation() {            
            return ExVR.Display().cameras().get_eye_camera_transform().rotation;
        }

        public static Vector3 eye_camera_position() {
            return ExVR.Display().cameras().get_eye_camera_transform().position;
        }

        public static Vector3 eye_camera_forward() {
            return ExVR.Display().cameras().get_eye_camera_transform().forward;
        }

        public static Vector3 eye_camera_up() {
            return ExVR.Display().cameras().get_eye_camera_transform().up;
        }

        public static Vector3 eye_camera_right() {
            return ExVR.Display().cameras().get_eye_camera_transform().right;
        }

        // # move
        public static void move_eye_camera_forward(float amount) {
            ExVR.Display().cameras().move_eye_camera_forward_by_modifying_camera_rig(amount);
        }
        public static void move_eye_camera_backward(float amount) {
            ExVR.Display().cameras().move_eye_camera_backward_by_modifying_camera_rig(amount);
        }
        public static void move_eye_camera_horizontally(float amount) {
            ExVR.Display().cameras().move_eye_camera_horizontally_by_modifying_camera_rig(amount);
        }
        public static void move_eye_camera_vertically(float amount) {
            ExVR.Display().cameras().move_eye_camera_vertically_by_modifying_camera_rig(amount);
        }
        public static void translate_eye_camera_referential(Vector3 vector) {
            ExVR.Display().cameras().translate_eye_camera_referential_by_modifying_camera_rig(vector);
        }

        // # rotate
        public static void rotate_eye_camera(Quaternion rotation) {
            ExVR.Display().cameras().rotate_eye_camera_by_modifying_camera_rig(rotation);
        }
        public static void rotate_eye_camera(Vector3 rotation) {            
            rotate_eye_camera(Quaternion.Euler(rotation));
        }

        // # set
        // ## position
        public static void set_eye_camera_position(Vector3 worldPosition) {
            ExVR.Display().cameras().set_eye_camera_position_by_modifying_camera_rig(worldPosition);
        }

        // ## rotation
        public static void set_eye_camera_rotation(Quaternion worldRotation) {
            ExVR.Display().cameras().set_eye_camera_rotation_by_modifying_camera_rig(worldRotation);
        }
        public static void set_eye_camera_rotation(Vector3 worldRotation) {
            set_eye_camera_rotation(Quaternion.Euler(worldRotation));
        }
        // ## transform
        public static void set_eye_camera_transform(Vector3 worldPosition, Quaternion worldRotation) {
            // OK
            ExVR.Display().cameras().set_eye_camera_transform_by_modifying_camera_rig(worldPosition, worldRotation);
        }
        public static void set_eye_camera_transform(Vector3 worldPosition, Vector3 worldRotation) {
            // OK
            set_eye_camera_transform(worldPosition, Quaternion.Euler(worldRotation));
        }
        public static void set_eye_camera_from_target(Transform target, Vector3 positionOffset, Quaternion rotationOffset) {
            // ?
            set_eye_camera_transform(
                target.position + (target.forward * positionOffset.z + target.up * positionOffset.y + target.right * positionOffset.x),
                target.rotation * rotationOffset
            );
        }

        // # layer
        public static void apply_eye_camera_only_layer(GameObject go) {
            foreach (Transform tr in go.GetComponentsInChildren<Transform>(true)) {
                tr.gameObject.layer = Layers.EyeCameraOnly;
            }
        }

        // eye camera relative
        // # get
        public static Quaternion eye_camera_relative_rotation() {
            return ExVR.Display().cameras().get_eye_camera_relative_transform().localRotation;
        }

        public static Vector3 eye_camera_relative_position() {
            return ExVR.Display().cameras().get_eye_camera_relative_transform().localPosition;
        }

        // target
        public static void set_target_from_eye_camera(Transform target, Vector3 worldPosition, Quaternion worldRotation) {

            // TO TEST
            target.position = eye_camera_position() - (target.forward * worldPosition.z + target.up * worldPosition.y + target.right * worldPosition.x);
            target.rotation = eye_camera_rotation() * Quaternion.Inverse(worldRotation);
        }
    }
}