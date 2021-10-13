
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex {

    public class AudioData {

        float[] data = null;
        int nbChannels = 0;
        public AudioData(AudioClip clip) {
            nbChannels = clip.channels;
            data = new float[clip.channels * clip.samples];
            clip.GetData(data, 0);
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
}