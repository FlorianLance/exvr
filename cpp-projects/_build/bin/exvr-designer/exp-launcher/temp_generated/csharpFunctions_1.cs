using System;
using System.Collections.Generic;
using UnityEngine;
 namespace Ex.CSharpFunctions { public class Camera_factor_settings { 
static CameraTargetComponent moveCameraWithOffset = ExVR.Components().get_from_name<CameraTargetComponent>("Move camera with offset"); 
static OBXComponent poc = ExVR.Components().get_csharp_script<OBXComponent>("Platform offset control");

static void set_factor(float factor){
	//	ExVR.Log().message("Factor " + factor);
	moveCameraWithOffset.set_factor(factor);
}public class move_plateform_up { 

 public static object function(object input) {
object output = null;

set_factor(poc.hexaCurrentFactor);

 
return output;
} 
}public class move_plateform_down { 

 public static object function(object input) {
object output = null;

set_factor(	1f - poc.hexaCurrentFactor);

 
return output;
} 
}
 }
}