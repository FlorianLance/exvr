
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.IO;
using System.Collections.Generic;

// unity
using UnityEngine;

#if UNITY_EDITOR
using UnityEditor;
namespace Ex{

    [CustomEditor(typeof(Ex.ResourcesManager), true)]
    public class ResourcesManagerEditor : Editor{

        public override void OnInspectorGUI() {

            if (!Application.isPlaying) {
                return;
            }

            Ex.ResourcesManager manager = (Ex.ResourcesManager)target;
            EditorGUILayout.LabelField("### Resources per type:");
            foreach (Ex.ResourcesManager.ResourceType r in Enum.GetValues(typeof(Ex.ResourcesManager.ResourceType))) {

                var resources = manager.get_resources_from_type(r);
                if(resources.Count > 0) {
                    EditorGUILayout.LabelField(String.Format("{0} -> count: {1}", r.ToString(), resources.Count));
                    foreach(var resource in resources) {
                        EditorGUILayout.LabelField(String.Format("\t[{0}] [{1}] ({2}) ", resource.alias, resource.path, resource.key));
                    }
                }
            }
        }
    }
}
#endif

namespace Ex { 

    public class ResourcesManager : MonoBehaviour {

        public enum ResourceType : int {  
            Audio = 1, Image = 2, Mesh = 4, Text = 8, Video = 16, 
            UnityAssetBundle = 32, CSharpScript = 64, PythonScript = 128, Cloud = 256,
            ScanerVideo = 512, Plot = 1024, Directory = 2048
        };

        public void log_message(string message) {
            ExVR.Log().message(string.Format("[RESOURCE] {0}", message));
        }

        public void log_warning(string warning) {
            ExVR.Log().warning(string.Format("[RESOURCE] {0}", warning));
        }

        public void log_error(string error) {
            ExVR.Log().error(string.Format("[RESOURCE] {0}", error));
        }

        private Dictionary<ResourceType, Dictionary<string, Resource>> m_pathMappingResources = null; // type - path -> resource        
        private Dictionary<ResourceType, Dictionary<string, Resource>> m_aliasMappingResources = null; // type - alias -> resource

        public List<Resource> get_resources_from_type(ResourceType type) {
            List<Resource> resources = new List<Resource>(m_pathMappingResources[type].Count);
            foreach(var resource in m_pathMappingResources[type]) {
                resources.Add(resource.Value);
            }
            return resources;
        }

        public void initialize() {

            // init dictionnaries
            m_pathMappingResources = new Dictionary<ResourceType, Dictionary<string, Resource>>();
            m_aliasMappingResources = new Dictionary<ResourceType, Dictionary<string, Resource>>();
            foreach (ResourceType type in Enum.GetValues(typeof(ResourceType))) {
                m_pathMappingResources[type]    = new Dictionary<string, Resource>();
                m_aliasMappingResources[type]   = new Dictionary<string, Resource>();
            }

            // add defaults
            add_default_resources();
        }

        public void add_default_resources() {

            // images
            var dImage = new ImageResource(-1, "default_texture", "");
            dImage.read_data();
            dImage.initialize();
            dImage.doNotRemove = true;
            m_aliasMappingResources[ResourceType.Image]["default_texture"] = dImage;
            // ...
        }

        public void clean() {

            foreach(var resourcesType in m_aliasMappingResources) {
                foreach (var resource in resourcesType.Value) {
                    resource.Value.clean();
                }
            }
        }

        private Resource generate_resource(ResourceType type, int key, string alias, string path) {

            // resource file exists
            switch (type) {
                case ResourceType.Image:               
                    return new ImageResource(key, alias, path);
                case ResourceType.Text:
                    return new TextResource(key, alias, path);
                case ResourceType.UnityAssetBundle:
                    return new AssetBundleResource(key, alias, path);
                case ResourceType.Video:
                    return new VideoResource(key, alias, path);
                case ResourceType.Audio:
                    return new AudioResource(key, alias, path);
                case ResourceType.CSharpScript:
                    return new CSharpScriptResource(key, alias, path);
                case ResourceType.Cloud:
                    return new CloudResource(key, alias, path);
                case ResourceType.ScanerVideo:
                    return new ScanerVideoResource(key, alias, path);
                case ResourceType.Plot:
                    return new PlotResource(key, alias, path);
                case ResourceType.Directory:
                    return new DirectoryResource(key, alias, path);
            }
            return null;
        }


