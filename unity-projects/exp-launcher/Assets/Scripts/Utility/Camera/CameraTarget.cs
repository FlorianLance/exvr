
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{

    class CameraTarget{
        public int id;
        public double time;
        public bool display;
        public bool sphericInterpolation;
        public Vector3 translation;
        public Vector3 rotation;
        public Color color;
        public AnimationCurve speed;
    }
}