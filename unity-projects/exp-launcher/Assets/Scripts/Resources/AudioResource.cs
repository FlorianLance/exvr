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

    public class AudioResource : ResourceFile{

        public AudioType type;
        public AudioClip clip = null;
        private static AudioClip m_lastAudioClipLoaded = null;

        public AudioResource(int key, string alias, string path) : base(key, alias, path) {

            var enumerator = load_audio_clip(path); // load file in couroutine
            while (enumerator.MoveNext()) { // wait for the end
            }

            if (m_lastAudioClipLoaded == null) {
                log_error("Failed to load audio clip with path: " + path);
            } else {
                clip = m_lastAudioClipLoaded;
            }
        }

        private System.Collections.IEnumerator load_audio_clip(string pathAudioFile) {

            // find audio type
            var ext = Path.GetExtension(pathAudioFile);
            AudioType type = AudioType.UNKNOWN;
            if (ext == ".wav") {
                type = AudioType.WAV;
            } else if (ext == ".mp3") {
                type = AudioType.MPEG;
            } else if (ext == ".ogg") {
                type = AudioType.OGGVORBIS;
            } else if (ext == ".aif") {
                type = AudioType.AIFF;
            }

            // send media request
            UnityEngine.Networking.UnityWebRequest request = UnityEngine.Networking.UnityWebRequestMultimedia.GetAudioClip(pathAudioFile, type);
            yield return request.SendWebRequest();

            while (!request.isDone) {
                yield return true;
            }

            if (request.isNetworkError || request.isHttpError) { // check errors
                log_error("Error happened during multimedia request.");
                m_lastAudioClipLoaded = null;
            } else { // get content                
                m_lastAudioClipLoaded = UnityEngine.Networking.DownloadHandlerAudioClip.GetContent(request);
            }
        }
    }

}