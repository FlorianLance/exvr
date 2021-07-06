
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

        int nbVerticesH = 10;
        int nbVerticesV = 10;
        float width = 1f;
        float height = 0.6f;
        float depth = 0.001f;
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
            nbVerticesH = EditorGUILayout.IntField("Nb vertices H", nbVerticesH);
            nbVerticesV = EditorGUILayout.IntField("Nb vertices V", nbVerticesV);
            width = EditorGUILayout.FloatField("Width", width);
            height = EditorGUILayout.FloatField("Height", height);
            depth = EditorGUILayout.FloatField("Depth", depth);
            bothSides = EditorGUILayout.Toggle("Both sides", bothSides);
            goName    = EditorGUILayout.TextField("GO name", goName);

            if (GUILayout.Button("Generate")) {
                GameObject grid = new GameObject(goName);
                var mf = grid.AddComponent<MeshFilter>();
                //var mr = grid.AddComponent<MeshRenderer>();
                var smr = grid.AddComponent<SkinnedMeshRenderer>();
                smr.sharedMaterial = Resources.Load(string.Format("Materials/Procedural/Grid")) as Material;
                var mesh = PrimitivesMesh.GridBuilder.generate(nbVerticesH, nbVerticesV, width, height, depth);
                mf.mesh = mesh;                
                smr.sharedMesh = mesh;
                var cloth = grid.AddComponent<Cloth>();                
                var coeff = cloth.coefficients;

                int idV = 0;
                for(int ii = 0; ii < nbVerticesH; ii++) {
                    for(int jj = 0; jj < nbVerticesV; jj++, idV++) {
                        if(idV < nbVerticesH) {
                            coeff[idV].maxDistance = (1.0f * idV) / nbVerticesH;
                        } else {
                            coeff[idV].maxDistance = 0.0f;
                        }
                        Debug.Log("coeff[idV] " + idV + " " + coeff[idV].maxDistance);
                    }
                }

                for (int ii = 0; ii < nbVerticesH; ii++) {
                    for (int jj = 0; jj < nbVerticesV; jj++, idV++) {
                        coeff[idV].maxDistance = 0.0f;
                        //if (ii == 0) {
                        //    coeff[idV].maxDistance = 0.0f;
                        //} else {
                        //    coeff[idV].maxDistance = 0.5f;
                        //}
                    }
                }

                cloth.coefficients = coeff;
            }
        }
    }
}

#endif