        private bool parallel_add_resources_from_xml(List<XML.Resource> resources) {

            List<Resource> loadedResources = new List<Resource>();

            // init dictionnaries
            foreach (var resource in resources) {

                if (!Path.IsPathRooted(resource.Path)) {
                    resource.Path = Path.GetFullPath(ExVR.Paths().designerDataTempDir + "/" + resource.Path);
                }

                var type = (ResourceType)Enum.Parse(typeof(ResourceType), resource.Type);
                bool exists = (type == ResourceType.Directory) ? Directory.Exists(resource.Path) : File.Exists(resource.Path);
                if (!exists) {
                    log_error(String.Format("Cannot load resource file of type [{0}] with path: {1})", resource.Type, resource.Path));
                    return false;
                }

                // init resource if not mapped                
                if (!m_pathMappingResources[type].ContainsKey(resource.Path)) {
                    Resource resourceData = generate_resource(type, resource.Key, resource.Alias, resource.Path);
                    m_pathMappingResources[type][resource.Path]   = resourceData;
                    m_aliasMappingResources[type][resource.Alias] = resourceData;
                    loadedResources.Add(resourceData);
                }
            }

            // parallel resources loading
            System.Threading.Tasks.Parallel.ForEach(loadedResources, resource => {
                resource.read_data();
            });
            foreach(var resource in loadedResources) {
                resource.initialize();
            }

            return true;
        }

        private bool add_resource_from_xml(XML.Resource resource, ResourceType type) {

            if (!Path.IsPathRooted(resource.Path)) {
                resource.Path = Path.GetFullPath(ExVR.Paths().designerDataTempDir + "/" + resource.Path);
            }

            bool exists = (type == ResourceType.Directory) ? Directory.Exists(resource.Path) : File.Exists(resource.Path);
            if (!exists) {
                log_error(String.Format("Cannot load resource file of type [{0}] with path: {1})", resource.Type, resource.Path));
                return false;
            }

            // load resource if not mapped
            if (!m_pathMappingResources[type].ContainsKey(resource.Path)) {                

                Resource resourceData = generate_resource(type, resource.Key, resource.Alias, resource.Path);
                if (resourceData != null) {
                    m_pathMappingResources[type][resource.Path] = resourceData;
                    m_aliasMappingResources[type][resource.Alias] = resourceData;
                    resourceData.read_data();
                    resourceData.initialize();
                }
            }

            return true;
        }

