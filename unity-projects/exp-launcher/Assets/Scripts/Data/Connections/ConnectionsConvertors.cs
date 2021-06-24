/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex{

    public class ConnectionsConvertors : MonoBehaviour{

        private Dictionary<string, Func<object, object>> convertors = null;

        public Func<object, object> get(string convertorStr) {
            if (convertors.ContainsKey(convertorStr)) {
                return convertors[convertorStr];
            }
            ExVR.Log().error("Convertor [" + convertorStr + "] doesn't exist.");
            return null;            
        }

        public void initialize() {

            // convertors
            convertors = new Dictionary<string, Func<object, object>>();
            // # from any to            
            convertors["any:id_any"]                = input => { return Converter.to_id_any(input); };
            convertors["any:string_any"]            = input => { return Converter.to_string_any(input); };
            convertors["any:bool"]                  = input => { return Converter.to_bool(input); };
            convertors["any:integer"]               = input => { return Converter.to_int(input); };
            convertors["any:float"]                 = input => { return Converter.to_float(input); };
            convertors["any:real"]                  = input => { return Converter.to_double(input); };
            convertors["any:string"]                = input => { return Converter.to_string(input); };
            convertors["any:vector2"]               = input => { return Converter.to_vector2(input); };
            convertors["any:vector3"]               = input => { return Converter.to_vector3(input); };
            convertors["any:transform"]             = input => { return Converter.to_transform(input); };
            convertors["any:decimal"]               = input => {return Converter.to_decimal(input); };
            convertors["any:list_string"]           = input => { return Converter.to_string_list(input); };            
            convertors["any:lm_frame"]              = input => { return (Leap.Frame)input; };
            convertors["any:lm_hands_frame"]        = input => { return (LeapMotionFrame)input; };
            convertors["any:kinect_body"]           = input => { return (KinectBodyData)input; };
            convertors["any:image"]                 = input => { return (ImageContainer)input; };
            convertors["any:real_list"]             = input => { return Converter.to_double_list(input); };            
            convertors["any:keyboard_button"]       = input => { return (Input.KeyboardButtonEvent)input; };
            convertors["any:joypad_button"]         = input => { return (Input.JoypadButtonEvent)input; };
            convertors["any:joypad_axis"]           = input => { return (Input.JoypadAxisEvent)input; };
            convertors["any:mouse_button"]          = input => { return (Input.MouseButtonEvent)input; };
            convertors["any:trigger"]               = input => { return null; };
            // # from trigger
            convertors["trigger:any"]               = input => { return 0; };
            // # from bool to 
            convertors["bool:integer"]              = input => { return Converter.to_int((bool)input); };
            convertors["bool:float"]                = input => { return Converter.to_float((bool)input); };
            convertors["bool:real"]                 = input => { return Converter.to_double((bool)input); };
            convertors["bool:decimal"]              = input => { return Converter.to_decimal((bool)input); };
            convertors["bool:string"]               = input => { return Converter.to_string((bool)input); };
            convertors["bool:any"]                  = input => { return input; };
            convertors["bool:trigger"]              = input => { return null; };
            // # from int to
            convertors["integer:bool"]              = input => { return Converter.to_bool((int)input); };
            convertors["integer:float"]             = input => { return Converter.to_float((int)input); };
            convertors["integer:real"]              = input => { return Converter.to_double((int)input); };
            convertors["integer:real_list"]         = input => { return Converter.to_double_list((int)input); };
            convertors["integer:decimal"]           = input => { return Converter.to_decimal((int)input); };
            convertors["integer:string"]            = input => { return Converter.to_string((int)input); };
            convertors["integer:any"]               = input => { return input; };
            convertors["integer:trigger"]           = input => { return null; };
            // # from float to 
            convertors["float:bool"]                = input => { return Converter.to_bool((float)input); };
            convertors["float:integer"]             = input => { return Converter.to_int((float)input); };
            convertors["float:real"]                = input => { return Converter.to_double((float)input); };
            convertors["float:real_list"]           = input => { return Converter.to_double_list((float)input); };
            convertors["float:decimal"]             = input => { return Converter.to_decimal((float)input); };
            convertors["float:string"]              = input => { return Converter.to_string((float)input); };
            convertors["float:any"]                 = input => { return input; };
            convertors["float:trigger"]             = input => { return null; };
            // # from real to 
            convertors["real:bool"]                 = input => { return Converter.to_bool((double)input); };
            convertors["real:integer"]              = input => { return Converter.to_int((double)input); };
            convertors["real:float"]                = input => { return Converter.to_float((double)input); };
            convertors["real:decimal"]              = input => { return Converter.to_decimal((double)input); };
            convertors["real:real_list"]            = input => { return Converter.to_double_list((double)input); };
            convertors["real:string"]               = input => { return Converter.to_string((double)input); };
            convertors["real:any"]                  = input => { return input; };
            convertors["real:trigger"]              = input => { return null; };
            // # from decimal to
            convertors["decimal:bool"]              = input => { return Converter.to_bool(input); };
            convertors["decimal:integer"]           = input => { return Converter.to_int((DecimalValue)input); };
            convertors["decimal:float"]             = input => { return Converter.to_float((DecimalValue)input); };
            convertors["decimal:real"]              = input => { return Converter.to_double((DecimalValue)input); };
            convertors["decimal:string"]            = input => { return Converter.to_string((DecimalValue)input); };
            convertors["decimal:real_list"]         = input => { return Converter.to_double_list((DecimalValue)input); };
            convertors["decimal:decimal_list"]      = input => { return Converter.to_decimal_list((DecimalValue)input); };
            convertors["decimal:any"]               = input => { return input; };
            convertors["decimal:trigger"]           = input => { return null; };
            // # from string to            
            convertors["string:string_list"]        = input => { return Converter.to_string_list((string)input); };
            convertors["string:any"]                = input => { return input; };           
            convertors["string:trigger"]            = input => { return null; };
            convertors["string:bool"]               = input => { return Converter.to_bool((string)input); };
            convertors["string:integer"]            = input => { return Converter.to_int((string)input); };
            convertors["string:real"]               = input => { return Converter.to_double((string)input); };
            // # from List<string> to                
            convertors["string_list:string"]        = input => { return Converter.to_string((List<string>)input); };
            convertors["string_list:any"]           = input => { return input; };
            convertors["string_list:trigger"]       = input => { return null; };
            // # from List<real> to
            convertors["real_list:any"]             = input => { return input; };
            convertors["real_list:trigger"]         = input => { return null; };
            // # from List<decimal> to
            convertors["decimal_list:any"]          = input => { return input; };
            convertors["decimal_list:trigger"]      = input => { return null; };
            // # from leap motion frame
            convertors["lm_frame:any"]              = input => { return input; };
            convertors["lm_frame:trigger"]          = input => { return null; };
            // # from leap motion hands frame
            convertors["lm_hands_frame:any"]        = input => { return input; };
            convertors["lm_hands_frame:trigger"]    = input => { return null; };            
            // from kinect body
            convertors["kinect_body:any"]           = input => { return input; };
            convertors["kinect_body:trigger"]       = input => { return null; };
            // # from image
            convertors["image:any"]                 = input => { return input; };
            convertors["image:trigger"]             = input => { return null; };
            // # from plot
            convertors["plot:any"]                  = input => { return input; };
            convertors["plot:trigger"]              = input => { return null; };
            // # from vector2
            convertors["vector2:any"]               = input => { return input; };
            convertors["vector2:trigger"]           = input => { return null; };
            convertors["vector2:string"]            = input => { return Converter.to_string((Vector2)input); };
            // # from vector3
            convertors["vector3:any"]               = input => { return input; };
            convertors["vector3:trigger"]           = input => { return null; };
            convertors["vector3:string"]            = input => { return Converter.to_string((Vector3)input); };
            // # from transform
            convertors["transform:any"]             = input => { return input; };
            convertors["transform:trigger"]         = input => { return null; };
            convertors["transform:string"]          = input => { return Converter.to_string((TransformValue)input); };
            // # from id any
            convertors["id_any:any"]                = input => { return input; };
            convertors["id_any:trigger"]            = input => { return null; };
            // # from string any
            convertors["string_any:any"]            = input => { return input; };
            convertors["string_any:trigger"]        = input => { return null; };
            // # from keyboard button state
            convertors["keyboard_button:any"]       = input => { return input; };
            convertors["keyboard_button:trigger"]   = input => { return null; };
            // # from mouse button state
            convertors["mouse_button:any"]          = input => { return input; };
            convertors["mouse_button:trigger"]      = input => { return null; };
            // # from joypad button state
            convertors["joypad_button:any"]         = input => { return input; };
            convertors["joypad_button:trigger"]     = input => { return null; };
            // # from joypad axis state
            convertors["joypad_button:any"]         = input => { return input; };
            convertors["joypad_button:trigger"]     = input => { return null; };
        }
    }
}
