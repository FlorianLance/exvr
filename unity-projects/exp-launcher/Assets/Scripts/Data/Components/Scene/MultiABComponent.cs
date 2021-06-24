
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Collections.Generic;
using System.Reflection;
// unity
using UnityEngine;


namespace Ex {

    public class MultiABComponent : ExComponent {

        private static readonly string[] assembliesNames = new string[] {
            ", UnityEngine",
            ", UnityEngine.UI",
            ", UnityEngine.Image",
            ", System",
            ", System.Collections",
            ", System.Collections.Generic"
        };

        private Dictionary<string, GameObject> bundles = null;
        private GameObject currentBundle = null;

        protected override bool initialize() {

            // slots
            add_slot("set visibility", (visibility) => { set_visibility((bool)visibility); });
            add_slot("set position", (position) => { set_position((Vector3)position); });
            add_slot("set rotation", (rotation) => { set_rotation((Vector3)rotation); });
            add_slot("set scale", (scale) => { set_scale((Vector3)scale); });
            // signals
            add_signal("visibility changed");

            var resources = initC.get_resources_asset_bundle_data_list("ab_list");
            bundles = new Dictionary<string, GameObject>(resources.Count);
            foreach (var resource in resources) {

                var bundle = ExVR.Resources().instantiate_asset_bundle(resource.alias, "", transform);
                if(bundle != null) {
                    instantiate_sub_components(bundle);
                    Debug.Log("add " + resource.alias);
                    bundles[resource.alias] = bundle;
                } else {
                    return false;
                }                
            }

            return true;
        }

        protected override void start_routine() {

            update_from_current_config();
            if(currentBundle == null) {
                log_error("Current alias resource is not available in resource list.");
            }
        }

        protected override void update_parameter_from_gui(XML.Arg arg) {
            reset_transform();
        }

        protected override void set_visibility(bool visibility) {

            foreach(var bundle in bundles) {
                bundle.Value.SetActive(false);
            }

            if(currentBundle != null) {
                currentBundle.SetActive(visibility);
            }
            
            invoke_signal("visibility changed", visibility);
        }

        // public 
        public override void update_from_current_config() {

            var alias = currentC.get_resource_alias("ab_alias");
            if (bundles.ContainsKey(alias)) {
                currentBundle = bundles[alias];
            } else {
                currentBundle = null;
            }
            
            set_visibility(is_visible());
            reset_transform();
        }

        public void set_position(Vector3 position) {
            if (currentBundle != null) {
                currentBundle.transform.localPosition = position;
            }
        }
        public void set_rotation(Vector3 rotation) {
            if (currentBundle != null) {
                currentBundle.transform.localEulerAngles = rotation;
            }
        }
        public void set_scale(Vector3 scale) {
            if (currentBundle != null) {
                currentBundle.transform.localScale = scale;
            }
        }

        public Vector3 position() {
            if (currentBundle != null) {
                return currentBundle.transform.localPosition;
            }
            return Vector3.zero;
        }

        public Vector3 rotation() {
            if (currentBundle != null) {
                return currentBundle.transform.localEulerAngles;
            }

            return Vector3.zero;
        }

        public Vector3 scale() {
            if (currentBundle != null) {
                return currentBundle.transform.localScale;
            }
            return Vector3.one;
        }

        public void reset_transform() {
            if (currentBundle != null) {
                currentC.update_transform("transform", currentBundle.transform, true);
            }
        }

