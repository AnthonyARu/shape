// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

// Include GLEW
#include "dependente\glew\glew.h"

// Include GLFW
#include "dependente\glfw\glfw3.h"

// Include GLM
#include "dependente\glm\glm.hpp"
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"

#include "shader.hpp"

//variables
GLFWwindow* window;
const int width = 1024, height = 1024;
float sx = 0.1f, sy = 0.1f, sz = 0;

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, "Lab 4", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		return -1;
	}

	//specify the size of the rendering window
	glViewport(0, 0, width, height);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	//sqaure
	std::vector<GLfloat> squareVertices =
	{
		 1.0f,  1.0f,  0.0f, // top right	
		 1.0f, -1.0f,  0.0f, // bottom right
		-1.0f, -1.0f,  0.0f, // bottom left
		-1.0f,  1.0f,  0.0f, // top left 
	};

	std::vector<unsigned int> squareIndices =
	{
		0, 1, 2,
		2, 3, 0
	};
	//hexagon
	std::vector<GLfloat> hexagonVertices =
	{
		-0.5f,   1.0f, 0.0f,    // left top
		0.5f,   1.0f, 0.0f,    // right top
		1.0f,   0.0f, 0.0f,    // right
		0.5f,   -1.0f, 0.0f,    // right bottom
		-0.5f,  -1.0f, 0.0f,    // left bottom
		-1.0f,   0.0f, 0.0f,     // left
	};

	std::vector<unsigned int> hexagonIndices =
	{
		0,1,2,
		2,3,0,
		3,4,0,
		4,5,0,
		5,6,0,
		6,1,0
	};
	//octagon
	std::vector<GLfloat> octagonVertices =
	{
		-0.4f, 1.0f, 0.0f,    // left top
		-1.0f, 0.4f,0.0f,		//middletop left
		-1.0f, -0.4f,0.0f,	//middlebottom left
		-0.4f, -1.0f,0.0f,	//bot left
		 0.4f, -1.0f, 0.0f,
		 1.0, -0.4, 0.0f,
		 1.0,0.4,0.0f,
		 0.4,1.0,0.0f

	};

	std::vector<unsigned int> octagonIndices =
	{
		0,1,2,
		2,3,0,
		3,4,0,
		4,5,0,
		5,6,0,
		6,7,0,
		7,8,0,
		8,9,0,
		9,1,0
	};


	// A Vertex Array Object (VAO) is an object which contains one or more Vertex Buffer Objects and is designed to store the information for a complete rendered object. 
	GLuint vbo, vao, ibo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	//bind VAO
	glBindVertexArray(vao);

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	//bind IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);


	//set attribute pointers
	glVertexAttribPointer(
		0,                  // attribute 0, must match the layout in the shader.
		3,                  // size of each attribute
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		3 * sizeof(float),  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);


	glm::mat4 trans(1.0f);
	trans = glm::scale(trans, glm::vec3(sx, sy, sz));

	float s = 0.0f; // scaling variable
	float x = 0.0f; // float variable for the value of x since the translation will happen on the x-axis 
	bool goLeft = false; // going left boolean as false because the starting motion should be going to the right
	bool goRight = true; // going right boolean as true because the starting motion should be going to the right

	


	while (!glfwWindowShouldClose(window))
	{
		// Swap buffers
		glfwSwapBuffers(window);

		// Check for events
		glfwPollEvents();

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);
		//send verteces and indices to buffer for every key that is pressed. Results in the changing of shape.
		if (glfwGetKey(window, GLFW_KEY_J)) {
			std::vector<GLfloat> verticesSentToGPU = squareVertices;
			std::vector<unsigned int> indicesSentToGPU = squareIndices;

			glBufferData(GL_ARRAY_BUFFER, verticesSentToGPU.size() * sizeof(GLfloat), &(*verticesSentToGPU.begin()), GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSentToGPU.size() * sizeof(unsigned int), &(*indicesSentToGPU.begin()), GL_STATIC_DRAW);
		}

		if (glfwGetKey(window, GLFW_KEY_K)) {
			std::vector<GLfloat> verticesSentToGPU = hexagonVertices;
			std::vector<unsigned int> indicesSentToGPU = hexagonIndices;

			glBufferData(GL_ARRAY_BUFFER, verticesSentToGPU.size() * sizeof(GLfloat), &(*verticesSentToGPU.begin()), GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSentToGPU.size() * sizeof(unsigned int), &(*indicesSentToGPU.begin()), GL_STATIC_DRAW);
		}

		if (glfwGetKey(window, GLFW_KEY_L)) {
			std::vector<GLfloat> verticesSentToGPU = octagonVertices;
			std::vector<unsigned int> indicesSentToGPU = octagonIndices;

			glBufferData(GL_ARRAY_BUFFER, verticesSentToGPU.size() * sizeof(GLfloat), &(*verticesSentToGPU.begin()), GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSentToGPU.size() * sizeof(unsigned int), &(*indicesSentToGPU.begin()), GL_STATIC_DRAW);
		}
		std::vector<GLfloat> verticesSentToGPU = hexagonVertices;
		std::vector<unsigned int> indicesSentToGPU = hexagonIndices;


		if (glfwGetKey(window, GLFW_KEY_R)) {
			trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
		}

		if (glfwGetKey(window, GLFW_KEY_S)) {
		
			trans = glm::scale(glm::mat4(1.0f), glm::vec3(sin(glfwGetTime()), sin(glfwGetTime()), 0.0f)); //modifing the sacling factor on button press
		}

		if (glfwGetKey(window, GLFW_KEY_T)) { //if T is pressed do translation to right then to left
			if (goRight == true) { //initial setting: going right first
				if (x < 1.0f) { //if x < 1.0 continue going right (1.0 is the maximum right boundry of the screen) 
					x += 0.01f;
				}
				else { //when x is > 1.0 then we have to go left so we set the boolean for going right to false and set the boolean for going left to true
					goLeft = true;
					goRight = false;
				}
			}
			if (goLeft == true) { //second setting: going left 
				if (x > -1.0f) { //if x > -1.0 continue going left (-1.0 is the maximum right boundry of the screen) 
					x -= 0.01f;
				}
				else {  //when x is < -1.0 then we have to go right so we set the boolean for going left to false and set the boolean for going right to true
					goRight = true;
					goLeft = false;
				}
			}
			trans = glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, 0.0f));
			trans = glm::scale(trans, glm::vec3(sx, sy, sz));//modifing only the x position since we want to move to the right then left and visa versa on the x-axis
		}


		glUseProgram(programID);

		//rotation task based on glfw
		//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
		//with fixed angle
		//trans = glm::rotate(trans, 1.0f, glm::vec3(0.0, 0.0, 1.0));

			//bind VAO
		glBindVertexArray(vao);

		// send variables to shader
		unsigned int transformLoc = glGetUniformLocation(programID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));




		unsigned int transformLoc2 = glGetUniformLocation(programID, "color");
		glm::vec4 color = glm::vec4(0.5f, 0, 0.5f, 1.0);
		glUniform4fv(transformLoc2, 1, glm::value_ptr(color));


		glDrawElements(GL_TRIANGLES, indicesSentToGPU.size(), GL_UNSIGNED_INT, 0);
	}

	// Cleanup
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}