/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

namespace Ex{

    public class Duration{

        private int m_callsNb = 0;

        public int calls_nb() {
            return m_callsNb;
        }
    }

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

        public void start(FlowElementInfo elementInfo) {
            gameObject.SetActive(true);
        }

        public void stop() {
            gameObject.SetActive(false);
        }
    }
}