///*******************************************************************************
//** exvr-exp                                                                   **
//** No license (to be defined)                                                 **
//** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
//********************************************************************************/

//using UnityEngine;

//public class AnimationController : MonoBehaviour{

//    private Animator m_animator = null;

//    [SerializeField]
//    public string state = "Default";

//    [SerializeField]
//    public bool auto = false;

//    [SerializeField]
//    [Range(0.0f, 1.0f)]
//    public float time = 0f;

//    [SerializeField]
//    [Range(0.0f, 10f)]
//    public float factor = 1f;

//    // Start is called before the first frame update
//    void Awake(){
//        m_animator = GetComponent<Animator>();
//    }

//    // Update is called once per frame
//    void Update(){
//        return;
//        if (auto) {
//            m_animator.speed = 1f;
//            time += factor * Time.deltaTime;
//            if (time > 1f) {
//                time -= 1f;
//            }
            
//        } else {
//            m_animator.speed = 0f;
//        }

//        m_animator.Play(state, 0, time);
//    }

//    public void set_current_state(float time) {
//        this.time = time;
//        m_animator.Play(state, 0, time);
//    }
//}
////using System.Collections;
////using System.Collections.Generic;
////using UnityEngine;

////public class controllAnim : MonoBehaviour
////{

////    public List<GameObject> keepValues;

////    private List<Transform> transfos;
////    private List<Vector3> positions;
////    private List<Quaternion> rotations;

////    // Start is called before the first frame update
////    void Awake() {

////        positions = new List<Vector3>();
////        rotations = new List<Quaternion>();
////        transfos = new List<Transform>();
////        foreach (var go in keepValues) {
////            Transform[] trInChildren = go.GetComponentsInChildren<Transform>();
////            foreach (var tr in trInChildren) {
////                transfos.Add(tr);
////                positions.Add(tr.position);
////                rotations.Add(tr.rotation);
////            }
////        }
////    }

////    // Update is called once per frame
////    void Update() {

////        if (auto) {
////            ratio += factor * Time.deltaTime;
////            if (ratio > 1f) {
////                ratio -= 1f;
////            }
////        }
////        GetComponent<Animator>().SetFloat("progress", ratio);

////        for (int ii = 0; ii < transfos.Count; ++ii) {
////            transfos[ii].position = positions[ii];
////            transfos[ii].rotation = rotations[ii];
////        }
////    }
////}
