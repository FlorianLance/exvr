/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/



namespace Ex{

    public class VideoSaverComponent : CppComponent {

        protected override bool initialize() {

            // init dll
            cppDll = new DLL.VideoSaver();
            cppDll.parent = this;

            // init slots
            add_slot("add frame", (image) => {
                ((DLL.VideoSaver)cppDll).add_frame((ImageContainer)image);
            });

            return cppDll.initialize();
        }
    }
}