/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex{

    public class PlotResourceComponent : ExComponent{

        public List<AnimationCurve> curves = null;
        private PlotResource data = null;

        protected override bool initialize() {
            add_signal("plot loaded");
            add_signal("plot loaded alias");
            add_signal("plot loaded path");
            return true;
        }

        protected override void start_routine() {
            load_plot();            
            if (data != null) {
                invoke_signal("plot loaded", curves[0]);
                invoke_signal("plot loaded alias", data.alias);
                invoke_signal("plot loaded path", data.path);
            }
        }

        protected override void update_parameter_from_gui(XML.Arg arg) {
            if (arg.Name == "plot") {
                load_plot();
            }
        }

        private void load_plot() {

            if (currentC.get<bool>("random")) {
                var plots = currentC.get_resources_plot_data_list("plots_list");
                if (plots.Count > 0) {
                    data = plots[Random.Range(0, plots.Count - 1)];
                }
            } else {
                data = currentC.get_resource_plot_data("plot");
            }

            curves = new List<AnimationCurve>();            
            if (data != null) {
                foreach(var plot in data.curves) {
                    curves.Add(plot);
                }
            } else {
                // load default                
                curves.Add(new AnimationCurve());                
                // ...
            }
        }
    }
}