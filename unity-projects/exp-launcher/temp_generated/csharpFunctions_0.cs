using System;
using System.Collections.Generic;
using UnityEngine;
 namespace Ex.CSharpFunctions { public class CSharp_function { 
static KeyboardComponent keyboard = ExVR.Components().get_from_name<KeyboardComponent>("Keyboard");public class standard { 

 public static object function(object input) {
object output = null;
//var k = (Input.KeyboardButtonEvent)input;
var p = keyboard.buttonsState[KeyCode.Keypad4].is_pressed();
//ExVR.Log().message("pressed " + p); 
return output;
} 
}
 }
}