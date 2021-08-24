
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


// system
using System;
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex{

    public class AudioData {

        float[] data = null;
        int nbChannels = 0;
        public AudioData(AudioClip clip) {
            nbChannels = clip.channels;
            data = new float[clip.channels*clip.samples];
            clip.GetData(data,0);
        }

        public float channel_value(int currentSample, int channelId) {
            if (channelId < nbChannels) {
                int id = (currentSample) * nbChannels + channelId;
                if (id < data.Length) {
                    return data[id];
                } 
            }
            return 0f;
        }
    }

    public class AudioSourceComponent : ExComponent{

        public GameObject audioSourceGO = null;
        private Mesh audioMesh = null;
        public AudioSource audioSource = null;
        private AudioClip audioClip = null; 

        private bool stopEndBlock = false;
        private bool playNewBlock = false;
        private bool pauseEndBlock = false;

        private AudioData audioData = null;

        // signals
        private static readonly string sampleValueChannelStr = "sample value channel";

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
            audioMesh = audioSourceGO.GetComponent<MeshFilter>().mesh;
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

            audioClip = audioFileData.clip;
            if(audioClip == null) {
                log_error("No audio file resource defined as a source.");
                return false;
            }

            // send sound characteristices
            List<string> infos = new List<string>();
            infos.Add(audioClip.name);
            infos.Add(Converter.to_string(audioClip.channels));
            infos.Add(Converter.to_string(audioClip.frequency));
            infos.Add(Converter.to_string(audioClip.length));
            infos.Add(Converter.to_string(audioClip.samples));
            infos.Add(Converter.to_string(audioClip.ambisonic));           

            send_infos_to_gui_init_config("input_sound_info", String.Join("?", infos.ToArray()));

            if (initC.get<bool>("generate_new_sound")) {
                int newNbChannels = initC.get<int>("new_sound_channel") + 1;

                var newClip = AudioClip.Create(audioClip.name + "_modified", audioClip.samples, newNbChannels, audioClip.frequency, false);

                float[] currentSamples = new float[audioClip.samples * audioClip.channels];
                audioClip.GetData(currentSamples, 0);

                float[] newSamples = new float[audioClip.samples * newNbChannels];
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

                        for (int sampleId = 0; sampleId < audioClip.samples; ++sampleId) {
                            newSamples[sampleId * newNbChannels + destinationChannel] = currentSamples[sampleId * audioClip.channels + originChannel];
                            //newSamples[audioClip.samples * newNbChannels + sampleId + destinationChannel] = currentSamples[audioClip.samples * audioClip.channels + sampleId + originChannel];
                            //newSamples[destinationChannel * audioClip.samples + sampleId] = currentSamples[originChannel * audioClip.samples + sampleId];
                        }
                    }
                }

                newClip.SetData(newSamples,0);
                audioClip = newClip;
            }

            audioSource.clip = audioClip;
            audioData = new AudioData(audioSource.clip);

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
            playNewBlock             = currentC.get<bool>("play_new_block");
            stopEndBlock             = currentC.get<bool>("stop_end_block");
            pauseEndBlock            = currentC.get<bool>("pause_end_block");

            set_volume(currentC.get<float>("volume"));

            if (!currentC.get<bool>("transform_do_not_apply")) {
                currentC.update_transform("transform", transform);
            }
        }

        protected override void start_routine() {
            update_from_current_config();            
        }

        protected override void update_parameter_from_gui(XML.Arg arg) {
            update_from_current_config();
        }

        protected override void set_visibility(bool visibility) {
            audioSourceGO.GetComponent<MeshFilter>().mesh = (visibility && currentC.get<bool>("display"))? audioMesh : null;
        }

        protected override void set_update_state(bool doUpdate) {

            if (doUpdate) {
                if (playNewBlock) {
                    audioSource.Play();
                }
            } else {
                if (stopEndBlock) {
                    audioSource.Stop();
                } else if (pauseEndBlock) {
                    audioSource.Pause();
                }
            }
        }

        protected override void update() {

            for (int ii = 0; ii < audioSource.clip.channels; ++ii) {                      
                invoke_signal(sampleValueChannelStr, new IdAny(ii + 1, audioData.channel_value(audioSource.timeSamples, ii)));
            }
        }

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
    }
}