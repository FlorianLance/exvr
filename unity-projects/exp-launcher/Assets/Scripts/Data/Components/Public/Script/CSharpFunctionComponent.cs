
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Collections.Generic;
using System.Reflection;
using System.CodeDom.Compiler;

// unity
using UnityEngine;

namespace Ex{


    public class CSharpFunctionComponent : ExComponent {



        private static readonly string startPart = "namespace Ex{public class CSharpFunction{";
        private static readonly string startFunctionPart = "public static object function(object input){object output = null;";
        private static readonly string endPart = "return output;}}}";

        List<Assembly> assemblies = null;
        Dictionary<string, MethodInfo> methods = null;
        MethodInfo currentMethod = null;

        public static Assembly compile_assembly_from_text(string code) {

            Modified.Mono.CSharp.CSharpCodeCompiler provider = new Modified.Mono.CSharp.CSharpCodeCompiler();
            var param = new CompilerParameters();

            // add assemblies
            foreach (var assembly in AppDomain.CurrentDomain.GetAssemblies()) {
                if (assembly.GetName().Name != "Microsoft.GeneratedCode"
                    && assembly.GetName().Name != "Anonymously Hosted DynamicMethods Assembly") {
                    param.ReferencedAssemblies.Add(assembly.Location);
                }
            }

            // parameters
            param.GenerateExecutable = false;
            param.GenerateInMemory = true;
            param.IncludeDebugInformation = true;
            param.TreatWarningsAsErrors = false;

            // Compile the source            
            CompilerResults result = null;
            try {
                result = provider.CompileAssemblyFromSource(param, code);
            } catch (Exception ex) {
                ExVR.Log().error(string.Format("[COMPILER] Cannot compile csharp code: {0}", ex.Message), false);
            }

            if (result != null) {
                foreach (CompilerError error in result.Errors) {

                    string errorMsg = string.Format("[COMPILER] Compilation {0} {1} : \"{2}\" from file {3} at line {4} and column {5}",
                        error.IsWarning ? "warning " : "error ",
                        error.ErrorNumber,
                        error.ErrorText,
                        error.FileName,
                        error.Line,
                        error.Column
                    );

                    if (error.IsWarning) {
                        ExVR.Log().warning(errorMsg, false);
                    } else {
                        ExVR.Log().error(errorMsg, false);
                        return null;
                    }
                }
            } else {
                ExVR.Log().error("[COMPILER] CompileAssemblyFromFile crash", false);
                return null;
            }

            return result.CompiledAssembly;
        }

        protected override bool initialize() {

            // connections
            connections().add_slot("input", (input) => {
                invoke_signal("output", currentMethod.Invoke(null, new object[1] { input }));
            });
            connections().add_signal("output");            

            // generate assemblies
            assemblies = new List<Assembly>();
            methods = new Dictionary<string, MethodInfo>();
            var flagPublic = System.Reflection.BindingFlags.Static | System.Reflection.BindingFlags.Public;
            foreach (var config in configs) {
                var assembly = compile_assembly_from_text(string.Concat(startPart, config.get<string>("extra"), startFunctionPart, config.get<string>("function"), endPart));


                var runtimeType = assembly.GetType("Ex.CSharpFunction");
                if (runtimeType == null) {
                    log_error(string.Format("Cannot instantiate class Ex.CSharpFunction for config {0}", config.name));
                    return false;
                }

                var method = runtimeType.GetMethod("function", flagPublic);
                methods[config.name] = method;

                assemblies.Add(assembly);
            }           

            return true;
        }

        protected override void start_routine() {
            currentMethod = methods[currentC.name];
        }
    }
}

