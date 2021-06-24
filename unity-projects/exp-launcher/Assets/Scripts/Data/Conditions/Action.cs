/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class Action{

        private TimeLine        m_timeline  = null;
        private ComponentConfig m_config    = null;        
        private ExComponent     m_component = null;

        public void set_config(ComponentConfig config) {
            m_config = config;
        }

        public ComponentConfig config() {
            return m_config;
        }

        public TimeLine timeline() {
            return m_timeline;
        }

        public ExComponent component() {
            return m_component;
        }
        public void force_config(ComponentConfig config) {
            m_config = config;
        }

        public Action(XML.Action actionXml) {

            // init timeline
            m_timeline = new TimeLine(actionXml.Timelines[0], actionXml.Timelines[1]);

            // retrieve component
            m_component = ExVR.Components().get(actionXml.KeyComponent);

            if (!m_component) {
                ExVR.Log().error(string.Format("Cannot init action, component with key {0} not found. ", actionXml.KeyComponent));
                return;
            }
            
            // retrieve config
            foreach (ComponentConfig config in m_component.configs) {
                if (config.key == actionXml.KeyConfig) {
                    m_config = config;
                    break;
                }
            }

            if (m_config == null) {
                ExVR.Log().error("Cannot init action, config with key " + actionXml.KeyConfig + " in component " + m_component.name + " not found. ");
                return;
            }           
        }
    }
}