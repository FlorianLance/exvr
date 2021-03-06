/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Collections.Generic;

// unity
using UnityEngine;

#if UNITY_EDITOR
using UnityEditor;
namespace Ex{

    [CustomEditor(typeof(Config),true)]
    public class ConfigEditor : Editor{

        public override bool RequiresConstantRepaint() {
            return true;
        }

        public override void OnInspectorGUI() {

            if (!Application.isPlaying) {
                return;
            }

            Config config = (Config)target;

            var win = Screen.width;
            var w1 = win * 0.25f;
            var w2 = win * 0.25f;
            var w3 = win * 0.25f;
            var w4 = win * 0.25f;

            EditorGUILayout.LabelField("All args: ");
            GUILayout.BeginHorizontal();
            GUILayout.Label("Name", GUILayout.Width(w1));
            GUILayout.Label("Type", GUILayout.Width(w2));
            GUILayout.Label("Value", GUILayout.Width(w3));
            GUILayout.Label("Array", GUILayout.Width(w4));
            GUILayout.EndHorizontal();

            foreach (var pair in config.args) {

                GUILayout.BeginHorizontal();
                if (pair.Value.xml == null) {
                    GUILayout.Label("(-) " + pair.Key, GUILayout.Width(w1));
                    GUILayout.Label(pair.Value.type.ToString(), GUILayout.Width(w2));
                    GUILayout.Label(Converter.to_string(pair.Value.value), GUILayout.Width(w3));

                } else { 
                    
                    GUILayout.Label(pair.Key, GUILayout.Width(w1));
                    GUILayout.Label(pair.Value.type.ToString(), GUILayout.Width(w2));
                    GUILayout.Label(Converter.to_string(pair.Value.value), GUILayout.Width(w3));
                    if (pair.Value.xml.Dim > 0) {
                        GUILayout.Label("[d=" + pair.Value.xml.Dim + "][s=" + pair.Value.xml.Sizes + "][s=" + pair.Value.xml.Separator + "]", GUILayout.Width(w4));
                    }                    
                }

                GUILayout.EndHorizontal();
            }

        }
    }
}
#endif



namespace Ex {

    public static class ConfigUtility{

        public static Dictionary<string, TMPro.TextAlignmentOptions> textAlignment = null;

        public static void initialize() {

            if (textAlignment == null) {
                textAlignment = new Dictionary<string, TMPro.TextAlignmentOptions>();
                textAlignment["Middle left"] = TMPro.TextAlignmentOptions.BaselineLeft;
                textAlignment["Middle right"] = TMPro.TextAlignmentOptions.BaselineRight;
                textAlignment["Middle justified"] = TMPro.TextAlignmentOptions.BaselineJustified;
                textAlignment["Middle centered"] = TMPro.TextAlignmentOptions.BaselineGeoAligned;
                textAlignment["Bottom left"] = TMPro.TextAlignmentOptions.BottomLeft;
                textAlignment["Bottom right"] = TMPro.TextAlignmentOptions.BottomRight;
                textAlignment["Bottom justified"] = TMPro.TextAlignmentOptions.BottomJustified;
                textAlignment["Bottom centered"] = TMPro.TextAlignmentOptions.BottomGeoAligned;
                textAlignment["Top left"] = TMPro.TextAlignmentOptions.TopLeft;
                textAlignment["Top right"] = TMPro.TextAlignmentOptions.TopRight;
                textAlignment["Top justified"] = TMPro.TextAlignmentOptions.TopJustified;
                textAlignment["Top centered"] = TMPro.TextAlignmentOptions.TopGeoAligned;
            }
        }
    }

    public class Config : MonoBehaviour{

        public int key;
        public string keyStr;
        public Dictionary<string, Argument> args = null;


        public void log_error(string error, bool verbose = true) {
            if (verbose) {
                ExVR.Log().error(string.Format("From config {0}:{1} -> {2}", name, key, error));
            } else {
                ExVR.Log().error(error);
            }           
        }

        // contains

        public bool has(string argName) {
            return args.ContainsKey(argName);
        }
        
        public Argument get(string argName) {

            if (!has(argName)) {
                log_error(string.Format("Argument {0}  doesn't exist.", argName));
                return null;
            }
            return args[argName];
        }

        public T get<T>(string argName){

            Argument arg = get(argName);
            if(arg == null) {
                return default(T);
            }

            try {
                return (T)arg.value;
            } catch (System.InvalidCastException) {
                log_error(string.Format("Cannot cast argument {0} of type {1}:{2} of value {3}", argName, typeof(T).ToString(), args[argName].xml.Type, args[argName].xml.Value));
            }

            return default(T);
        }

