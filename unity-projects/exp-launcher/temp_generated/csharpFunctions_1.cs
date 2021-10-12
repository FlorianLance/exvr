using System;
using System.Collections.Generic;
using UnityEngine;
 namespace Ex.CSharpFunctions { public class Set_camera_settings { 
static CameraTargetComponent t1 = ExVR.Components().get_from_name<CameraTargetComponent>("Camera target 1"); 
static CameraTargetComponent t2 = ExVR.Components().get_from_name<CameraTargetComponent>("Camera target 2");

static OBXComponent poc = ExVR.Components().get_csharp_script<OBXComponent>("Platform offset control");


static void set_factor(float factor){
	// 	ExVR.Log().message("Factor " + factor);
	t1.set_factor(factor);
	t2.set_factor(factor);
}public class move_up { 

 public static object function(object input) {
object output = null;

set_factor(poc.currentFactor); 
return output;
} 
}public class move_down { 

 public static object function(object input) {
object output = null;

set_factor(	1f - poc.currentFactor);

 
return output;
} 
}public class cStatic_pDown { 

 public static object function(object input) {
object output = null;

/**
set_cam_values(
	"cStatic_pDown",
	-poc.diffV,

);
*/

set_factor(	1f - poc.currentFactor); 
return output;
} 
}public class cDown_pUp { 

 public static object function(object input) {
object output = null;
// Start:
// obx factor: 0
// obx diff: 0

// cam factor: 0
// cam offset: 0


// 	poc.currentFactor*(-poc.diffV),

/**
set_cam_values(
	"cDown_pUp",
	Vector3.zero,//poc.currentFactor*(-poc.diffV),
	poc.currentFactor
);
*/

set_factor(poc.currentFactor);

// End:
// obx factor: 1
// obx diff: 0.415

// cam factor: 1
// cam offset: -0.415 
return output;
} 
}public class cStatic_pUp { 

 public static object function(object input) {
object output = null;

// Start:
// obx factor: 0
// obx diff: 0

// cam factor: 0
// cam offset: -0

/**
set_cam_values(
	"cStatic_pUp",
	-poc.diffV,
	poc.currentFactor
);
*/

set_factor(poc.currentFactor);


// End:
// obx factor: 1
// obx diff: 0.415

// cam factor: 1
// cam offset: -0.415 
return output;
} 
}public class cUp_pDown { 

 public static object function(object input) {
object output = null;

// Start:
// obx factor: 1
// obx diff: 0.415

// cam factor: 0
// cam offset: 0

//	-poc.diffV + (poc.currentFactor * poc.diffV),
/**
set_cam_values(
	"cUp_pDown",
	Vector3.zero,//-poc.diffV,// + (poc.currentFactor * poc.diffV),
	1f-poc.currentFactor
);
*/

set_factor(	1f - poc.currentFactor);

// End:
// obx factor: 0
// obx diff: 0

// cam factor: 1
// cam offset: 0 
return output;
} 
}public class cUp_pUp { 

 public static object function(object input) {
object output = null;

/**
set_cam_values(
	"cUp_pUp",
	(1f-poc.currentFactor)*poc.diffV,
	poc.currentFactor
);
*/
set_factor(poc.currentFactor); 
return output;
} 
}public class cDown_pDown { 

 public static object function(object input) {
object output = null;

/**
set_cam_values(
	"cDown_pDown",
	(1f-poc.currentFactor)*poc.diffV,
	1f-poc.currentFactor
);
*/

set_factor(	1f - poc.currentFactor);



 
return output;
} 
}
 }
}