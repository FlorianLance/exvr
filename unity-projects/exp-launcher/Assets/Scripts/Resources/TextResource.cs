/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.IO;


namespace Ex{

    public class TextResource : ResourceFile{

        public string content;

        public TextResource(int key, string alias, string path) : base(key, alias, path) {

            try {
                content = File.ReadAllText(path);
            } catch (System.Exception ex) {
                log_error(string.Format("Cannot read text file {0}, error: {1}", path, ex.Message));
                content = "";
            }
        }
    }
}