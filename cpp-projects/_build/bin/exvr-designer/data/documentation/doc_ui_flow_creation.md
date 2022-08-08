
# Experiment flow creation

![Image](images/img_ui_flow_creation_00.png "icon")

The flow creation panel is the place where you can define the structure of your experiment by placing elements on the arrow.
You have 3 differents available elements:

For adding a new element, first you need to chosse a node:

![Image](images/img_ui_flow_creation_01.png "icon")

Then click on the black ball, it will display 2 differents choices:

![Image](images/img_ui_flow_creation_02.png "icon")

You can either validate a choice by clicking on the corresponding button or canceling it by clicking anywhere on the grey part.

![Image](images/img_ui_flow_creation_03.png "icon")

Here a [routine](cpp-projects/_build/bin/exvr-designer/data/documentation/doc_ui_element_selection.md#routine) has been created.
The [routine](cpp-projects/_build/bin/exvr-designer/data/documentation/doc_ui_element_selection.md#routine) is the base container used in experiments, it contains conditions which number depends from its position inside loops. When created outside a loop they only contains a "default" condition.

You can easily move any [routine](cpp-projects/_build/bin/exvr-designer/data/documentation/doc_ui_element_selection.md#routine) by selecting it: 

![Image](images/img_ui_flow_creation_04.png "icon")

Then clicking on the right or left arrow: 

![Image](images/img_ui_flow_creation_05.png "icon")
![Image](images/img_ui_flow_creation_06.png "icon")

The cross button can remove any element.


If you create a [loop](cpp-projects/_build/bin/exvr-designer/data/documentation/doc_ui_element_selection.md#loop):

![Image](images/img_ui_flow_creation_07.png "icon")

You can move either the [routine](cpp-projects/_build/bin/exvr-designer/data/documentation/doc_ui_element_selection.md#routine) to put it inside, or extending the [loop](cpp-projects/_build/bin/exvr-designer/data/documentation/doc_ui_element_selection.md#loop): my moving its left or right node to englobe the [routine](cpp-projects/_build/bin/exvr-designer/data/documentation/doc_ui_element_selection.md#routine).

![Image](images/img_ui_flow_creation_08.png "icon")
![Image](images/img_ui_flow_creation_09.png "icon")

You can move a node [loop](cpp-projects/_build/bin/exvr-designer/data/documentation/doc_ui_element_selection.md#loop): to englobe another one, but loops nodes cannot overlap.

![Image](images/img_ui_flow_creation_10.png "icon")
![Image](images/img_ui_flow_creation_11.png "icon")
![Image](images/img_ui_flow_creation_12.png "icon")

It's possible to transform a [routine](cpp-projects/_build/bin/exvr-designer/data/documentation/doc_ui_element_selection.md#routine) into a [randomizer](cpp-projects/_build/bin/exvr-designer/data/documentation/doc_ui_element_selection.md#randomizer).

![Image](images/img_ui_flow_creation_13.png "icon")

It behaves exactly like an empty [routine](cpp-projects/_build/bin/exvr-designer/data/documentation/doc_ui_element_selection.md#routine) and it is used mostly for creating complexes randomizations or as an indicator to separate sections in the flow.

![Image](images/img_ui_flow_creation_15.png "icon")

You can zoom using this bar or adapt the view to the scene by clicking on the button.

![Image](images/img_ui_flow_creation_14.png "icon")

