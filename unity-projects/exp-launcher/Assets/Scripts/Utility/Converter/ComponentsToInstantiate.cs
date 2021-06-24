
// system
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex
{

    [System.Serializable]
    public class SubParameterToSet
    {
        public string name = "";
        public string type = "";
        public string fullAssemblyName = "";
        public string strValue = "";

        public MonoBehaviour mono = null;
        public GameObject gameObject = null;
        public Component component = null;

        public bool isDeletedComponent = false;
        public string deletedComponentTypeName = "";
    }

    [System.Serializable]
    public class ParameterToSet
    {

        public string name = "";
        public string type = "";
        public string fullAssemblyName = "";
        public string strValue = "";

        public MonoBehaviour mono = null;
        public GameObject gameObject = null;
        public Component component = null;

        public bool isDeletedComponent = false;
        public string deletedComponentTypeName = "";

        public bool isArray = false;
        public bool isList = false;
        public List<SubParameterToSet> subParameters = null;

        public SubParameterToSet to_sub() {
            SubParameterToSet sub = new SubParameterToSet();
            sub.name = name;
            sub.type = type;
            sub.fullAssemblyName = fullAssemblyName;
            sub.strValue = strValue;
            sub.mono = mono;
            sub.gameObject = gameObject;
            sub.component = component;
            sub.isDeletedComponent = isDeletedComponent;
            sub.deletedComponentTypeName = deletedComponentTypeName;
            return sub;
        }
    }

    [System.Serializable]
    public class ComponentParametersToSet
    {
        public string name;
        public string assemblyFullName;
        public string args;
        public List<ParameterToSet> parameters = new List<ParameterToSet>();
    }

    [System.Serializable]
    public class ComponentsToInstantiate : MonoBehaviour
    {
        public List<ComponentParametersToSet> components = new List<ComponentParametersToSet>();
    }
}