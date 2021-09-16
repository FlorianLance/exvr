

/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

[RequireComponent(typeof(MeshFilter))]
public class BlendFadeOverlay : MonoBehaviour{

    
    private bool isColorChanging = false;
    private float timer = 0.0f;

    public float blendColorDuration = 2.0f;
    public float fadeColorDuration = 2.0f;
    private bool doBlendAndFade = true;


    private Color fromColor;
    private Color toColor;
    private Material material;

    public void initialize() {

        reverse_normals(gameObject);
        material = gameObject.GetComponent<Renderer>().material;

        isColorChanging = false;
        timer           = 0;        
    }


    public void start_color_change(bool onlyBlend, Color start, Color end, float durationBlend, float durationFade) {

        doBlendAndFade      = !onlyBlend;
        fromColor           = start;
        toColor             = end;
        blendColorDuration  = durationBlend;
        fadeColorDuration   = durationFade;
        isColorChanging     = true;
        timer               = 0;
    }

    public void update() {

        if (isColorChanging == false) {
            return;
        }

        timer += Time.deltaTime;

        if (doBlendAndFade) {

            if (timer < blendColorDuration) {
                float factor = timer / blendColorDuration;
                if (factor >= 1f) {
                    factor = 0.99f;
                }
                material.color = Color.Lerp(fromColor, toColor, factor);
            }else if((timer - blendColorDuration) < fadeColorDuration) {
                float factor = (timer - blendColorDuration) / fadeColorDuration;
                if(factor >= 1f) {
                    factor = 0.99f;
                }
                material.color = Color.Lerp(toColor, fromColor, factor);
            } else {
                material.color = fromColor;
                isColorChanging = false;
                timer = 0;
            }

        } else {
            if(timer < blendColorDuration) {
                float factor = timer / blendColorDuration;
                if (factor >= 1f) {
                    factor = 0.99f;
                }
                material.color = Color.Lerp(fromColor, toColor, factor);
            } else {
                material.color = toColor;
                isColorChanging = false;
                timer = 0;
            }
        }
    }

    private void reverse_normals(GameObject gameObject) {

        MeshFilter filter = gameObject.GetComponent(typeof(MeshFilter)) as MeshFilter;
        if (filter != null) {

            Mesh mesh = filter.mesh;
            Vector3[] normals = mesh.normals;
            for (int ii = 0; ii < normals.Length; ii++) {
                normals[ii] = -normals[ii];
            }
            mesh.normals = normals;

            for (int ii = 0; ii < mesh.subMeshCount; ii++) {
                int[] triangles = mesh.GetTriangles(ii);
                for (int jj = 0; jj < triangles.Length; jj += 3) {
                    int temp = triangles[jj + 0];
                    triangles[jj + 0] = triangles[jj + 1];
                    triangles[jj + 1] = temp;
                }
                mesh.SetTriangles(triangles, ii);
            }
        }
    }
}
