using System;
using System.Collections.Generic;
using UnityEngine;
 namespace Ex.CSharpFunctions { public class Sound_controller { 

static AudioSourceComponent audioC = ExVR.Components().get_from_name<AudioSourceComponent>("Audio source");

static float startDistanceM = 1.0425f;
static float speedMMs = 0.00075f;
static float incrementMs = 190f;
static float condition = 1f;

static int process(IdAny idV){

	if(idV.id == 0){
		string conditionName = (string)idV.value;
		condition = Converter.to_float(	conditionName.Substring(1));
	}else if(idV.id == 1){
		float currentTimeMs = Converter.to_float((double)idV.value);
		if(start_audio_tactile(currentTimeMs)){
			return 248;
		}
	}

	return 0;
}

static bool start_audio_tactile(float currentTimeMs){	

	TransformValue tv = new TransformValue();
	tv.position = new Vector3(0f,0.02f, startDistanceM - speedMMs * currentTimeMs);
	tv.scale = new Vector3(0.05f,0.05f,0.05f);
	audioC.current_config().set_transform("transform", tv);
	audioC.update_from_current_config();

	return currentTimeMs > (condition*incrementMs);
}public class T1 { 

 public static object function(object input) {
object output = null;
output = process((IdAny)input); 
return output;
} 
}public class T2 { 

 public static object function(object input) {
object output = null;
output = process((IdAny)input); 
return output;
} 
}public class T3 { 

 public static object function(object input) {
object output = null;
output = process((IdAny)input); 
return output;
} 
}public class T4 { 

 public static object function(object input) {
object output = null;
output = process((IdAny)input); 
return output;
} 
}public class T5 { 

 public static object function(object input) {
object output = null;
output = process((IdAny)input); 
return output;
} 
}public class T6 { 

 public static object function(object input) {
object output = null;
output = process((IdAny)input); 
return output;
} 
}
 }
}