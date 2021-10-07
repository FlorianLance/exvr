
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.IO;
using System.Text;
using System.Collections.Generic;
using System.Reflection;

namespace Ex {

    public class CSharpFunctionComponent : ExComponent {

        public static readonly string[] charsToRemove = new string[] { "@", ",", ".", ";", "'", "{", "}", "(", ")", "[", "]", " ", "-" };

        public static readonly string startClassStr = "namespace Ex.CSharpFunctions { public class {0} { {1} ";
        public static readonly string configStr = "public class {0} { {1} public static object function(object input) {object output = null; {2} return output;} }";
        public static readonly string endClassStr = "}}";

        private static string generate_code(string className, string initConfigExtraContent, List<string> configsName, List<string> condConfigsFunctionContent, List<string> condConfigsExtraContent) {

            StringBuilder b = new StringBuilder();
            b.Append("using System;\nusing System.Collections.Generic;\nusing UnityEngine;\n");
            b.Append(" namespace Ex.CSharpFunctions { public class ");
            b.Append(className);
            b.Append(" { \n");
            b.Append(initConfigExtraContent);
            for (int ii = 0; ii < configsName.Count; ++ii) {
                b.Append("public class ");
                b.Append(configsName[ii]);
                b.Append(" { \n");
                b.Append(condConfigsExtraContent[ii]);
                b.Append("\n public static object function(object input) {\nobject output = null;\n");
                b.Append(condConfigsFunctionContent[ii]);
                b.Append(" \nreturn output;\n} \n}");
            }
            b.Append("\n }\n}");
            return b.ToString();
        }

        private static List<string> generate_temp_files_from_source_batch(string baseName, List<string> sources) {

            List<string> fileNames = new List<string>(sources.Count);
            for (int ii = 0; ii < sources.Count; ++ii) {
                fileNames.Add(ExVR.Paths().expLauncherTempGeneratedDir + "/" + baseName + "_" + ii + ".cs");
                if (File.Exists(fileNames[ii])) {
                    File.Delete(fileNames[ii]);
                }
                FileStream f = new FileStream(fileNames[ii], FileMode.CreateNew);
                using (StreamWriter s = new StreamWriter(f, Encoding.UTF8)) {
                    s.Write(sources[ii]);
                    s.Close();
                }
                f.Close();
            }

            return fileNames;
        }


        public static List<string> generate_files_from_scripts_functions(XML.Components componentsXML) {

            

            List<string> csharpFunctionsComponentsCode = new List<string>();
            foreach (var component in componentsXML.Component) {
                if (component.Type == "CSharpFunction") {

                    string initConfigExtraContent = "";
                    List<string> configs = new List<string>();
                    List<string> condConfigsFuncContent = new List<string>();
                    List<string> condConfigsExtraContent = new List<string>();

                    foreach (var arg in component.InitConfig.Arg) {
                        if (arg.Name == "extra") {
                            initConfigExtraContent = arg.Value;
                            break;
                        }
                    }

                    foreach (var config in component.Configs.Config) {

                        string configName = config.Name;
                        foreach (var c in charsToRemove) {
                            configName = configName.Replace(c, "_");
                        }

                        configs.Add(configName);
                        foreach (var arg in config.Arg) {
                            if (arg.Name == "function") {
                                condConfigsFuncContent.Add(arg.Value);
                                continue;
                            }
                            if (arg.Name == "extra") {
                                condConfigsExtraContent.Add(arg.Value);
                                continue;
                            }
                        }
                    }
                    
                    var componentName = component.Name;
                    foreach (var c in charsToRemove) {
                        componentName = componentName.Replace(c, "_");
                    }

                    csharpFunctionsComponentsCode.Add(CSharpFunctionComponent.generate_code(componentName,initConfigExtraContent, configs, condConfigsFuncContent, condConfigsExtraContent)); ;
                }
            }

            return generate_temp_files_from_source_batch("csharpFunctions", csharpFunctionsComponentsCode);
        }

        Dictionary<string, MethodInfo> methods = null;
        MethodInfo currentMethod = null;


        protected override bool initialize() {

            // connections
            connections().add_slot("input", (input) => {
                invoke_signal("output", currentMethod.Invoke(null, new object[1] { input }));
            });
            connections().add_signal("output");


            string className = name;
            foreach (var c in charsToRemove) {
                className = className.Replace(c, "_");
            }

            // retrieve type
            var assembly = CSharpScriptResource.get_compiled_assembly();
            if (assembly == null) {
                log_error(string.Concat("No assembly available, cannot instantiate class Ex.CSharpFunctions.", className));
                return false;
            }


            var flagPublic = System.Reflection.BindingFlags.Static | System.Reflection.BindingFlags.Public;
            methods = new Dictionary<string, MethodInfo>();
            foreach (var config in configs) {

                string configName = config.name;
                foreach (var c in charsToRemove) {
                    configName = configName.Replace(c, "_");
                }

                // get nested class using '+'
                var configClassName = string.Format("Ex.CSharpFunctions.{0}+{1}", className, configName);
                var runtimeType = assembly.GetType(configClassName);
                if (runtimeType == null) {
                    log_error(string.Concat("Cannot instantiate class ", configClassName));
                    return false;
                }

                var method = runtimeType.GetMethod("function", flagPublic);
                methods[config.name] = method;
            }

            return true;
        }

        protected override void start_routine() {
            currentMethod = methods[currentC.name];
        }
    }
}

