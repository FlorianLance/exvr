/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Collections.Generic;
using System.ComponentModel;


namespace Ex{

    public class Argument{

        // add static converters        
        public bool update_from_xml(XML.Arg xmlArg) {

            // get type
            xml  = xmlArg;
            type = Type.GetType(xmlArg.Type);
            if(type == null) {
                ExVR.Log().error("Can't read type from argument with name " + xml.Name);
                return false;
            }

            TypeConverter converter = TypeDescriptor.GetConverter(type);
            if (!converter.CanConvertFrom(typeof(string))) {
                return false;
            }

            switch (xmlArg.Dim) {
                case 0: {// one value
                        value = converter.ConvertFrom(xmlArg.Value);
                        return true;
                    }
                case 1: { // 1D array
                        if (xmlArg.Value.Length == 0) { 
                            value = new List<object>();
                            return true;
                        }
                        value = Converter.to_list(xmlArg.Value, xmlArg.Separator, converter);
                        var l = (List<object>)value;
                        if(l.Count != Converter.to_int(xmlArg.Sizes.Split(' ')[0])) {
                            value = new List<object>();
                            ExVR.Log().error("List size invalid for arg: " + xmlArg.Name + " -> " + l.Count + " " + xmlArg.Sizes[0]);
                        }
                        return true;
                    }
                case 2: { // 2D array
                        if (xmlArg.Value.Length == 0) {
                            return false;
                        }

                        string[] sizes = xmlArg.Sizes.Split(' ');
                        if(sizes.Length < 2) {
                            ExVR.Log().error("List 2D sizes invalid for arg: " + xmlArg.Name);
                            return false;
                        }

                        int rows = Converter.to_int(sizes[0]);
                        int cols = Converter.to_int(sizes[1]);
                        value = Converter.to_2D_list(xmlArg.Value, xmlArg.Separator, rows, cols, converter);
                        if(value == null) {
                            value = new List<List<object>>();
                            ExVR.Log().error("List 2D sizes invalid for arg: " + xmlArg.Name);
                            return false;
                        }
                                               
                        return true;
                    }
                default:
                    break;
            }

            return false;
        }

        public object value = null;
        public Type type    = null;
        public XML.Arg xml  = null;
    }
}