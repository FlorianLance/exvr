/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


// system
using System.Collections.Generic;

// unity
using UnityEngine;


#if UNITY_EDITOR
using UnityEditor;
namespace Ex
{

    [CustomEditor(typeof(ISIs))]
    public class ISIsEditor : Editor{

        public override bool RequiresConstantRepaint() {
            return true;
        }

        public override void OnInspectorGUI() {

            base.OnInspectorGUI();

            if (!Application.isPlaying) {
                return;
            }

            foreach (var isi in ExVR.ISIs().get_all()) {
                EditorGUILayout.ObjectField(isi, typeof(ISI), true);
            }

            var currentI = ExVR.ISIs().current();
            EditorGUILayout.LabelField("Current: ");
            EditorGUILayout.ObjectField(currentI, typeof(ISI), true);
        }
    }
}
#endif


namespace Ex
{

    public class ISIs : MonoBehaviour{

        private List<ISI> m_ISIs = new List<ISI>();
        private ISI m_currentIsi = null;

        public void generate_from_xml(XML.ISIs xmlISIs) {

            foreach (XML.Isi xmlIsi in xmlISIs.Isi) {
                var isi = GO.generate_empty_object(xmlIsi.Name, ExVR.GO().ISIs.transform).AddComponent<ISI>();
                isi.initialize(xmlIsi);
                m_ISIs.Add(isi);
            }
        }

        public ISI current() {
            return m_currentIsi;
        }

        public List<ISI> get_all() {
            return new List<ISI>(m_ISIs);
        }

        public ISI get(int isiKey) {

            foreach(var isi in m_ISIs) {
                if(isi.key() == isiKey) {
                    return isi;
                }
            }
            return null;
        }


        public void disable() {
            foreach (var isi in m_ISIs) {
                isi.disable();
            }
            m_currentIsi = null;
        }

        public void clean() {

            foreach (var isi in m_ISIs) {
                Destroy(isi.gameObject);
            }
            m_ISIs.Clear();
        }

        public void enable(ISIInfo info) {
            m_currentIsi = (ISI)info.element;
            ExVR.ExpLog().isi_manager(info);
            m_currentIsi.enable(info);
        }
    }
}


