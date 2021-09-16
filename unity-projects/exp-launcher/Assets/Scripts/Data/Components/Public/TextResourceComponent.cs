/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

namespace Ex{

    public class TextResourceComponent : ExComponent{

        string m_text = "";
        string[] m_lines = null;
        int m_currentLine = 0;

        protected override bool initialize() {

            add_signal("full text");
            add_signal("alias");
            add_signal("path");
            add_signal("line");

            add_slot("read line", (nullArg) => {
                if(m_currentLine < m_lines.Length) {
                    invoke_signal("line", m_lines[m_currentLine++]);
                }                
            });

            return true;
        }

        protected override void start_routine() {
            load_text();            
        }

        protected override void update_parameter_from_gui(string updatedArgName) {
            if (updatedArgName == "text") {
                load_text();
            }
        }

        private void load_text() {            
            string textAlias = currentC.get_resource_alias("text");
            var textData = ExVR.Resources().get_text_file_data(textAlias);
            m_text = string.Copy(textData.content);
            m_lines =  m_text.Split('\n');
            m_currentLine = 0;
            
            invoke_signal("alias", textData.alias);
            invoke_signal("path", textData.path);
            invoke_signal("full text", m_text);
        }
    }
}