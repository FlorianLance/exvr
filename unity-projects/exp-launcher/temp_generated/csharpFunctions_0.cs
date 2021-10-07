using System;
using System.Collections.Generic;
using UnityEngine;
 namespace Ex.CSharpFunctions { public class Sound_tuner { 
public class increase_5s { 

 public static object function(object input) {
object output = null;
	float timeMs = Converter.to_float(input);//(float)((double)input);

	float duration = 5000f;
	float maxVolume = 0.5f;
	if(timeMs < duration){
		output = maxVolume * timeMs / duration;
	}else{
		output = maxVolume;
	} 
return output;
} 
}public class decrease_8s { 

 public static object function(object input) {
object output = null;
	float timeMs = Converter.to_float(input);

	float duration = 8000f;
	float maxVolume = 0.5f;
	if(timeMs < duration){
		output = maxVolume - maxVolume * timeMs / duration;
	}else{
		output = 0f;
	} 
return output;
} 
}public class decrease_5s { 

 public static object function(object input) {
object output = null;
	float timeMs = Converter.to_float(input);

	float duration = 5000f;
	float maxVolume = 0.5f;
	if(timeMs < duration){
		output = maxVolume - maxVolume * timeMs / duration;
	}else{
		output = 0f;
	} 
return output;
} 
}
 }
}