/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;


// unity
using UnityEngine;

namespace Ex{

    public class GuiSettingsManager : MonoBehaviour{

        // display
        public DisplayManager.DisplayMode displayMode = DisplayManager.DisplayMode.Flat;
        public int stereoFov = 60;

        // network
        public int readingPort  = 0;
        public int writingPort  = 8196;

        // debug/exceptions
        public bool debug                       = true;
        public bool designerDebugBuild          = false;
        public bool csharpDebugInfo             = false;
        public bool catchComponentsExceptions   = false;

        // camera
        public bool enablePositionalTracking    = true;
        public bool useCameraXAxixAsNeutral     = false;
        public bool useCameraYAxixAsNeutral     = true;
        public bool useCameraZAxixAsNeutral     = false;

        // input
        public bool catchExternalKeyboardEvents = false;

        // editor
        public bool editor = false;

        public void initialize() {

#if UNITY_EDITOR
            editor = true;
#else
            editor = false;
#endif

            // globalization system
            System.Globalization.CultureInfo customCulture = (System.Globalization.CultureInfo)System.Threading.Thread.CurrentThread.CurrentCulture.Clone();
            customCulture.NumberFormat.NumberDecimalSeparator = ".";
            System.Threading.Thread.CurrentThread.CurrentCulture = customCulture;

            // init display mode from unity starting value (depends command line option)
            if (!editor) {
                var currentDevice = UnityEngine.XR.XRSettings.loadedDeviceName;
                if (currentDevice == "OpenVR") {
                    displayMode = DisplayManager.DisplayMode.OpenVR;
                } else {
                    displayMode = DisplayManager.DisplayMode.Flat;
                }

                read_command_line_arguments();

            }else{
                // force display mode for editor by using selected value
                ExVR.Display().change_display_mode(displayMode);
            }          
        }

        public void read_from_xml(XML.Settings settings) {
            
            // retrieve settings
            // # debug
            debug                       = settings.Debug;
            csharpDebugInfo             = settings.CSharpDebugInfo;
            catchComponentsExceptions   = settings.CatchComponentsExceptions;
            // # camera
            enablePositionalTracking    = settings.PositionalTracking;
            useCameraXAxixAsNeutral     = settings.Camera.CameraNeutralX;
            useCameraYAxixAsNeutral     = settings.Camera.CameraNeutralY;
            useCameraZAxixAsNeutral     = settings.Camera.CameraNeutralZ;
            catchExternalKeyboardEvents = settings.CatchExternalKeyboardEvents;
            // # display
            stereoFov                   = settings.Display.StereoFOV;
            displayMode                 = (DisplayManager.DisplayMode)settings.Display.Mode;

            // start/stop raw input events reading
            UnityRawInput.RawKeyInput.Stop();
            if (catchExternalKeyboardEvents) {
                UnityRawInput.RawKeyInput.Start(catchExternalKeyboardEvents);
            }

            // set debug display mode
            ExVR.Debug().displayExpInfos.set_debug_mode(debug);

            // change display mode
            ExVR.Display().change_display_mode(displayMode);            
        }

        public void OnDestroy() {
            UnityRawInput.RawKeyInput.Stop();
        }

        private bool read_command_line_arguments() {

            // gui mode
            // # read/write udp ports
            string[] arguments = Environment.GetCommandLineArgs();
            //foreach(var v in arguments) {
            //    Debug.LogError("v: " + v);
            //}

            if (arguments.Length >= 2) {

                writingPort = Int32.Parse(arguments[1]);
                readingPort = writingPort + 1;
                designerDebugBuild = UInt32.Parse(arguments[2]) == 1;
                return true;             
            } else {
                UnityEngine.Debug.LogError(string.Format("Invalid nb of arguments : {0}", arguments.Length));
            }

            return true;
        }
    }
}
