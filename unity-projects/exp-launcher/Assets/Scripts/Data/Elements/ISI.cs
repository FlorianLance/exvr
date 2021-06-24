/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

namespace Ex{

    public class ISI : FlowElement{

        
        public List<double> m_durations = null;

        private bool m_randomized = false;


        public void initialize(XML.Isi isi) {

            m_key        = isi.Key;
            m_keyStr     = Converter.to_string(isi.Key);
            m_type       = FlowElementType.Isi;
            m_randomized = isi.Randomized;

            string[] splits = isi.Set.Split(' ');
            m_durations = new List<double>(splits.Length);
            foreach (string split in splits) {
                m_durations.Add(Converter.to_double(split));
            }
        }

        public void enable(FlowElementInfo elementInfo) {


            if (gameObject.activeSelf) {
                return;
            }
            
            gameObject.SetActive(true);
        }

        public void disable() {

            if (!gameObject.activeSelf) {
                return;
            }

            gameObject.SetActive(false);
        }


    }
}