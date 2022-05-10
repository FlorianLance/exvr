
/***********************************************************************************
** exvr-exp                                                                       **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

// system
using System;
using System.Collections.Generic;
using System.ComponentModel;


namespace Ex{

    public class Argument{

        public object value = null;
        public Type type = null;
        public XML.Arg xml = null;

        // add static converters        
        public bool update_from_xml(XML.Arg xmlArg) {

            // get type
            xml  = xmlArg;
            type = Type.GetType(xmlArg.Type);
            if(type == null) {
                ExVR.Log().error(string.Format("Can't read type [{0}] from argument.", xmlArg.Type));
                return false;
            }

            // get converter
            TypeConverter converter = TypeDescriptor.GetConverter(type);
            if (!converter.CanConvertFrom(typeof(string))) {
                return false;
            }

            if(xmlArg.Dim == 0) { // one value
                value = converter.ConvertFrom(xmlArg.Value);
            } else if(xmlArg.Dim == 1) { // 1D array
                if (xmlArg.Value.Length != 0) {

                    string[] splitArg = Ex.Text.split(xmlArg.Value, xmlArg.Separator);
                    List<object> argList1D = new List<object>(splitArg.Length);
                    foreach (string split in splitArg) {
                        argList1D.Add(converter.ConvertFrom(split));
                    }

                    if (argList1D.Count != Converter.to_int(Ex.Text.split(xmlArg.Sizes, ' ')[0])) {
                        value = new List<object>();
                        ExVR.Log().warning(string.Format("List size inconsistency for arg with name [{0}] -> [{1} {2}]", 
                            xmlArg.Name, argList1D.Count, xmlArg.Sizes[0]));
                    } else {
                        value = argList1D;
                    }
                    
                } else {
                    value = new List<object>();
                }

            } else if(xmlArg.Dim == 2) { // 2D array

                string[] sizes = Ex.Text.split(xmlArg.Sizes, ' ');
                if (sizes.Length < 2) {
                    ExVR.Log().error(string.Format("List 2D sizes invalid for argument with name [{0}] and value [{1}]",
                        xml.Name, xml.Value));
                    return false;
                }

                if (xmlArg.Value.Length != 0) {

                    int rows = Converter.to_int(sizes[0]);
                    int cols = Converter.to_int(sizes[1]);

                    string[] splitArg = Ex.Text.split(xmlArg.Value, xmlArg.Separator);
                    List<List<object>> argList2D = new List<List<object>>(rows);
                    if (splitArg.Length != rows * cols) {
                        ExVR.Log().error(string.Format("List 2D sizes invalid for argument with name {0} and value {1}", xml.Name, xml.Value));
                        return false;
                    }

                    int id = 0;
                    for (int ii = 0; ii < rows; ++ii) {
                        argList2D.Add(new List<object>(cols));
                        for (int jj = 0; jj < cols; ++jj) {
                            argList2D[ii].Add(converter.ConvertFrom(splitArg[id++]));
                        }
                    }

                    value = argList2D;

                } else {
                    value = new List<List<object>>();
                }

            } else {
                ExVR.Log().error(string.Format("Cannot convert arg with name [{0}] and value [{1}], nb of dimensions [{2}] not managed. ", xmlArg.Name, xmlArg.Value, xmlArg.Dim));
                return false;
            }

            return true;
        }
    }
}
