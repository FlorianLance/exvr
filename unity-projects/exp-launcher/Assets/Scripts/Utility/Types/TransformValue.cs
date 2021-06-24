/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex {
    public class TransformValue {

        public static TransformValue from_transform(Transform transform) {
            var trV = new TransformValue();
            trV.position = transform.position;
            trV.rotation = transform.rotation;
            trV.scale    = transform.localScale;
            return trV;
        }

        public Vector3 position     = Vector3.zero;
        public Quaternion rotation  = Quaternion.identity;
        public Vector3 scale        = Vector3.one;
    }
}
