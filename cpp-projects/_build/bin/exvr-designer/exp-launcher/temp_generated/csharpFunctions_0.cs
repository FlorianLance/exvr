using System;
using System.Collections.Generic;
using UnityEngine;
 namespace Ex.CSharpFunctions { public class Choose__cue { 

static Routine wordsRoutine = ExVR.Routines().get("Words");
static List<string> conditions = ExVR.Instance().get_routine_conditions_names_order(wordsRoutine);
static string content = ExVR.Resources().get_text_file_data("words").content;
static string[] words = content.Split(new string[] {
	System.Environment.NewLine }, StringSplitOptions.None
);

public class standard { 

 public static object function(object input) {
object output = null;

int id = Converter.to_int(conditions[(int)input]);
output = words[id];


// 40 words
// 3x4 * 40

 
return output;
} 
}
 }
}