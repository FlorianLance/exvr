using System;
using System.Collections.Generic;
using UnityEngine;
 namespace Ex.CSharpFunctions { public class Set_camera_settings { 
static CameraTargetComponent t1 = ExVR.Components().get_from_name<CameraTargetComponent>("Camera target 1"); 
static CameraTargetComponent t2 = ExVR.Components().get_from_name<CameraTargetComponent>("Camera target 2");
static CameraTargetComponent t3 = ExVR.Components().get_from_name<CameraTargetComponent>("Camera target 3");

static OBXComponent poc = ExVR.Components().get_csharp_script<OBXComponent>("Platform offset control");

static void set_cam_values(string config, Vector3 offset, float factor){
	string txt = config;
	txt += " Offset: " + Converter.to_string(offset);
	txt += " Factor " + factor;
	ExVR.Log().message(txt);
	set_offset(offset);
	set_factor(factor);
}

static void set_offset(Vector3 offset){
	t1.set_offset(offset);
	t2.set_offset(offset);
	t3.set_offset(offset);
}

static void set_factor(float factor){
	t1.set_factor(factor);
	t2.set_factor(factor);
	t3.set_factor(factor);
}public class cStatic_pDown { 

 public static object function(object input) {
object output = null;

set_cam_values(
	"cStatic_pDown",
	-poc.diffV,
	1f - poc.currentFactor
); 
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

set_cam_values(
	"cDown_pUp",
	poc.currentFactor*(-poc.diffV),
	poc.currentFactor
);

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

set_cam_values(
	"cStatic_pUp",
	-poc.diffV,
	poc.currentFactor
);


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

set_cam_values(
	"cUp_pDown",
	-poc.diffV + (poc.currentFactor * poc.diffV),
	1f-poc.currentFactor
);

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

set_cam_values(
	"cUp_pUp",
	poc.currentFactor*poc.diffV,
	poc.currentFactor
);
 
return output;
} 
}public class cDown_pDown { 

 public static object function(object input) {
object output = null;


set_cam_values(
	"cDown_pDown",
	(1f-poc.currentFactor)*poc.diffV,
	1f-poc.currentFactor
);



 
return output;
} 
}public class reset_offset { 

 public static object function(object input) {
object output = null;

set_offset(Vector3.zero); 
return output;
} 
}
 }
}