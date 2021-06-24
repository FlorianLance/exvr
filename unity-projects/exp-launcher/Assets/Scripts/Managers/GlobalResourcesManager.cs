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

namespace Ex
{

    public class GlobalResourcesManager : MonoBehaviour
    {

        public enum ResourceType { Prefabs, Materials };

        private Dictionary<string, Material> m_loadedMaterials = null;
        private Dictionary<string, GameObject> m_loadedPrefabs = null;


        #region materials

        public bool material_exist(string path) {
            return m_loadedMaterials.ContainsKey(path);
        }

        public bool load_material(string pathMat) {

            if (material_exist(pathMat)) {
                Debug.LogError(string.Format("Material with path {0} already loaded.", pathMat));                
                return false;
            }

            var mat = Resources.Load(string.Format("Materials/{0}", pathMat)) as Material;
            if (mat == null) {
                Debug.LogError(string.Format("Cannot load material: {0}", pathMat));
                return false;
            }

            m_loadedMaterials[pathMat] = mat;
            return true;
        }

        public Material get_material(string pathMat) {
            if (!material_exist(pathMat)) {

                if (load_material(pathMat)) {
                    return m_loadedMaterials[pathMat] as Material;
                } else {
                    Debug.LogError(string.Format("Cannot get material with path: {0}", pathMat));
                    return null;
                }
            }

            return m_loadedMaterials[pathMat] as Material;
        }

        public Material instantiate_default_mat() {
            return instantiate_mat("DefaultModel");
        }

        public Material instantiate_default_transparent_mat() {
            return instantiate_mat("DefaultTransparentModel");
        }

        public Material instantiate_unlit_color_mat() {
            return instantiate_mat("UnlitColor");
        }

        public Material instantiate_mat(string pathMat) {

            var material = get_material(pathMat);
            if (material != null) {
                return Instantiate(material) as Material;
            }
            return null;
        }

        public Material instantiate_mat(Material material) {
            if (material == null) {
                Debug.LogError("Input material is null, cannot copy.");
                return null;
            }
            return Instantiate(material);
        }

        #endregion


        // prefabs
        private bool load_prefab(string pathPrefab) {

            var go = Resources.Load(string.Format("Prefabs/{0}", pathPrefab)) as GameObject;
            if (go == null) {
                ExVR.Log().error(string.Format("Failed to load prefab: {0}", pathPrefab));
                return false;
            }
            var storedPrefabResource = Instantiate(go);
            storedPrefabResource.SetActive(false);
            storedPrefabResource.transform.SetParent(transform);
            storedPrefabResource.name = string.Format("{0}_loaded_resource", go.name);
            m_loadedPrefabs[pathPrefab] = storedPrefabResource;
            return true;
        }

        public GameObject instantiate_prebab_without_storing(string pathPrefab, Transform parent = null, string newName = "") {

            var prefab = Resources.Load(string.Format("Prefabs/{0}", pathPrefab)) as GameObject;
            if (prefab == null) {
                ExVR.Log().error(string.Format("Failed to load prefab: {0}", pathPrefab));
                return null;
            }

            var go = Instantiate(prefab) as GameObject;
            if (parent != null) {
                go.transform.SetParent(parent);
            }

            go.layer = Layers.Default;
            if (go.GetComponent<RectTransform>() == null) {
                go.transform.localPosition = new Vector3(0, 0, 0);
                go.transform.localEulerAngles = new Vector3(0, 0, 0);
                go.transform.localScale = new Vector3(1, 1, 1);
            }

            if (newName.Length == 0) {
                go.name = pathPrefab;
            } else {
                go.name = newName;
            }

            go.SetActive(false);

            return go;
        }

        public GameObject instantiate_prebab(string pathPrefab, Transform parent = null, string newName = "") {

            if (!m_loadedPrefabs.ContainsKey(pathPrefab)) {
                if (!load_prefab(pathPrefab)) {
                    return null;
                }
            }

            var go = Instantiate(m_loadedPrefabs[pathPrefab]) as GameObject;
            if (parent != null) {
                go.transform.SetParent(parent);
            }

            go.layer = Layers.Default;
            if (go.GetComponent<RectTransform>() == null) {
                go.transform.localPosition = new Vector3(0, 0, 0);
                go.transform.localEulerAngles = new Vector3(0, 0, 0);
                go.transform.localScale = new Vector3(1, 1, 1);
            }

            if (newName.Length == 0) {
                go.name = pathPrefab;
            } else {
                go.name = newName;
            }

            go.SetActive(false);

            return go;
        }


        public void initialize() {

            // materials
            m_loadedMaterials = new Dictionary<string, Material>();
            load_material("DefaultModel");
            load_material("DefaultTransparentModel");
            load_material("UnlitColor");   

            // prefabs
            m_loadedPrefabs = new Dictionary<string, GameObject>();
        }

        //public void clean() {
        //    m_loadedMaterials.Clear();
        //    m_loadedPrefabs.Clear();
        //    load_material("DefaultModel");
        //    load_material("DefaultTransparentModel");
        //    load_material("UnlitColor");
        //}
    }
}