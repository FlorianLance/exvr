/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


// unity
using UnityEngine;

namespace Ex{

    public class MemoryManager : MonoBehaviour{

        public void initialize() {
        }
        public void delete_texture(Texture2D texture) {
            if(texture != null) {
                Destroy(texture);
            }
        }
    }
}