/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;
using UnityEngine.UI;

namespace Ex{

    public class ImageViewerComponent : CanvasWorldSpaceComponent{

        private GameObject m_imageGO = null;

        private Texture2D m_currentImage = null;
        private Texture2D m_generatedInputImage = null;

        private int m_currentImageWidth = 0;
        private int m_currentImageHeight = 0;

        protected override bool initialize() {

            // init slots
            add_slot("set image", (imageContainer) => {
                load_image_from_container((ImageContainer)imageContainer);
            });

            // init gameObjects
            m_imageGO = ExVR.GlobalResources().instantiate_prebab("Components/ImageRect", transform);

            // init default 
            set_image(ExVR.Resources().get_image_file_data("default_texture").texture);

            return m_imageGO != null;
        }

        protected override void clean() {
            if(m_generatedInputImage != null) {
                Destroy(m_generatedInputImage);
                m_generatedInputImage = null;
            }
        }

        protected override void start_routine() {
            load_image_from_resource(currentC.get_resource_alias("image"));
            resize_image();
        }

        protected override void set_visibility(bool visibility) {
            m_imageGO.SetActive(visibility);
        }

        protected override void update_parameter_from_gui(XML.Arg arg) {
            if(arg.Name == "image") {
                load_image_from_resource(currentC.get_resource_alias("image"));
            }
            resize_image();
        }

        // use_eye_camera
        protected override void pre_update() {
            resize_image();
        }

        public void resize_image() {

            m_imageGO.transform.position = Vector3.zero;
            m_imageGO.transform.rotation = Quaternion.identity;

            var rTr = m_imageGO.GetComponent<RectTransform>();
            rTr.pivot = new Vector2(0.5f, 0.5f);

            if (currentC.get<bool>("use_eye_camera")) {

                // move to head
                Transform camTr = ExVR.Display().cameras().get_eye_camera_transform();
                m_imageGO.transform.position = camTr.position + camTr.forward * currentC.get<float>("distance");
                m_imageGO.transform.rotation = camTr.rotation;
                m_imageGO.transform.eulerAngles += currentC.get_vector3("rotation");                
                rTr.pivot = currentC.get_vector2("pivot");

            } else {
                rTr.localPosition = currentC.get_vector3("position");
                rTr.localEulerAngles = currentC.get_vector3("rotation");                
            }

            rTr.sizeDelta = ((currentC.get<bool>("use_original_size")) ?
                        new Vector2(m_currentImageWidth, m_currentImageHeight) :
                        new Vector2(currentC.get<int>("width"), currentC.get<int>("height"))
            );

            var sf = currentC.get<float>("scale_factor") * 0.01f;
            rTr.localScale = new Vector3(
                sf, sf, sf
            );
        }

        public void load_image_from_resource(string imageAlias) {

            if (imageAlias.Length != 0) {
                set_image(ExVR.Resources().get_image_file_data(imageAlias).texture);
            }
        }

        public void load_image_from_container(ImageContainer imageContainer) {
            if (imageContainer.texture != null) {
                set_image(imageContainer.texture);
            } else {
                m_generatedInputImage = imageContainer.update_texture2D(m_generatedInputImage);
                set_image(m_generatedInputImage);
            }
        }

        public void set_image(Texture2D texture) {

            m_currentImage = texture;

            m_currentImageWidth     = m_currentImage.width;
            m_currentImageHeight    = m_currentImage.height;
            m_imageGO.GetComponent<UnityEngine.UI.Image>().sprite = Sprite.Create(
                m_currentImage, 
                new Rect(0.0f, 0.0f, m_currentImageWidth, m_currentImageHeight), 
                new Vector2(0f, 0f), 
                100.0f, 
                0, 
                SpriteMeshType.FullRect
            );
        }
    }
}