        private void instantiate_sub_components(GameObject bundle) {

            // keep deleted components references to be added after when every component would have been regenerated
            List<GameObject> gameObjectsToEnable = new List<GameObject>();
            List<Tuple<UnityEngine.Component, FieldInfo, GameObject, string>> deletedComponentsToAdd = new List<Tuple<UnityEngine.Component, FieldInfo, GameObject, string>>();



            List<Tuple<Type, ComponentParametersToSet, Component>> allComponents = new List<Tuple<Type, ComponentParametersToSet, Component>>();
            foreach (var componentToInstantiate in bundle.GetComponentsInChildren<ComponentsToInstantiate>()) {

                var tr = componentToInstantiate.transform;

                // disable gameobject for avoiding Awake call just after component creation
                tr.gameObject.SetActive(false);
                gameObjectsToEnable.Add(tr.gameObject);

                // generate all components                
                foreach (var componentParameters in componentToInstantiate.components) {

                    Type typeComponent = Type.GetType(componentParameters.name);
                    if (typeComponent == null) {
                        typeComponent = Type.GetType(componentParameters.name + "," + componentParameters.assemblyFullName);
                        if (typeComponent == null) {

                            if (CSharpScriptResource.get_compiled_assembly() == null) {
                                Debug.LogError("No compiled assembly.");
                                continue;
                            }
                            typeComponent = CSharpScriptResource.get_type_from_compiled_assembly(componentParameters.name);
                            if (typeComponent == null) {
                                Debug.LogError("Cannot instantiate type " + componentParameters.name);
                                continue;
                            }
                        }
                    }

                    // generate component                    
                    allComponents.Add(new Tuple<Type, ComponentParametersToSet, Component>(typeComponent, componentParameters, tr.gameObject.AddComponent(typeComponent)));
                }
            }

            //generate parameters for each component
            foreach (var component in allComponents) {

                var typeComponent = component.Item1;
                var parametersToSet = component.Item2;
                var generatedComponent = component.Item3;

                // set parameters
                foreach (var parameter in parametersToSet.parameters) {

                    var varField = typeComponent.GetField(parameter.name);
                    if (varField == null) {
                        Debug.LogError("Variable " + parameter.name + " doesn't exist in component " + generatedComponent.name + " from GameObject " + generatedComponent.gameObject.name);
                        continue;
                    }

                    if (parameter.isArray) {

                        Type arrayType = Type.GetType(parameter.type + "," + parameter.fullAssemblyName);
                        Type elementType = arrayType.GetElementType();
                        if (elementType != null) {

                            var listType = typeof(List<>);
                            var constructedListType = listType.MakeGenericType(elementType);
                            var instance = Activator.CreateInstance(constructedListType);

                            var list = (System.Collections.IList)instance;
                            foreach (var subP in parameter.subParameters) {
                                var value = SceneConverter.deserialize(subP, CSharpScriptResource.get_compiled_assembly());
                                if (value != null) {
                                    list.Add(value);
                                }
                            }

                            Array y = Array.CreateInstance(elementType, list.Count);
                            list.CopyTo(y, 0);
                            varField.SetValue(generatedComponent, y);
                        } else {
                            Debug.LogError("INVALID TYPE: " + parameter.type + " " + parameter.fullAssemblyName);
                        }

                    } else if (parameter.isList) {


                        int startIndex = parameter.type.IndexOf('[') + 1;
                        int endIndex = parameter.type.LastIndexOf(']');
                        int length = endIndex - startIndex;
                        parameter.type = parameter.type.Substring(startIndex, length);

                        Type elementType = Type.GetType(parameter.type + ", " + parameter.fullAssemblyName);
                        if (elementType != null) {

                            var listType = typeof(List<>);
                            var constructedListType = listType.MakeGenericType(elementType);
                            var instance = Activator.CreateInstance(constructedListType);

                            var list = (System.Collections.IList)instance;
                            foreach (var subP in parameter.subParameters) {
                                var value = SceneConverter.deserialize(subP, CSharpScriptResource.get_compiled_assembly());
                                if (value != null) {
                                    list.Add(value);
                                }
                            }
                            varField.SetValue(generatedComponent, list);
                        } else {
                            Debug.LogError("INVALID TYPE: " + parameter.type + " " + parameter.fullAssemblyName);
                        }

                    } else {
                        object value = SceneConverter.deserialize(parameter, CSharpScriptResource.get_compiled_assembly());
                        if (value != null) {
                            varField.SetValue(generatedComponent, value);
                        } else {
                            Debug.LogError("CANNOT SET");
                        }
                    }
                }
            }

            // enable again associated gameobject to allow Awake call
            foreach (var go in gameObjectsToEnable) {
                Destroy(go.GetComponent<ComponentsToInstantiate>());
                go.SetActive(true);
            }
        }
    }

}