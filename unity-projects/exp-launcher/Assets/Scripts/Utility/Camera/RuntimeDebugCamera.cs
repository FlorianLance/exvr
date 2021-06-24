/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{

    public class RuntimeDebugCamera : MonoBehaviour {

        public float speedT = 0.5f;
        public float speedRH = 3f;
        public float speedRV = 3f;
        public float speedRR = 3f;
        private float yaw   = 0.0f;
        private float pitch = 0.0f;
        private float roll = 0.0f;
        public bool outside = true;

        Camera cameraC = null;
        private void Awake() {
            cameraC = GetComponent<Camera>();
        }

        public bool is_mouse_outside() {

            if (!cameraC.enabled) {
                return true;
            }

            var view = cameraC.ScreenToViewportPoint(UnityEngine.Input.mousePosition);
            return (view.x < 0 || view.x > 1 || view.y < 0 || view.y > 1);
        }

        private void Update() {

            if (outside = is_mouse_outside()) {
                return;
            }

            bool leftClick = UnityEngine.Input.GetMouseButton(0);
            bool rightClick = UnityEngine.Input.GetMouseButton(1);
            bool middleClick = UnityEngine.Input.GetMouseButton(2);
            float nx = UnityEngine.Input.GetAxis("Mouse X");
            float ny = UnityEngine.Input.GetAxis("Mouse Y");
            float scroll = UnityEngine.Input.GetAxis("Mouse ScrollWheel");

            if (scroll > 0f) {
                move_forward(speedT);
            } else if (scroll < 0f) {
                move_backward(speedT);
            }

            if (middleClick) {

                // check horizontal right click mouse drag movement
                if (nx != 0) {
                    horizontal_strafe(nx * speedT);
                }
                // check vertical right click mouse drag movement
                if (ny != 0) {
                    vertical_strafe(ny * speedT);
                }

            } else if (leftClick && rightClick) {
                transform.Rotate(0, 0, speedRR * nx);
            } else if (rightClick) {
                transform.Rotate(new Vector3(-ny * speedRV, nx * speedRH, 0));
            } else if (leftClick) {
                // ...
            }
        }

        protected void horizontal_strafe(float amount) {
            transform.position = transform.position + transform.right * amount;
        }

        protected void vertical_strafe(float amount) {
            transform.position = transform.position + transform.up * amount;
        }

        protected void move_forward(float amount) {
            transform.position += transform.forward * amount;
        }

        protected void move_backward(float amount) {
            transform.position -= transform.forward * amount;
        }

        public void hide() {
            cameraC.enabled = false;
            //GetComponent<UnityEngine.UI.Image>().enabled = false;
        }

        public void bottom_left() {
            cameraC.rect = new Rect(0, 0, 0.5f, 0.5f);
            cameraC.enabled = true;
            //GetComponent<UnityEngine.UI.Image>().enabled = true;
        }

        public void expand() {
            cameraC.rect = new Rect(0, 0, 1, 1);
            cameraC.enabled = true;
            //GetComponent<UnityEngine.UI.Image>().enabled = true;
        }
    }
}


