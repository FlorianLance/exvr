
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

//using System.Collections;
//using System.Threading.Tasks;
//using System.Collections.Generic;
//using UnityEngine;

//public class DeformBreathing : MonoBehaviour{

//    public GameObject scene = null;
//    public bool female = true;

//    public GameObject femaleAvatar = null;
//    public GameObject maleAvatar = null;
//    public GameObject currentAvatar = null;
//    public SkinnedMeshRenderer shirt = null;
//    public SkinnedMeshRenderer pants = null;
//    public SkinnedMeshRenderer body = null;

//    public GameObject selection = null;
//    public GameObject projection = null;
//    public GameObject remove = null;

//    DuplicateMesh shirtD = null;
//    DuplicateMesh pantsD = null;
//    DuplicateMesh bodyD = null;

//    [Range(0, 16)]
//    public int colorId = 0;
//    public List<Color32> skinColors = new List<Color32>();
//    // warm ivory 253 231 173
//    // sienna 212 158 122
//    // honey 212 158 122
//    // umber 178 102 68
//    // sand 248 217 152
//    // limestone 236 192 145
//    // band 173 138 96
//    // golden 127 68 34
//    // pale ivory 254 227 197
//    // beige 242 194 128
//    // almond 147 95 55
//    // expresso 95 51 16
//    // rose beige 249 212 160
//    // amber 187 101 54
//    // bronze 115 63 23
//    // chocolate 41 23 9

//    float time = 0f;
//    public bool automatic = false;

//    [Range(0.0f, 1.0f)]
//    public float factor = 1f;

//    [Range(0.5f, 2.0f)]
//    public float calibShirtFactor = 1f;

//    [Range(0.5f, 2.0f)]
//    public float calibPantsFactor = 1f;

//    public class DuplicateMesh{

//        Mesh mesh = null;
//        private Matrix4x4[] verticesMatrix;
//        private Matrix4x4[] verticesInvertMatrix;
//        private Vector3[] initVertices;
//        private Vector3[] initVerticesTr;
//        private List<int> verticesIdInsideSelection;

//        bool inside_sphere(Vector3 pos, SphereCollider sphere) {
//            float radius = sphere.radius * sphere.transform.localScale.x;
//            return (pos - sphere.transform.position).sqrMagnitude < radius* radius;
//        }

//        public DuplicateMesh(SkinnedMeshRenderer skinnedMesh, GameObject selection, GameObject remove) {

//            System.Diagnostics.Stopwatch timer = new System.Diagnostics.Stopwatch();
//            timer.Start();

//            Mesh shared = skinnedMesh.sharedMesh;                       
//            mesh = new Mesh();

//            var bonesMatrices = new List<Matrix4x4>(skinnedMesh.bones.Length);
//            for (int ii = 0; ii < skinnedMesh.bones.Length; ++ii) {
//                bonesMatrices.Add(skinnedMesh.bones[ii].localToWorldMatrix * skinnedMesh.sharedMesh.bindposes[ii]);
//            }

//            verticesMatrix = new Matrix4x4[shared.vertexCount];
//            verticesInvertMatrix = new Matrix4x4[shared.vertexCount];
//            var bonesW = shared.boneWeights;
//            Parallel.For(0, verticesMatrix.Length, ii => {

//                var weight = bonesW[ii];
//                var bm0 = bonesMatrices[weight.boneIndex0];
//                var bm1 = bonesMatrices[weight.boneIndex1];
//                var bm2 = bonesMatrices[weight.boneIndex2];
//                var bm3 = bonesMatrices[weight.boneIndex3];

//                var vertexMatrix = new Matrix4x4();
//                for (int n = 0; n < 16; n++) {
//                    vertexMatrix[n] =
//                        bm0[n] * weight.weight0 +
//                        bm1[n] * weight.weight1 +
//                        bm2[n] * weight.weight2 +
//                        bm3[n] * weight.weight3;
//                }

//                verticesMatrix[ii] = vertexMatrix;
//                verticesInvertMatrix[ii] = verticesMatrix[ii].inverse;
//            });
//            Debug.Log("t0 " + timer.ElapsedMilliseconds);

//            // check vertices inside remove
//            HashSet<int> verticesInside = new HashSet<int>();
//            for (int ii = 0; ii < shared.vertexCount; ++ii) {

//                if (remove == null) {
//                    break;
//                }

//                var point  = verticesMatrix[ii].MultiplyPoint3x4(shared.vertices[ii]);
//                bool inside = false;


//                foreach (var sphere in remove.GetComponentsInChildren<SphereCollider>()) {
//                    if(inside_sphere(point, sphere)) {
//                        inside = true;
//                    }                 
//                }

//                if (inside) {
//                    verticesInside.Add(ii);
//                }
//            }

//            List<int> newTriangles = new List<int>(shared.triangles.Length/3);
//            var triangles = shared.triangles;
//            for (int ii = 0; ii < triangles.Length; ii += 3) {

//                if (remove == null) {
//                    break;
//                }

//                var v1 = triangles[ii];
//                var v2 = triangles[ii + 1];
//                var v3 = triangles[ii + 2];