        public void get<T>(string argName, ref T value) {
            value = get<T>(argName);
        }

        public void get(string argName, ref Color value) {
            if (has(argName)) {
                value = Converter.to_color((List<object>)args[argName].value);
            } else {
                value = Color.black;
                log_error(string.Format("Argument {0} of type Color doesn't exist.", argName));
            }
        }

        public void get(string argName, ref Vector2 value) {
            if (has(argName)) {
                value = Converter.to_vector2((List<object>)args[argName].value);
            } else {
                value = Vector2.zero;
                log_error(string.Format("Argument {0} of type Vector2 doesn't exist.", argName));
            }
        }

        public void get(string argName, ref Vector3 value) {
            if (has(argName)) {
                value = Converter.to_vector3((List<object>)args[argName].value);
            } else {
                value = Vector3.zero;
                log_error(string.Format("Argument {0} of type Vector3 doesn't exist.", argName));
            }
        }

        public void get(string argName, ref DecimalValue value) {
            if (has(argName)) {
                value = Converter.to_decimal(args[argName].value);
            } else {
                value = new DecimalValue(0);
                log_error(string.Format("Argument {0} of type DecimalValue doesn't exist.", argName));
            }
        }

        // get only if exists
        public void get_if_exists<T>(string argName, ref T value) {
            if (has(argName)) {
                value = get<T>(argName);
            }
        }

        public void get_if_exists(string argName, ref Color value) {
            if (has(argName)) {
                value = Converter.to_color((List<object>)args[argName].value);
            }
        }

        public void get_if_exists(string argName, ref Vector2 value) {
            if (has(argName)) {
                value = Converter.to_vector2((List<object>)args[argName].value);
            }
        }

        public void get_if_exists(string argName, ref Vector3 value) {
            if (has(argName)) {
                value = Converter.to_vector3((List<object>)args[argName].value);
            }
        }

        public void get_if_exists(string argName, ref DecimalValue value) {
            if (has(argName)) {
                value = Converter.to_decimal(args[argName].value);
            }
        }


        // resources    
        public List<AssetBundleResource> get_resources_asset_bundle_data_list(string argName) {

            List<AssetBundleResource> resources = new List<AssetBundleResource>();
            if (!has(argName)) {
                log_error(string.Format("Argument {0} of type Asset bundle doesn't exist.", argName));
                return resources;
            }

            var split = ((List<object>)args[argName].value);
            foreach (var keyStr in split) {
                int key = Converter.to_int((string)keyStr);
                var resourceData = ExVR.Resources().get_resource_file_data(ResourcesManager.ResourceType.UnityAssetBundle, key);
                if (resourceData != null) {
                    resources.Add((AssetBundleResource)(resourceData));
                }
            }
            return resources;
        }


        public List<PlotResource> get_resources_plot_data_list(string argName) {

            List<PlotResource> resources = new List<PlotResource>();
            if (!has(argName)) {
                log_error(string.Format("Argument {0} of type PlotResource doesn't exist.", argName));
                return resources;
            }

            var split = ((List<object>)args[argName].value);
            foreach (var keyStr in split) {
                int key = Converter.to_int((string)keyStr);
                var resourceData = ExVR.Resources().get_resource_file_data(ResourcesManager.ResourceType.Plot, key);
                if (resourceData != null) {
                    resources.Add((PlotResource)(resourceData));
                }
            }
            return resources;
        }

        // # alias
        public string get_resource_alias(string argName) {

            if (!has(argName)) {
                log_error(string.Format("Argument {0} doesn't exist.", argName));
                return "";
            }

            var split = ((List<object>)args[argName].value);
            if (split.Count == 2) {
                return (string)split[0];
            }
            return "";
        }

        // # resource data
        public AudioResource get_resource_audio_data(string argName) {
            string audioAlias = get_resource_alias(argName);
            if (audioAlias.Length == 0) {
                return null;
            }
            return ExVR.Resources().get_audio_file_data(audioAlias);
        }

        public PlotResource get_resource_plot_data(string argName) {
            string plotAlias = get_resource_alias(argName);
            if (plotAlias.Length == 0) {
                return null;
            }
            return ExVR.Resources().get_plot_file_data(plotAlias);
        }

        public ImageResource get_resource_image_data(string argName) {
            string imageAlias = get_resource_alias(argName);
            if (imageAlias.Length == 0) {
                return null;
            }
            return ExVR.Resources().get_image_file_data(imageAlias);
        }

