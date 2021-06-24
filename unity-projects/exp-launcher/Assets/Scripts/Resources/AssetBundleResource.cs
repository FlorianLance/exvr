/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{
    public class AssetBundleResource : ResourceFile{

        public AssetBundle bundle;

        public AssetBundleResource(int key, string alias, string path) : base(key, alias, path) {

            bundle = AssetBundle.LoadFromFile(path);
            if (bundle == null) {
                log_error("Failed to load AssetBundle with path: " + path);
            }
        }

        public override void clean() {
            bundle.Unload(true);
        }
    }
}