//                if (!verticesInside.Contains(v1) && !verticesInside.Contains(v2) && !verticesInside.Contains(v3)) {
//                    newTriangles.Add(v1);
//                    newTriangles.Add(v2);
//                    newTriangles.Add(v3);
//                }
//            }

//            initVertices        = shared.vertices;
//            initVerticesTr = new Vector3[initVertices.Length];
//            for (int ii = 0; ii < initVertices.Length; ++ii) {
//                initVerticesTr[ii] = verticesMatrix[ii].MultiplyPoint3x4(initVertices[ii]);
//            }

//            mesh.vertices       = shared.vertices;
//            mesh.normals        = shared.normals;
//            mesh.uv             = shared.uv;
//            mesh.bindposes      = shared.bindposes;
//            mesh.boneWeights    = shared.boneWeights;
//            if (remove != null) {
//                mesh.triangles = newTriangles.ToArray();
//            } else {
//                mesh.triangles = shared.triangles;

//            }

//            skinnedMesh.sharedMesh = mesh;


//            // retrieve vertices id inside selection spehres
//            var selectionColliders = selection.GetComponentsInChildren<SphereCollider>();
//            verticesIdInsideSelection = new List<int>(initVertices.Length);
//            for (int ii = 0; ii < initVertices.Length; ++ii) {
//                var point = initVerticesTr[ii];

//                bool inside = false;
//                foreach (var sphere in selectionColliders) {
//                    if (inside_sphere(point, sphere)) {
//                        inside = true;
//                        break;
//                    } else {
//                        continue;
//                    }
//                }

//                if (inside) {
//                    verticesIdInsideSelection.Add(ii);
//                }
//            }
//        }

//        public void update(float factor, GameObject selection, GameObject projection) {

//            // retrieve vertices indices in the selection spheres
//            var vertices = mesh.vertices;

//            var projectionColliders = projection.GetComponentsInChildren<SphereCollider>();

//            for (int ii = 0; ii < verticesIdInsideSelection.Count; ++ii) {

//                int id = verticesIdInsideSelection[ii];
//                var point = initVerticesTr[id];

//                SphereCollider closestSphere = null;
//                float minDist = 0f;
//                Vector3 minSphereToPoint = Vector3.zero;
//                foreach (var sphere in projectionColliders) {

//                    Vector3 sphereP = sphere.transform.position;
//                    Vector3 sphereToPoint = point - sphereP;
//                    var currDist = sphereToPoint.magnitude;

//                    if (closestSphere == null) {
//                        closestSphere = sphere;
//                        minSphereToPoint = sphereToPoint;
//                        minDist = currDist;
//                    } else {
//                        if (currDist < minDist) {
//                            minDist = currDist;
//                            minSphereToPoint = sphereToPoint;
//                            closestSphere = sphere;
//                        }
//                    }
//                }

//                if (closestSphere == null) {
//                    continue;
//                }

//                minSphereToPoint.Normalize();
//                minSphereToPoint *= closestSphere.radius * closestSphere.transform.localScale.x;

//                Vector3 worldPoint = closestSphere.transform.position + minSphereToPoint;
//                vertices[id] = point + (worldPoint - point) * factor;
//                vertices[id] = verticesInvertMatrix[id].MultiplyPoint3x4(vertices[id]);

//            }
//            mesh.vertices = vertices;
//            mesh.RecalculateNormals();
//        }
//    }


//    void Start(){

//        // retrieve avatar
//        femaleAvatar = scene.transform.Find("female").gameObject;
//        maleAvatar   = scene.transform.Find("male").gameObject;
//        femaleAvatar.SetActive(female);
//        maleAvatar.SetActive(!female);
//        currentAvatar = female ? femaleAvatar : maleAvatar;

//        selection  = currentAvatar.transform.Find("selection").gameObject;
//        projection = currentAvatar.transform.Find("projection").gameObject;
//        remove     = currentAvatar.transform.Find("remove").gameObject;

//        // retrive shirt skinned mesh
//        shirt = currentAvatar.transform.Find("shirt").GetComponent<SkinnedMeshRenderer>();
//        pants = currentAvatar.transform.Find("pants").GetComponent<SkinnedMeshRenderer>();
//        body  = currentAvatar.transform.Find("body").GetComponent<SkinnedMeshRenderer>();


//        shirtD = new DuplicateMesh(shirt, selection, null);
//        pantsD = new DuplicateMesh(pants, selection, remove);
//        bodyD  = new DuplicateMesh(body, selection, remove);

//        selection.SetActive(false);
//        projection.SetActive(false);
//        remove.SetActive(false);
//    }

//    // Update is called once per frame
//    void Update(){

//        body.material.color = skinColors[colorId];

//        time += Time.deltaTime;        
//        float currentFactor = automatic ? (float)System.Math.Cos((double)(time * 1f))*0.5f + 0.5f : factor;        
//        shirtD.update(calibShirtFactor * currentFactor, selection, projection);
//        pantsD.update(calibPantsFactor * currentFactor, selection, projection);
//    }
//}