        public TextResource get_resource_text_data(string argName) {
            string textAlias = get_resource_alias(argName);
            if (textAlias.Length == 0) {
                return null;
            }
            return ExVR.Resources().get_text_file_data(textAlias);
        }

        public VideoResource get_resource_video_data(string argName) {
            string videoAlias = get_resource_alias(argName);
            if (videoAlias.Length == 0) {
                return null;
            }
            return ExVR.Resources().get_video_file_data(videoAlias);
        }

        public AssetBundleResource get_resource_asset_bundle_data(string argName) {
            string assetBundleAlias = get_resource_alias(argName);
            if (assetBundleAlias.Length == 0) {
                return null;
            }
            return ExVR.Resources().get_asset_bundle_file_data(assetBundleAlias);
        }

        // # resource sub data
        public string get_resource_path(ResourcesManager.ResourceType type, string argName) {
            string alias = get_resource_alias(argName);
            if (alias.Length == 0) {
                return "";
            }
            return ExVR.Resources().get_resource_file_data(type, alias).path;
        }

        public Texture2D get_resource_image(string argName, bool returnDefaultIfNull = true) {

            var data = get_resource_image_data(argName);
            if(data == null) {
                if (returnDefaultIfNull) {
                    return ExVR.Resources().get_image_file_data("default_texture").texture;
                } else {
                    return null;
                }
            }
            return data.texture;
        }

        public string get_resource_text(string argName) {

            string txtAlias = get_resource_alias(argName);
            if (txtAlias.Length == 0) {
                return "text_not_found";
            }
            return ExVR.Resources().get_text_file_data(txtAlias).content;
        }

        // components
        public T get_component<T>(string argName)  where T : ExComponent {

            if (!has(argName)) {
                log_error(string.Format("Argument {0} doesn't exist.", argName));
                return null;
            }

            var split = ((List<object>)args[argName].value);
            if (split.Count == 2) {
                string nameStr = (string)split[0];
                string idStr   = (string)split[1];
                int key = Converter.to_int(idStr);
                if(key == -1) {
                    return null;
                }
                return (T)ExVR.Components().get_from_key(key);
            }
            return null;
        }

        public Tuple<Routine, Condition, ExComponent,ComponentConfig> get_component_config(string argName){

            if (!has(argName)) {
                log_error(string.Format("Argument {0} doesn't exist.", argName));
                return null;
            }

            var split = ((List<object>)args[argName].value);
            if (split.Count == 6) {

                Condition condition = null;
                Routine routine = ExVR.Routines().get((string)split[2]);
                if(routine != null) {
                    condition = routine.get_condition_from_name((string)split[3]);
                }

                int componentKey = Converter.to_int((string)split[4]);
                int configKey    = Converter.to_int((string)split[5]);
                if (componentKey == -1 || configKey == -1) {
                    log_error("Invalid component/config key.");
                    return null;
                }
                ExComponent component = ExVR.Components().get_from_key(componentKey);
                if(component != null) {
                    ComponentConfig config = component.get_config(configKey);
                    if (config != null) {
                        return new Tuple<Routine, Condition, ExComponent, ComponentConfig>(routine, condition, component, config);
                    } else {
                        log_error(string.Format("Cannot find config from key {0} in component {1}", config, component.name));
                    }
                } else {
                    log_error(string.Format("Cannot find component from key {0}", componentKey));
                }
                
            }
            return null;
        }


        public List<T> get_components_list<T>(string argName) where T : ExComponent {

            List<T> components = new List<T>();
            if (!has(argName)) {
                log_error(string.Format("Argument {0} of type ComponentsList doesn't exist.", argName));
                return components;
            }

            var split = ((List<object>)args[argName].value);
            foreach(var keyStr in split) {
                int key = Converter.to_int((string)keyStr);
                var component = ExVR.Components().get_from_key(key);
                if(component != null) {
                    components.Add((T)(component));
                }
            }
            return components;
        }

        // others types
        public DecimalValue get_decimal(string argName) {
            if (!has(argName)) {
                log_error(string.Format("Argument {0} of type DecimalValue doesn't exist.", argName));
                return new DecimalValue();
            }
            return Converter.to_decimal(args[argName].value);
        }

        public List<T> get_list<T>(string argName) {
            if (!has(argName)) {
                log_error(string.Format("Argument {0} of type List doesn't exist.", argName));
                return new List<T>();
            }
            return Converter.to_list<T>(args[argName].value);
        }

        public Color get_color(string argName) {

            if (!has(argName)) {
                log_error(string.Format("Argument {0} of type Color doesn't exist.", argName));
                return new Color(0f, 0f, 0f);
            }
            return Converter.to_color((List<object>)args[argName].value);
        }

