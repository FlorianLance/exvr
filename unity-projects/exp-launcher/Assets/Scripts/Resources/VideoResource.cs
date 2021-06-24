/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class VideoResource : ResourceFile{

        public VideoResource(int key, string alias, string path) : base(key, alias, path) {


            //m_player = gameObject.AddComponent<UnityEngine.Video.VideoPlayer>();
        }
    }

}


//namespace Ex
//{

//    public class VideoFileComponent : ExComponent
//    {

//        private UnityEngine.Video.VideoPlayer m_player = null;
//        private Texture2D m_currentFrame = null;

//        protected override bool initialize() {

//            events().add_slot("pause", () => { pause(); });
//            events().add_slot("play", () => { play(); });
//            events().add_signal("new_frame", 1);

//            string videoPath = ExVR.Resources().get_video_file_data(initC.get_resource_alias("video")).path;
//            if (videoPath.Length == 0) {
//                return false;
//            }

//            // init player
//            m_player = gameObject.AddComponent<UnityEngine.Video.VideoPlayer>();
//            m_player.playOnAwake = false;
//            m_player.sendFrameReadyEvents = true;
//            m_player.source = UnityEngine.Video.VideoSource.Url;
//            m_player.url = videoPath;

//            m_player.sendFrameReadyEvents = true;
//            m_player.frame = 0;
//            m_player.frameReady += on_new_frame;

//            return true;
//        }

//        protected override void start_routine() {
//            m_player.frame = 0;
//            m_player.Play();
//        }

//        public override void play() {
//            m_player.Play();
//        }

//        public override void pause() {
//            m_player.Pause();
//        }

//        protected override void stop_routine() {
//            m_player.Stop();
//        }

//        void on_new_frame(UnityEngine.Video.VideoPlayer player, long frameIdx) {

//            RenderTexture renderTexture = player.texture as RenderTexture;
//            if (m_currentFrame == null) {
//                m_currentFrame = new Texture2D(renderTexture.width, renderTexture.height);
//            } else {
//                if (m_currentFrame.width != renderTexture.width || m_currentFrame.height != renderTexture.height) {
//                    m_currentFrame.Resize(renderTexture.width, renderTexture.height);
//                }
//            }

//            RenderTexture.active = renderTexture;
//            m_currentFrame.ReadPixels(new Rect(0, 0, renderTexture.width, renderTexture.height), 0, 0);
//            m_currentFrame.Apply();
//            RenderTexture.active = null;

//            events().invoke_signal("new_frame", new ImageContainer(m_currentFrame, true));
//        }

//        protected override void clean() {
//            if (m_currentFrame != null) {
//                Destroy(m_currentFrame);
//            }
//        }
//    }
//}