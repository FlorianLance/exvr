/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.IO;
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex{


    public class PlotResource : ResourceFile{

        public List<AnimationCurve> curves = null;

        public PlotResource(int key, string alias, string path) : base(key, alias, path) {

            var ext = Path.GetExtension(path);
            if (ext == ".csv") {

                using (var reader = new StreamReader(path)) {

                    while (!reader.EndOfStream) {
                        var line = reader.ReadLine();
                        var values = line.Split(',');

                        if(values.Length < 2) {
                            // error
                            return;
                        }

                        if(curves == null) {
                            curves = new List<AnimationCurve>(values.Length-1);
                            for(int ii = 0; ii < values.Length - 1; ++ii) {
                                curves.Add(new AnimationCurve());
                            }
                        }

                        float time = Converter.to_float(values[0]);
                        for (int ii = 0; ii < values.Length - 1; ++ii) {
                            curves[ii].AddKey(time, Converter.to_float(values[ii + 1]));
                        }
                    }                    
                }
            }

            if (curves != null) {
                //foreach (var curve in curves) {
                //    UnityEngine.Debug.Log("curve " + curve.length);
                //}
            } else {
                ExVR.Log().error("Cannot load plot file: " + alias + " with path: " + path);
            }
        }
    }
}