        public Vector2 get_vector2(string argName) {

            if (!has(argName)) {
                log_error(string.Format("Argument {0} of type Vector2 doesn't exist.", argName));
                return new Vector2(0f, 0f);
            }
            return Converter.to_vector2((List<object>)args[argName].value);
        }

        public Vector3 get_vector3(string argName) {

            if (!has(argName)) {
                log_error(string.Format("Argument {0} of type Vector3 doesn't exist.", argName));
                return new Vector3(0f, 0f, 0f);
            }
            return Converter.to_vector3((List<object>)args[argName].value);
        }
        public Vector3 get_vector3_with_order(string argName, Converter.AxisOrder order = Converter.AxisOrder.PitchYawRoll) {

            if (!has(argName)) {
                log_error(string.Format("Argument {0} of type Vector3 doesn't exist.", argName));
                return new Vector3(0f, 0f, 0f);
            }
            return Converter.to_vector3((List<object>)args[argName].value, order);
        }

        public TransformValue get_transform(string argName, Converter.AxisOrder order = Converter.AxisOrder.PitchYawRoll) {

            if (!has(argName)) {
                log_error(string.Format("Argument {0} of type Transform doesn't exist.", argName));
                return new TransformValue();
            }
            return Converter.to_transform(args[argName].value, order);
        }

        public void update_transform(string argName, Transform transform, bool local = true, bool position = true, bool rotation = true, bool scale = true) {

            if (!has(argName)) {
                log_error(string.Format("Argument {0} of type Transform doesn't exist.", argName));
                return;
            }
            Converter.apply_to_transform(args[argName].value, transform, local, position, rotation, scale);
        }

        public AnimationCurve get_curve(string argName) {

            if (!has(argName)) {
                log_error(string.Format("Argument {0} of type AnimationCurve doesn't exist.", argName));
                return new AnimationCurve();
            }                        
            return Converter.to_curve(get_list<float>(argName));
        }

        public void update_text(string baseArgName, TMPro.TextMeshProUGUI text) {

            string argName = baseArgName + "_text_resource";
            if (has(argName)) { // check if contain text input
                string textAlias = get_resource_alias(argName);
                if (textAlias.Length == 0) {
                    text.SetText(get<string>(baseArgName + "_text"));
                } else {
                    text.SetText(ExVR.Resources().get_text_file_data(textAlias).content);
                }
                text.richText = get<bool>(baseArgName + "_rich_text");
            }

            // set font style
            var fontStyle = TMPro.FontStyles.Normal;
            if (get<bool>(baseArgName + "_bold")) {
                fontStyle |= TMPro.FontStyles.Bold;
            }
            if (get<bool>(baseArgName + "_italic")) {
                fontStyle |= TMPro.FontStyles.Italic;
            }
            if (get<bool>(baseArgName + "_highlight")) {
                fontStyle |= TMPro.FontStyles.Highlight;
            }
            if (get<bool>(baseArgName + "_lower_case")) {
                fontStyle |= TMPro.FontStyles.LowerCase;
            }
            if (get<bool>(baseArgName + "_upper_case")) {
                fontStyle |= TMPro.FontStyles.UpperCase;
            }
            if (get<bool>(baseArgName + "_under_line")) {
                fontStyle |= TMPro.FontStyles.Underline;
            }
            text.fontStyle = fontStyle;

            // set font size
            text.fontSize = get<float>(baseArgName + "_font_size");
            text.enableAutoSizing = get<bool>(baseArgName + "_auto_size");
            text.enableWordWrapping = get<bool>(baseArgName + "_wrap");

            // alignment
            text.alignment = ConfigUtility.textAlignment[get<string>(baseArgName + "_alignment")];

            // colors
            //text.color = get_color(baseArgName + "_color");
            text.faceColor = get_color(baseArgName + "_face_color");

            // ouline         
            text.outlineColor = get_color(baseArgName + "_outline_color");
            text.outlineWidth = get<float>(baseArgName + "_outline_width");

            // spacing
            text.paragraphSpacing = get<float>(baseArgName + "_paragraph_spacing");
            text.lineSpacing = get<float>(baseArgName + "_line_spacing");
            text.wordSpacing = get<float>(baseArgName + "_word_spacing");
            text.characterSpacing = get<float>(baseArgName + "_character_spacing");

            // check if input font exists in list
            // if not do nothing
            // else CreateDynamicFontFromOSFont

            //TMP_FontAsset;
            //Font f = Resources.Load("Fonts/OTF/bimasakti") as Font;
            ////
            //// Résumé :
            ////     Get names of fonts installed on the machine.
            ////
            //// Retourne :
            ////     An array of the names of all fonts installed on the machine.
            //public static string[] GetOSInstalledFontNames();
            ////
            //// Résumé :
            ////     Gets the file paths of the fonts that are installed on the operating system.
            ////
            //// Retourne :
            ////     An array of the file paths of all fonts installed on the machine.
            //public static string[] GetPathsToOSFonts();

            //public static Font CreateDynamicFontFromOSFont(string fontname, int size);

            //Resources.GetBuiltinResourcke(typeof(Font), "Arial.ttf");
            // TrueType Fonts (.ttf files) and OpenType Fonts (.otf files).
            // font 
            //m_text.font = TMP_FontAsset.CreateFontAsset(new Font(currentC.get<string>("font_name")));
            //public bool isRightToLeftText { get; set; }
        }

