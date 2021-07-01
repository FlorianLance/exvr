
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/



#if UNITY_EDITOR

// unity
using UnityEngine;
using UnityEditor;

namespace Ex{

    public class EditorGeometryMenu : EditorWindow{

        int sizeX = 10;
        int sizeY = 10;
        bool bothSides = true;
        string goName = "Grid";

        // Add menu item named "My Window" to the Window menu
        [MenuItem("Geometry/Grid generator")]
        public static void ShowWindow() {
            //Show existing window instance. If one doesn't exist, make one.
            GetWindow(typeof(EditorGeometryMenu));
        }

        void OnGUI() {

            GUILayout.Label("Grid settings", EditorStyles.boldLabel);
            sizeX     = EditorGUILayout.IntField("Size X", sizeX);
            sizeY     = EditorGUILayout.IntField("Size Y", sizeY);
            bothSides = EditorGUILayout.Toggle("Both sides", bothSides);
            goName    = EditorGUILayout.TextField("GO name", goName);

            if (GUILayout.Button("Generate")) {
                GameObject grid = new GameObject(goName);
                var mf = grid.AddComponent<MeshFilter>();
                var mr = grid.AddComponent<MeshRenderer>();
                mr.sharedMaterial = Resources.Load(string.Format("Materials/Procedural/Grid")) as Material;
                mf.mesh = PrimitivesMesh.GridBuilder.generate(sizeX, sizeY, bothSides);
            }
        }
    }
}

#endif