﻿
/***********************************************************************************
** exvr-exp                                                                       **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

// system
using System;
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex{

    public class AudioSourceComponent : ExComponent{

        // signals
        private static readonly string sampleValueChannelStr = "sample value channel";

        private Mesh m_audioMesh = null;        
        private AudioClip m_audioClip = null;
        private AudioData m_audioData = null;

        private bool m_stopEndBlock = false;
        private bool m_playNewBlock = false;
        private bool m_pauseEndBlock = false;

        public GameObject audioSourceGO = null;
        public AudioSource audioSource = null;

        #region ex_functions
        protected override bool initialize() {

            // slots
            add_slot("play", (nullArg) => {
                audioSource.Play(); // TODO
            });
            add_slot("pause", (nullArg) => {
                pause();
            });
            add_slot("set time", (time) => {
                set_time((float)time);
            });
            add_slot("set volume", (volume) => {
                set_volume((float)volume);
            });
            // signals
            add_signal("sample value channel");

            audioSourceGO = ExVR.GlobalResources().instantiate_prebab("Components/AudioSource", transform, "Audio source");
            if (audioSourceGO == null) {
                log_error("Failed to load audio source GameObject");
                return false;
            }
            audioSourceGO.SetActive(true);
            m_audioMesh = audioSourceGO.GetComponent<MeshFilter>().mesh;
            audioSourceGO.GetComponent<MeshFilter>().mesh = null;            

            audioSource             = audioSourceGO.GetComponent<AudioSource>();
            audioSource.clip        = null;
            audioSource.playOnAwake = false;            
            audioSource.loop        = false;
            audioSource.spatialize  = false;

            var audioFileData = initC.get_resource_audio_data("sound"); 
            if(audioFileData == null) {
                log_error("Cannot load audio file.");
                return false;
            }

            m_audioClip = audioFileData.clip;
            if(m_audioClip == null) {
                log_error("No audio file resource defined as a source.");
                return false;
            }

            // send sound characteristices
            List<string> infos = new List<string>();
            infos.Add(m_audioClip.name);
            infos.Add(Converter.to_string(m_audioClip.channels));
            infos.Add(Converter.to_string(m_audioClip.frequency));
            infos.Add(Converter.to_string(m_audioClip.length));
            infos.Add(Converter.to_string(m_audioClip.samples));
            infos.Add(Converter.to_string(m_audioClip.ambisonic));           

            send_infos_to_gui_init_config("input_sound_info", String.Join("?", infos.ToArray()));

            if (initC.get<bool>("generate_new_sound")) {
                int newNbChannels = initC.get<int>("new_sound_channel") + 1;

                var newClip = AudioClip.Create(m_audioClip.name + "_modified", m_audioClip.samples, newNbChannels, m_audioClip.frequency, false);

                float[] currentSamples = new float[m_audioClip.samples * m_audioClip.channels];
                m_audioClip.GetData(currentSamples, 0);

                float[] newSamples = new float[m_audioClip.samples * newNbChannels];
                for(int ii = 0; ii < newSamples.Length; ++ii) {
                    newSamples[ii] = 0f;
                }

                for (int originChannel = 0; originChannel < newNbChannels; ++originChannel) {

                    var copyTo = initC.get<string>("channel_" + originChannel + "_copy_destination");
                    var destinationChannelsStr = copyTo.Split(' ');

                    foreach (var destinationChannelStr in destinationChannelsStr) {

                        if (destinationChannelStr.Length == 0) {
                            break;
                        }

                        var destinationChannel = Converter.to_int(destinationChannelStr);
                        if (destinationChannel < 1 || destinationChannel > 8) {
                            log_error("Bad channel value: " + destinationChannel);
                            return false;
                        }
                        destinationChannel--;                        

                        for (int sampleId = 0; sampleId < m_audioClip.samples; ++sampleId) {
                            newSamples[sampleId * newNbChannels + destinationChannel] = currentSamples[sampleId * m_audioClip.channels + originChannel];
                            //newSamples[audioClip.samples * newNbChannels + sampleId + destinationChannel] = currentSamples[audioClip.samples * audioClip.channels + sampleId + originChannel];
                            //newSamples[destinationChannel * audioClip.samples + sampleId] = currentSamples[originChannel * audioClip.samples + sampleId];
                        }
                    }
                }

                newClip.SetData(newSamples,0);
                m_audioClip = newClip;
            }

            audioSource.clip = m_audioClip;
            m_audioData = new AudioData(audioSource.clip);

            return true;
        }

        public override void update_from_current_config() {

            audioSource.spatialBlend = 0;
            audioSource.loop         = currentC.get<bool>("loop");
            audioSource.minDistance  = currentC.get<float>("min_distance");
            audioSource.maxDistance  = currentC.get<float>("max_distance");
            audioSource.spatialize   = currentC.get<bool>("spatialized");            
            audioSource.pitch        = currentC.get<float>("pitch");
            audioSource.panStereo    = currentC.get<float>("stereo");
            audioSource.spatialBlend = currentC.get<float>("spatial_blend");
            m_playNewBlock             = currentC.get<bool>("play_new_block");
            m_stopEndBlock             = currentC.get<bool>("stop_end_block");
            m_pauseEndBlock            = currentC.get<bool>("pause_end_block");

            set_volume(currentC.get<float>("volume"));

            if (!currentC.get<bool>("transform_do_not_apply")) {
                currentC.update_transform("transform", transform);
            }
        }

        protected override void update_parameter_from_gui(string updatedArgName) {
            update_from_current_config();
        }


        protected override void set_visibility(bool visibility) {
            audioSourceGO.GetComponent<MeshFilter>().mesh = (visibility && currentC.get<bool>("display"))? m_audioMesh : null;
        }

        protected override void set_update_state(bool doUpdate) {

            if (doUpdate) {
                if (m_playNewBlock) {
                    audioSource.Play();
                }
            } else {
                if (m_stopEndBlock) {
                    audioSource.Stop();
                } else if (m_pauseEndBlock) {
                    audioSource.Pause();
                }
            }
        }

        protected override void update() {

            for (int ii = 0; ii < audioSource.clip.channels; ++ii) {                      
                invoke_signal(sampleValueChannelStr, new IdAny(ii + 1, m_audioData.channel_value(audioSource.timeSamples, ii)));
            }
        }


        #endregion

        #region public_functions

        public void start_sound() {
            audioSource.Play();
        }
        public void stop_sound() {
            audioSource.Stop();
        }

        public override void play() {
            audioSource.UnPause();
        }

        public override void pause() {
            audioSource.Pause();
        }

        public void set_time(float time) {
            if(time < audioSource.clip.length) {
                audioSource.time = time;
            }            
        }

        public void set_volume(float volume) {
            audioSource.volume = volume;
        }

        #endregion
    }
}