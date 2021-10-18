/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.IO;

// unity
using UnityEngine;

namespace Ex{

    public class ImageContainer{

        public int width;
        public int height;
        public Color32[] pixels = null;
        public Texture2D texture = null;

        public ImageContainer(WebCamTexture webcamTexture) {
            pixels = webcamTexture.GetPixels32();
            width = webcamTexture.width;
            height = webcamTexture.height;
        }

        public ImageContainer(Texture2D texture, bool copyData) {

            width = texture.width;
            height = texture.height;

            if (copyData) {
                pixels = texture.GetPixels32();
            } else {
                this.texture = texture;
            }
        }

        public Texture2D update_texture2D(Texture2D texture) {

            if (texture == null) {
                texture = new Texture2D(width, height);
                texture.filterMode = FilterMode.Trilinear;
                texture.wrapMode = TextureWrapMode.Clamp;
                texture.SetPixels32(pixels);
                texture.Apply();
            } else {
                if (texture.width != width || texture.height != height) {
                    texture.Resize(width, height);
                }
                texture.SetPixels32(pixels);
                texture.Apply();
            }
            return texture;
        }
    }

    public class ImageResource : ResourceFile{

        public byte[] bytes = null;
        public Texture2D texture = null;

        public ImageResource(int key, string alias, string path) : base(key, alias, path) {
            texture = new Texture2D(2, 2);//, TextureFormat.RGB24, false);

            // set textures parameters
            //texture.filterMode = FilterMode.Trilinear;
            texture.wrapMode = TextureWrapMode.Clamp;
            texture.filterMode = FilterMode.Point;
        }
        public override void read_data() {

            if (path.Length == 0) {
                bytes = null;
                return;
            }

            try {
                bytes = File.ReadAllBytes(path);
            } catch (System.Exception ex) {
                log_error(string.Format("Cannot read image file {0}, error: {1}", path, ex.Message));
                bytes = null;
            }
        }

        public override void initialize() {
            
            bool loaded = false;
            if (bytes != null) {
                if (bytes.Length > 0) {
                    loaded = texture.LoadImage(bytes);  //..this will auto-resize the texture dimensions.
                } else {
                    log_error(string.Format("Can't create texture from image file {0}. Replaced with default image instead.", path));
                }
            }

            if (!loaded) {
                texture.Resize(500, 500);
                Color[] colors = new Color[500 * 500];
                Color black = new Color(1, 0, 0, 1);
                for (int ii = 0; ii < colors.Length; ++ii) {
                    colors[ii] = black;
                }
                texture.SetPixels(colors);
                texture.Apply();
            }
        }


        public override void clean() {
            ExVR.Memory().delete_texture(texture);
        }
    }
}