/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex{

    [RequireComponent(typeof(MeshRenderer))]
    [RequireComponent(typeof(MeshFilter))]
    public class GridMesh : MonoBehaviour{

        public int GridSize = 100;

        void Awake() {
            MeshFilter filter = gameObject.GetComponent<MeshFilter>();
            var mesh = new Mesh();
            var vertices = new List<Vector3>();

            var indices = new List<int>();
            for (int i = 0; i < GridSize; i++) {
                vertices.Add(new Vector3(i, 0, 0));
                vertices.Add(new Vector3(i, 0, GridSize));

                indices.Add(4 * i + 0);
                indices.Add(4 * i + 1);

                vertices.Add(new Vector3(0, 0, i));
                vertices.Add(new Vector3(GridSize, 0, i));

                indices.Add(4 * i + 2);
                indices.Add(4 * i + 3);
            }

            mesh.vertices = vertices.ToArray();
            mesh.SetIndices(indices.ToArray(), MeshTopology.Lines, 0);
            filter.mesh = mesh;

            MeshRenderer meshRenderer = gameObject.GetComponent<MeshRenderer>();
            //meshRenderer.material = new Material(Shader.Find("Sprites/Default"));
            meshRenderer.material.color = Color.black;
        }
    }
}