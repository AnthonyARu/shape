# shape
Shapes, is a Advance computer graphics project, developed with OpenGL/ C++.

in main.cpp, The code for the project is written in C++.
in shaders.cpp the required code to render shapes
vertexshader and fragment shader, required for renedring and attributing the shapes and window.


The Purpose of the project is to manipulate shapes and perform operations on them such as translation, scaling and rotation.
The shapes will be decided based on the number of indices and vertices that will be sent to the gpu to render. 

Using glfwGetKey an inbuilt function, i was able to declare what key to press and what i wish to achieve when the key is pressed

When "J" is pressed, A Square will appear || When "K" is pressed, A Hexagon will appear || When "L" is pressed, A Octagon will appear

When "R" is pressed the shape present on screen will Rotate as long as the button is pressed. 
When "T" is pressed, the shape will move from either side of the window. The windows dimensions or from (-1,1), Using if statements, we can incement or decrement 
in order to achieve this translation.
When "S" is pressed, the shape will scale to the boundaries of the window, and then it will shrink back to its origin.