        public void generate_from_xml(XML.Experiment xmlExperiment) {

            XML.Resources xmlResources = xmlExperiment.Resources;

            // fill dictionnay for commodity
            var resources = new Dictionary<ResourceType, Dictionary<string, XML.Resource>>();
            foreach (var resource in xmlResources.Resource) {
                var type = (ResourceType)Enum.Parse(typeof(ResourceType), resource.Type);
                if (!resources.ContainsKey(type)) {
                    resources[type] = new Dictionary<string, XML.Resource>();
                }
                resources[type][resource.Path] = resource;
            }

            // look for resources not available anymore
            List<Tuple<ResourceType, string, Resource>> resourcesToRemove = new List<Tuple<ResourceType, string, Resource>>();
            foreach(var mappingPerType in m_pathMappingResources) {
                foreach(var resource in mappingPerType.Value) {

                    // look for resource in dictionnaries
                    bool found = false;
                    if (resources.ContainsKey(mappingPerType.Key)){
                        if (resources[mappingPerType.Key].ContainsKey(resource.Key)) {
                            found = true;
                        }
                    }
                    
                    // if not found remove from it
                    if (!found) {
                        resourcesToRemove.Add(new Tuple<ResourceType, string, Resource>(mappingPerType.Key, resource.Key, resource.Value));
                    }
                }
            }

            // remove theses resources
            foreach(var resource in resourcesToRemove) {                
                m_aliasMappingResources[resource.Item1].Remove(resource.Item3.alias);
                m_pathMappingResources[resource.Item1].Remove(resource.Item2);
                resource.Item3.clean();
            }

            // clean resources depending reload code
            foreach (ResourceType type in Enum.GetValues(typeof(ResourceType))) {

                // check reload code
                if((xmlResources.ReloadCode & (int)type) == 0) {
                    continue;
                }

                // clean data
                List<Resource> resourcesToKeep = new List<Resource>();
                foreach (var bundle in m_aliasMappingResources[type]) {
                    if (!bundle.Value.doNotRemove) {
                        bundle.Value.clean();
                    } else {
                        resourcesToKeep.Add(bundle.Value);
                    }
                }    

                // remove from dictionnary
                m_pathMappingResources[type].Clear();
                m_aliasMappingResources[type].Clear();

                // add again non removables resources in dictionnaries
                foreach(Resource resourceToKeep in resourcesToKeep) {
                    m_aliasMappingResources[type][resourceToKeep.alias] = resourceToKeep;
                }
            }

            // C# scripts resources
            // ### retrieve c# scripts resources load them
            List<XML.Resource> cSharpSriptResources = new List<XML.Resource>();
            foreach (var resource in xmlResources.Resource) {
                var type = (ResourceType)Enum.Parse(typeof(ResourceType), resource.Type);
                if(type == ResourceType.CSharpScript) {
                    cSharpSriptResources.Add(resource);
                    add_resource_from_xml(resource, type);
                }                
            }

            // ###  remove c# scripts resources from main resources list
            foreach (var resource in cSharpSriptResources) {
                xmlResources.Resource.Remove(resource);
            }

            // ###  compile/recompile scripts
            if ((xmlResources.ReloadCode & (int)ResourceType.CSharpScript) != 0) {

                List<string> scriptsFiles = new List<string>();

                // retrieve resources scripts
                foreach (var csharpData in m_pathMappingResources[ResourceType.CSharpScript]) {
                    scriptsFiles.Add(csharpData.Value.path);
                }

                // retrieve ui functions scripts                
                foreach (var tempFile in CSharpFunctionComponent.generate_files_from_scripts_functions(xmlExperiment.Components)) {
                    scriptsFiles.Add(tempFile);
                }

                // compile assembly from scripts
                CSharpScriptResource.compile_assembly_from_scripts_files(scriptsFiles.ToArray());                    
            }

            // others resources
            //parallel_add_resources_from_xml(xmlResources.Resource); // mostly useless
            foreach (var resource in xmlResources.Resource) {
                // get type from string
                var type = (ResourceType)Enum.Parse(typeof(ResourceType), resource.Type);
                if (!add_resource_from_xml(resource, type)) {
                    continue;
                }
            }
        }

        public Resource get_resource_file_data(int key) {

            foreach(var resourcesPerType in m_aliasMappingResources) {
                foreach(var resource in resourcesPerType.Value) {
                    if(resource.Value.key == key) {
                        return resource.Value;
                    }
                }
            }

            log_error(String.Format("Cannot read resource with key [{0}] from resources.", key));
            return null;
        }

        public Resource get_resource_file_data(ResourceType type, int key) {

            foreach (var resource in m_aliasMappingResources[type]) {
                if(resource.Value.key == key) {
                    return resource.Value;
                }
            }
            log_error(String.Format("Cannot read resource with key [{0}] and type [{1}] from resources.", key, type.ToString()));
            return null;
        }

        public Resource get_resource_file_data(ResourceType type, string alias) {
            if (!m_aliasMappingResources[type].ContainsKey(alias)) {
                log_error(String.Format("Cannot read resource with alias [{0}] and type [{1}] from resources.", alias, type.ToString()));
                return null;
            }
            return m_aliasMappingResources[type][alias];
        }

        public ScanerVideoResource get_scaner_video_file_data(string alias) {
            if (!m_aliasMappingResources[ResourceType.ScanerVideo].ContainsKey(alias)) {
                log_error(String.Format("Cannot read scaner video with alias [{0}] from resources.", alias ));
                return null;
            }
            return ((ScanerVideoResource)m_aliasMappingResources[ResourceType.ScanerVideo][alias]);
        }