        // setters
        public void init_or_set<T>(string argName, T value) {
            if (has(argName)) {
                set(argName, value);
            } else {
                add(argName, value);
            }
        }
        public void add<T>(string argName, T value) {

            if (has(argName)) {
                log_error(string.Format("Argument {0} of type {1} already exists.", argName, typeof(T).ToString()));
                return;
            }
            args[argName] = new Argument();
            args[argName].value = value;
            args[argName].type = typeof(T);
        }

        public void set<T>(string argName, T value) {
            if (!has(argName)) {
                log_error(string.Format("Argument {0} of type {1} doesn't exist in config.", argName, typeof(T).ToString()));
                return;
            }
            args[argName].value = value;
        }

        public void set_vector2(string argName, Vector2 value) {
            set(argName, Converter.to_list(value));
        }

        public void set_vector3(string argName, Vector3 value) { 
            set(argName, Converter.to_list(value));
        }

        public void set_transform(string argName, Transform transform, bool local = false) {
            set(argName, Converter.to_list(transform, local));
        }

        public void set_transform(string argName, TransformValue transform) {
            set(argName, Converter.to_list(transform));
        }

        public void set_transform(string argName, List<Vector3> transform) {
            set(argName, Converter.to_list(transform));
        }
        public void set_color(string argName, Color color) {
            set(argName, Converter.to_list(color));
        }

        public void set_list<T>(string argName, List<T> values) {

            List<object> elements = new List<object>(values.Count);
            foreach (T value in values) {
                elements.Add(value);
            }
            set(argName, elements);
        }

        // # alias
        //public void set_resource_alias(string argName, string resourceAlias) {


            //if (!has(argName)) {
            //    log_error(string.Format("Argument {0} doesn't exist.", argName));
            //    return "";
            //}

            //var split = ((List<object>)args[argName].value);
            //if (split.Count == 2) {
            //    return (string)split[0];
            //}
            //return "";
        //}


        // xml
        public bool update_from_xml(XML.Arg xmlArg) {

            // get the name from its id
            if (!has(xmlArg.Name)) {
                log_error(string.Format("Argument {0} doesn't exist.", xmlArg.Name));
                return false;
            }

            // convert xml to arg
            if (!args[xmlArg.Name].update_from_xml(xmlArg)) {
                log_error(string.Format("Cannot update argument {0} with value {1}.", xmlArg.Name, xmlArg.Value));
                return false;
            }

            return true;
        }

        public void init_from_xml(XML.Arg xmlArg) {

            args = new Dictionary<string, Argument>(1);
            Argument arg = new Argument();
            if (!arg.update_from_xml(xmlArg)) {
                log_error(string.Format("Cannot initialize argument {0} with value {1}.", xmlArg.Name, xmlArg.Value));
            }
            args[xmlArg.Name] = arg;
        }

        public void init_from_xml(List<XML.Arg> xmlArgs) {

            args = new Dictionary<string, Argument>(xmlArgs.Count);
            foreach (XML.Arg xmlArg in xmlArgs) {
                Argument arg = new Argument();
                if (!arg.update_from_xml(xmlArg)) {
                    log_error(string.Format("Cannot initialize argument {0} with value {1}.", xmlArg.Name,xmlArg.Value));
                }
                args[xmlArg.Name] = arg;
            }
        }
    }

    public class ComponentInitConfig : Config{

        public void initialize(XML.InitConfig initConfig) {
            name = "init";
            init_from_xml(initConfig.Arg);
            key = initConfig.Key;
            keyStr = Converter.to_string(key);
        }
    }

    public class ComponentConfig : Config{

        public void initialize(XML.Config config) {
            name = config.Name;
            init_from_xml(config.Arg);
            key = config.Key;
            keyStr = Converter.to_string(key);
        }
    }
}