# ExVR - Open Virtual Psychology

ExVR is a software for creating and executing 3D/2D complexes experiments using virtual reality or not. Its philosophy is roughly based on [Psychopy](https://www.psychopy.org/) and can easily be extended by users using scripting.
It allows to create pipeline of different routines, ISI using loops for generating a randomization based on conditions. To each condition we can associate any number of components (theses ones can be anything, an image, a sound, a script, a 3D scene...) with timelines and specific configurations.

Communication between components can be done using scripting (C# or Python) or by using visual scripting with nodes and connections.


ExVR is subdivided in two software:
* the designer with a GUI for creating the experiments
* the launcher (based on Unity 3D engine) that will generate and execute the previously defined experiment

They both communicate between themselves, the GUI controls the launcher and can update its parameters, and the launcher send information and feedback to the GUI.
