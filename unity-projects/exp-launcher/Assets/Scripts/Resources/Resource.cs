/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.IO;

namespace Ex{

    public class Resource{

        public int key;
        public string alias;
        public string path;
        public bool doNotRemove = false;

        public Resource(int key, string alias, string path) {
            this.key = key;
            this.alias = alias;
            this.path = path;
        }

        public virtual void read_data() {
        }

        public virtual void initialize() {
        }

        public virtual void clean() {
        }

        public string verbose_name() {
            return string.Format(" [From resource of type {0} with alias {1}]", this.GetType().ToString(), alias);
        }

        public void log_message(string message, bool verbose = false) {
            if (verbose) {
                ExVR.Log().message(string.Concat(message, verbose_name()));
            } else {
                ExVR.Log().message(message);
            }
        }

        public void log_warning(string warning, bool verbose = true) {
            if (verbose) {
                ExVR.Log().warning(string.Concat(warning, verbose_name()));
            } else {
                ExVR.Log().warning(warning);
            }
        }

        public void log_error(string error, bool verbose = true) {
            if (verbose) {
                ExVR.Log().error(string.Concat(error, verbose_name()));
            } else {
                ExVR.Log().error(error);
            }
        }
    }

    public class ResourceFile : Resource{

        public string extension;

        public ResourceFile(int key, string alias, string path) : base(key, alias, path) {
            this.extension = Path.GetExtension(path);
        }
    }
}