
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Reflection;
using System.CodeDom.Compiler;

// unity
using UnityEngine;



namespace Ex
{


    public class CSharpFunctionComponent : ExComponent
    {

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

            string firstPart = "namespace Ex{public class TestCode{public static object foo(object value){object result = null;";
            string codePart = initC.get<string>("code");// "UnityEngine.Debug.Log(\"OK!\");";
            string lastPart = "return result;}}}";
            var assembly = compile_assembly_from_text(firstPart + codePart + lastPart);


            var runtimeType = assembly.GetType(string.Concat("Ex.TestCode"));
            if (runtimeType == null) {
                log_error(string.Concat("Cannot instantiate class Ex.TestCode"));
                return false;
            }

            var flagPublic = System.Reflection.BindingFlags.Static | System.Reflection.BindingFlags.Public;
            var method = runtimeType.GetMethod("foo", flagPublic);
            //var function = (runtimeType.GetMethod("foo", flagPublic).DeclaringType == runtimeType);

            object[] parameters = new object[1] { 0f };
            var a = method.Invoke(null, parameters);

            return true;
        }
    }
}

