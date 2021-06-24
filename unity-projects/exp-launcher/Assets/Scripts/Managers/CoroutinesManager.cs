/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections;

// unity
using UnityEngine;


namespace Ex {

    public class CoroutinesManager : MonoBehaviour{

        public Coroutine start(IEnumerator coroutine) {
            return StartCoroutine(coroutine);
        }

        public Coroutine start(string coroutineName, object value) {
            return StartCoroutine(coroutineName, value);
        }

        public void stop_coroutine(IEnumerator coroutine) {
            StopCoroutine(coroutine);
        }
    }

    public class CoroutineWithData{

        public Coroutine coroutine { get; private set; }
        public object result;
        private IEnumerator target;

        public CoroutineWithData(IEnumerator target) {

            this.target = target;
            this.coroutine =  ExVR.Coroutines().start(Run());
        }

        private IEnumerator Run() {
            while (target.MoveNext()) {
                result = target.Current;
                yield return result;
            }
        }
    }
}