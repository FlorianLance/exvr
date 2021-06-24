/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public static class Layers{

        static public readonly int Default       = UnityEngine.LayerMask.NameToLayer("Default");
        static public readonly int Debug         = UnityEngine.LayerMask.NameToLayer("Debug");
        static public readonly int Ignore        = UnityEngine.LayerMask.NameToLayer("Ignore");
        static public readonly int LeftEye       = UnityEngine.LayerMask.NameToLayer("Left eye");
        static public readonly int RightEye      = UnityEngine.LayerMask.NameToLayer("Right eye");
        static public readonly int EyeCameraOnly = UnityEngine.LayerMask.NameToLayer("EyeCameraOnly");
        static public readonly int MirrorOnly    = UnityEngine.LayerMask.NameToLayer("MirrorOnly"); 
    }
}