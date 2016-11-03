
#include <stdio.h>
#include <stdlib.h>
#include "Hull3q.h"
#include "Scene.h"
#include <fstream>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace std;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>

GLuint loadCubemap(vector<const GLchar*> faces);
int main(void)
{
	int mountianheight = 0;
	int cycles = 0;
	char question;
	bool range = false;
	bool repeat = true;
	
	repeat = false;
	while (!range)
	{
		while (!range)
		{
			mountianheight = 69;
			if (mountianheight <20 || mountianheight > 100)
			{
				cout << "Please enter a number between 20 and 100." << endl;
			}
			else
				range = true;
		}
		range = false;
		while (!range)
		{
			cout << "Enter the number of iterations (ie mountain making loops) (0-10):  ";
			cin.clear();
			cin >> cycles;
			if (cycles <0 || cycles > 10)
			{
				cout << "Please enter a number between 0 and 10." << endl;
			}
			else
				range = true;
		}
	}
	Hull hl(cycles);
	hl.makeHull(mountianheight, cycles);
	//cout << "Build another mountian? (enter y for yes)" << endl;
	//cin.clear();
	//cin >> question;
	repeat = false;
	//////////////////////////////////////////
	
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1000, 750, " GL Mountain", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 600, 10);
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1000 / 2, 800 / 2);

	// Dark blue background
	glClearColor(.40f, .60f, .95f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_SAMPLE_SHADING);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");
	
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

	// Load the texture
	GLuint Texture6 = loadDDS("Stone_DarkGray.DDS");
	
	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

	Scene background;

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colorvec;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; 
	

	// Load it into a VBO
	int size = hl.vertices.size();

	for (int i = 0; i<size; i++)
	{
		glm::vec3 vertex;
		vertex.x= (hl.vertices[i].getXpos()/20)-2;
		vertex.y = (hl.vertices[i].getZpos()/20)-1;
		vertex.z = hl.vertices[i].getYpos()/20;
		vertices.push_back(vertex);
	}
	

	// Load it into a VBO

	size = hl.UVs.size();
	int uvcount = 0;
	while (uvcount<size)//!unput_dataFile.eof())
	{
		glm::vec2 coor;
		coor.x = hl.UVs[uvcount];
		uvcount++;
		coor.y = hl.UVs[uvcount];
		uvcount++;
		uvs.push_back(coor);
	}

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	do {
		glUseProgram(programID);		
		//cin.get();
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glDepthMask(GL_FALSE); 
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();// glm::mat4(glm::mat3(getViewMatrix()));
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		//ProjectionMatrix = getProjectionMatrix();
		//ViewMatrix = getViewMatrix();
		//ModelMatrix = glm::mat4(1.0);
		//MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		//glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		//glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
		
		background.DrawScene();
	// Bind our texture 

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture6);
		glUniform1i(TextureID, 0);
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		//system("pause");
		//gameloopcount++;
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	//glDeleteBuffers(1, &vertexbuffer);
	//glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII
// Loads a cubemap texture from 6 individual texture faces
// Order should be:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front) 
// -Z (back)
GLuint loadCubemap(vector<const GLchar*> faces)
{
	GLuint textureID;

	for (GLuint i = 0; i < faces.size(); i++)
	{
		FILE *fp;

		/* try to open the file */
		fp = fopen(faces[i], "rb");
		if (fp == NULL) {
			printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", faces[i]); getchar();
			return 0;
		}
		printf("Reading image %s\n", faces[i]);

		unsigned char header[124];

		/* verify the type of file */
		char filecode[4];
		fread(filecode, 1, 4, fp);
		if (strncmp(filecode, "DDS ", 4) != 0) {
			fclose(fp);
			return 0;
		}

		/* get the surface desc */
		fread(&header, 124, 1, fp);

		unsigned int height = *(unsigned int*)&(header[8]);
		unsigned int width = *(unsigned int*)&(header[12]);
		unsigned int linearSize = *(unsigned int*)&(header[16]);
		unsigned int mipMapCount = *(unsigned int*)&(header[24]);
		unsigned int fourCC = *(unsigned int*)&(header[80]);


		unsigned char * buffer;
		unsigned int bufsize;
		/* how big is it going to be including all mipmaps? */
		bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
		buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
		fread(buffer, 1, bufsize, fp);
		/* close the file pointer */
		fclose(fp);

		unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
		unsigned int format;
		switch (fourCC)
		{
		case FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			free(buffer);
			return 0;
		}

		// Create one OpenGL texture
		GLuint textureID;
		glGenTextures(1, &textureID);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
		unsigned int offset = 0;

		/* load the mipmaps */
		for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
		{
			unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
			glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, format, width, height,
				0, size, buffer + offset);

			offset += size;
			width /= 2;
			height /= 2;

			// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
			if (width < 1) width = 1;
			if (height < 1) height = 1;

		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	}
		return textureID;
}
