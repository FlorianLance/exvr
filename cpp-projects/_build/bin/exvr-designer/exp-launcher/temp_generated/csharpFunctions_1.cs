using System;
using System.Collections.Generic;
using UnityEngine;
 namespace Ex.CSharpFunctions { public class Select_image { 


static ImageViewerComponent selector = ExVR.Components().get_from_name<ImageViewerComponent>("Selector");
static ImageViewerComponent im1 = ExVR.Components().get_from_name<ImageViewerComponent>("Image1");
static ImageViewerComponent im2 = ExVR.Components().get_from_name<ImageViewerComponent>("Image2");
static ImageViewerComponent im3 = ExVR.Components().get_from_name<ImageViewerComponent>("Image3");
static ImageViewerComponent im4 = ExVR.Components().get_from_name<ImageViewerComponent>("Image4");

static List<Vector2> pivots = new List<Vector2>(new Vector2[]{
	new Vector2(1.025f,-0.025f),
	new Vector2(-0.025f,-0.025f),
	new Vector2(1.025f,1.025f),
	new Vector2(-0.025f,1.025f)
});public class standard { 
static int currentId = 0;
 public static object function(object input) {
object output = null;

// selector.force_config("p2");
// selector.update_from_current_config();

//selector.current_config().set_vector2("pivot", p1);





var i = (IdAny)input;

if(i.id == 0){
	var rnd = new System.Random();
	currentId  = rnd.Next(0, 4);  

	var currentRoutineName =  ExVR.Scheduler().current_element_info().name();


	// select set
	int idSet;
	if(currentRoutineName == "Object reco"){
		idSet = 1;
	}else if(currentRoutineName == "Object reco"){
		idSet = 2;
	}else{
		idSet = 3;
	}

	// select word
	int idWord = 1;
	// ... add others images

	var resM = ExVR.Resources();
	var image1 = resM.get_image_file_data(string.Format("{0}_{1}_{2}", idSet, idWord, 1));
	var image2 = resM.get_image_file_data(string.Format("{0}_{1}_{2}", idSet, idWord, 2));
	var image3 = resM.get_image_file_data(string.Format("{0}_{1}_{2}", idSet, idWord, 3));
	var image4 = resM.get_image_file_data(string.Format("{0}_{1}_{2}", idSet, idWord, 4));

	im1.set_image(image1.texture);
	im2.set_image(image2.texture);
	im3.set_image(image3.texture);
	im4.set_image(image4.texture);


}else{
	currentId = (currentId + 1)%4;
}


selector.current_config().set_vector2("pivot", pivots[currentId]);
selector.update_from_current_config(); 
return output;
} 
}
 }
}