        public CloudResource get_cloud_file_data(string alias) {
            if (!m_aliasMappingResources[ResourceType.Cloud].ContainsKey(alias)) {
                log_error(String.Format("Cannot read cloud with alias [{0}] from resources.", alias));
                return null;
            }
            return ((CloudResource)m_aliasMappingResources[ResourceType.Cloud][alias]);
        }

        public TextResource get_text_file_data(string alias, bool showError = true) {
            if (!m_aliasMappingResources[ResourceType.Text].ContainsKey(alias)) {
                if (showError) {
                    log_error(String.Format("Cannot read text with alias [{0}] from resources.", alias));
                }
                return null;
            }
            return ((TextResource)m_aliasMappingResources[ResourceType.Text][alias]);
        }
        public AudioResource get_audio_file_data(string alias) {
            if (!m_aliasMappingResources[ResourceType.Audio].ContainsKey(alias)) {
                log_error(String.Format("Cannot read audio with alias [{0}] from resources.", alias));
                return null;
            }
            return ((AudioResource)m_aliasMappingResources[ResourceType.Audio][alias]);
        }

        public VideoResource get_video_file_data(string alias) {
            if (!m_aliasMappingResources[ResourceType.Video].ContainsKey(alias)) {
                log_error(String.Format("Cannot read video with alias [{0}] from resources.", alias));
                return null;
            }
            return ((VideoResource)m_aliasMappingResources[ResourceType.Video][alias]);
        }

        public PlotResource get_plot_file_data(string alias) {
            if (!m_aliasMappingResources[ResourceType.Plot].ContainsKey(alias)) {
                log_error(String.Format("Cannot read plot with alias [{0}] from resources.", alias));
                return null;
            }
            return ((PlotResource)m_aliasMappingResources[ResourceType.Plot][alias]);
        }

        public ImageResource get_image_file_data(string alias) {
            if (!m_aliasMappingResources[ResourceType.Image].ContainsKey(alias)) {
                log_error(String.Format("Cannot read image with alias [{0}] from resources.", alias));
                return null;
            }
            return ((ImageResource)m_aliasMappingResources[ResourceType.Image][alias]);
        }

        public AssetBundleResource get_asset_bundle_file_data(string alias) {
            if (!m_aliasMappingResources[ResourceType.UnityAssetBundle].ContainsKey(alias)) {
                log_error(String.Format("Cannot read asset bundle with alias [{0}] from resources.", alias));
                return null;
            }
            return ((AssetBundleResource)m_aliasMappingResources[ResourceType.UnityAssetBundle][alias]);
        }


        public GameObject instantiate_asset_bundle(string alias, string nameSubObject, Transform parent = null) {

            var assetBundle = get_asset_bundle_file_data(alias);
            if(assetBundle == null) {
                return null;
            }

            GameObject assets;
            if(nameSubObject.Length == 0) {
                Debug.Log("-> " + assetBundle.bundle.GetAllAssetNames()[0]);
                assets = assetBundle.bundle.LoadAsset<GameObject>(assetBundle.bundle.GetAllAssetNames()[0]);
            } else {
                assets = assetBundle.bundle.LoadAsset<GameObject>(nameSubObject);                
            }
            
            // load asset from asset bundle
            if (assets == null) {
                log_error(String.Format("Sub object [{0}] doesn't exist in loaded AssetBundle with alias: {1}", nameSubObject, alias));
                System.Threading.Thread.Sleep(50);
                return null;
            }

            // instantiate gameobject from assets
            var go = Instantiate(assets) as GameObject;
            if (parent != null) {
                go.transform.SetParent(parent);
            }            
            go.layer = Layers.Default;

            // force layer option ?
            foreach(Transform child in go.transform.GetComponentInChildren<Transform>()) {
                child.gameObject.layer = Layers.Default;
            }

            if (go.GetComponent<RectTransform>() == null) {
                go.transform.localPosition = new Vector3(0, 0, 0);
                go.transform.localEulerAngles = new Vector3(0, 0, 0);
                go.transform.localScale = new Vector3(1, 1, 1);
            }

            go.name = nameSubObject.Length == 0 ? alias : nameSubObject;
            go.SetActive(false);

            return go;
        }
    }
}
