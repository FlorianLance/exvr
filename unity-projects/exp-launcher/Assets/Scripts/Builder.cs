
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex {

    public class ExVR {

        static public GoExplorer GO() {
            return Builder.autoRef.GO();
        }
        static public GuiSettingsManager GuiSettings() {
            return Builder.autoRef.guiSettingsManager;
        }

        static public DisplayManager Display() {            
            return Builder.autoRef.displayManager;
        }

        static public TimeManager Time() {
            return Builder.autoRef.timeManager;
        }

        static public PathsManager Paths(){
            return Builder.autoRef.pathsManager;
        }

        static public CoroutinesManager Coroutines() {
            return Builder.autoRef.coroutinesManager;
        }

        static public EventsManager Events() {
            return Builder.autoRef.eventsManager;
        }

        static public GlobalResourcesManager GlobalResources() {
            return Builder.autoRef.globalResourcesManager;
        }

        static public NetworkManager Network() {
            return Builder.autoRef.networkManager;
        }

        static public LoggerManager Logger() {
            return Builder.autoRef.loggerManager;
        }

        static public Log Log() {
            return Logger().log;
        }

        static public ExperimentLogger ExpLog() {
            return Logger().exp;
        }

        static public PythonManager Python() {
            return Builder.autoRef.pythonManager;
        }

        static public MemoryManager Memory() {
            return Builder.autoRef.memoryManager;
        }

        static public DebugManager Debug() {
            return Builder.autoRef.debugManager;
        }

        static public Experiment Experiment() {
            return Builder.autoRef.experiment;
        }

        static public Scheduler Scheduler() {
            return Experiment().schreduler;
        }

        static public Instance Instance() {
            return Scheduler().instance;
        }

        static public ResourcesManager Resources() {
            return Experiment().experimentResourcesManager;
        }        

        static public Components Components() {
            return Experiment().components;
        }

        static public Routines Routines() {
            return Experiment().routines;
        }

        static public ISIs ISIs() {
            return Experiment().ISIs;
        }
    }
}






namespace Ex{

    public class Builder : MonoBehaviour{

        public static Builder autoRef = null;
        public GoExplorer GO() { return go; }
        private GoExplorer go = null;

        [Header("Managers", order = 0)]
        [Rename("GUI settings")]
        public GuiSettingsManager guiSettingsManager = null;
        [Rename("Paths")]
        public PathsManager pathsManager = null;
        [Rename("VR")]
        public DisplayManager displayManager = null;
        [Rename("Coroutines")]
        public CoroutinesManager coroutinesManager = null;
        [Rename("Network")]
        public NetworkManager networkManager = null;
        [Rename("Events")]
        public EventsManager eventsManager = null;
        [Rename("Python")]
        public PythonManager pythonManager = null;
        [Rename("Logger")]
        public LoggerManager loggerManager = null;
        [Rename("Time")]
        public TimeManager timeManager = null;
        [Rename("Memory")]
        public MemoryManager memoryManager = null;
        [Rename("Debug")]
        public DebugManager debugManager = null;

        [Rename("Global resources")]
        public GlobalResourcesManager globalResourcesManager = null;

        [Header("Experiment content")]
        [Rename("Experiment")]
        public Experiment experiment = null;

        void Awake() {
            
#if EXVR
            Debug.Log("[EXVR-EXP]");
#else
            Debug.LogError("EXVR symbol not present.");
#endif
#if CLOSED_COMPONENTS
            Debug.Log("Closed components included.");
#endif
#if LNCO_COMPONENTS
            Debug.Log("LNCO components included.");
#endif
            autoRef = this; // for static access
            go      = GetComponent<GoExplorer>();

            // init managers
            // # time
            timeManager.start_program();
            // # setting            
            guiSettingsManager.initialize();
            // # paths
            pathsManager.initialize();
            // # events
            eventsManager.initialize();
            // # logger
            loggerManager.initialize();
            // # IPC
            ExVR.ExpLog().builder("Start IPC communication");
            networkManager.initialize();                        
            // # memory
            memoryManager.initialize();
            // # debug
            debugManager.initialize();

            // # global resources
            ExVR.ExpLog().builder("Initialize global resources");
            globalResourcesManager.initialize();
            // # graphics
            ExVR.ExpLog().builder("Initialize VR manager");
            displayManager.initialize();

            // # scripting            
            pythonManager.initialize();

            // config
            ConfigUtility.initialize();

            // init experiment
            ExVR.ExpLog().builder("Initialize experiment generator.");
            experiment.initialize();

            // indicates to the GUI that unity is ready
            ExVR.ExpLog().builder("Send ready signal to GUI.");
            networkManager.set_launcher_idle_state();
        }

        void OnApplicationQuit() {

            ExVR.Log().message(string.Format("Application ending after {0} seconds -> {1}", Time.time, GlobalVariables.wantToLeave), false);

            // force destroy experiment (mostly for C++DLL component to be clean correctly in Editor mode)
            ExVR.ExpLog().builder("Quit application");
            experiment.destroy_experiment();
                   
            ExVR.ExpLog().builder("Clean resources");
            ExVR.Resources().clean();

            ExVR.ExpLog().builder("Clean network communication");
            networkManager.clean();
            ExVR.ExpLog().write();
        }
    }
}


//Debug.LogError("UnityEngine.XR.XRSettings.loadedDeviceName " + UnityEngine.XR.XRSettings.loadedDeviceName);
//Debug.LogError("Screen.currentResolution " + Screen.currentResolution);
//Debug.LogError("Screen.fullScreen " + Screen.fullScreen);

//System.AppDomain.CurrentDomain.FirstChanceException += (sender, eventArgs) => {
//    Debug.LogError("[FirstChance]" + eventArgs.Exception.ToString());
//};
// UnityEngine.Debug.Log("QualitySettings.antiAliasing " + QualitySettings.antiAliasing);
// UnityEngine.Debug.Log("UnityEngine.XR.XRSettings.eyeTextureResolutionScale " + UnityEngine.XR.XRSettings.eyeTextureResolutionScale);



//static bool WantsToQuit() {
//    ExVR.Log().message("WantsToQuit");
//    Debug.Log("Player prevented from quitting.");
//    return GlobalVariables.wantToLeave;
//}

//void OnApplicationFocus() {
//    Debug.Log("FOCUS");
//}
//void OnDestroy() {
//    Debug.Log("DESTROY");
//    //ExVR.Log().message("DESTROY");
//}
//            if (!GlobalVariables.wantToLeave) {
//#if UNITY_EDITOR
//                UnityEditor.EditorApplication.isPlaying = true;
//#endif
//                return;
//            }

//private void OnDestroy(){
//    //UnityEngine.Debug.Break();
//    string str = UnityEngine.StackTraceUtility.ExtractStackTrace();
//    ExVR.Log().message("OnDestroy. " + str);
//    //experiment.destroy_experiment();
//}
//Application.wantsToQuit += () => {
//    ExVR.Log().message("Application wantsToQuit -> " + GlobalVariables.wantToLeave);                
//    return true;
//};
//Application.quitting += () => {
//    ExVR.Log().message("Application quiting");
//};

// companyName
// consoleLogPath
// dataPath
// isFocused
// isPlaying
// persistentDataPath
// systemLanguage
// streamingAssetsPath
// unityVersion
// version

