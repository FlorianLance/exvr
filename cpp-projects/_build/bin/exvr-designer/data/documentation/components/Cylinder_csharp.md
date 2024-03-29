

### Content:

```
// unity
using UnityEngine;

namespace Ex{
    public class CylinderComponent : ExComponent{    
        public override void update_from_current_config();
    }
}
```


### Samples:

```

// retrieve component 
var modelComponent = (CylinderComponent)get("cylinder_component_name");
// or 
var modelComponent = get<CylinderComponent>("cylinder_component_name");
// or if only one available
var modelComponent = get_first<CubeComponent>();


// change model current condition parameters
// # retrieve config
var modelConfig = modelComponent.current_config();    

// # change material color
modelConfig.set_color("color", Color.blue);
// # change material metallic value
modelConfig.set<float>("metallic", 0.5f);
// # change material smoothness value
modelConfig.set<float>("smoothness", 0.2f);   

// you can move/resize the model with:
// # a list of 3 Vector3 (postion,rotation,scale)
List<Vector3> listV = new List<Vector3>();
listV.Add(new Vector3(0,2f,0));  // position
listV.Add(new Vector3(30f,0,0)); // rotation
listV.Add(Vector3.one);          // scale
modelConfig.set_transform("transform", listV);

// # a TransformValue
TransformValue trV = new TransformValue();
trV.position = new Vector3(0,2f,0);
trV.rotation = Quaternion.Euler(new Vector3(30f,0,0));
trV.scale    = Vector3.one;
modelConfig.set_transform("transform", trV);

// # a Transform
Transform tr = someGameObject.transform;
modelConfig.set_transform("transform", tr);

// apply changes
modelComponent.update_from_current_config();
    
```

### Configs parameters:
```
// initialization config
var initC = init_config();
TransformValue trV = initC.get_transform("init_transform");
initC.get<int>("nb_sides");
initC.get<float>("radius");
initC.get<float>("length");

// condition config
var currentC = current_config();
TransformValue trV = currentC.get_transform_value("transform");
currentC.get_color("color");
currentC.get<float>("metallic");
currentC.get<float>("smoothness");
```



