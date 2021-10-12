using System;
using System.Collections.Generic;
using UnityEngine;
 namespace Ex.CSharpFunctions { public class Set_camera_settings { 
static CameraTargetComponent t1 = ExVR.Components().get_from_name<CameraTargetComponent>("Camera target 1"); 
static CameraTargetComponent t2 = ExVR.Components().get_from_name<CameraTargetComponent>("Camera target 2");

static OBXComponent poc = ExVR.Components().get_csharp_script<OBXComponent>("Platform offset control");


static void set_factor(float factor){
//	ExVR.Log().message("Factor " + factor);
	t1.set_factor(factor);
	t2.set_factor(factor);
}public class cStatic_pUp { 

 public static object function(object input) {
object output = null;

float factor = poc.currentFactor;
set_factor(poc.currentFactor);
//t1.offset = Vector3.zero;//-poc.diffV;
//t2.offset = -poc.diffV;

 
return output;
} 
}public class cUp_pDown { 

 public static object function(object input) {
object output = null;


float factor = 1f - poc.currentFactor;
set_factor(factor);
//t1.offset = poc.diffV;


//t2.offset = Vector3.zero;//-poc.diffV;

 
return output;
} 
}public class cDown_pUp { 

 public static object function(object input) {
object output = null;

float factor = poc.currentFactor;
set_factor(factor);

 
return output;
} 
}public class move_down { 

 public static object function(object input) {
object output = null;

set_factor(	1f - poc.currentFactor);

 
return output;
} 
}public class move_up { 

 public static object function(object input) {
object output = null;

set_factor(poc.currentFactor);

 
return output;
} 
}public class cStatic_pDown { 

 public static object function(object input) {
object output = null;


set_factor(	1f - poc.currentFactor); 
return output;
} 
}public class cUp_pUp { 

 public static object function(object input) {
object output = null;

set_factor(poc.currentFactor); 
return output;
} 
}public class cDown_pDown { 

 public static object function(object input) {
object output = null;


set_factor(	1f - poc.currentFactor);



 
return output;
} 
}
 }
}