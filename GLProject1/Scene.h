#pragma once
#include <GL/glew.h>

#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <common/shader.hpp>
#include <common/texture.hpp>
#include <iostream>
//extern GLFWwindow* window;
using namespace glm;
using namespace std;
class Scene
{
	public:
		Scene();
		void DrawScene();

private:
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");
	// Load the texture
	GLuint Texture;// = loadDDS("camodn.DDS");
	GLuint Texture1;// = loadDDS("camoft.DDS");
	GLuint Texture2;// = loadDDS("camoup.DDS");
	GLuint Texture3;// = loadDDS("camolf.DDS");
	GLuint Texture4;// = loadDDS("camort.DDS");
	GLuint Texture5;// = loadDDS("camobk.DDS");
	GLuint TextureID;// = glGetUniformLocation(programID, "myTextureSampler");

};

Scene::Scene()
{
	 programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");
	// Load the texture
	 Texture = loadDDS("camodn.DDS");
	 Texture1 = loadDDS("camoft.DDS");
	 Texture2 = loadDDS("camoup.DDS");
	 Texture3 = loadDDS("camolf.DDS");
	 Texture4 = loadDDS("camort.DDS");
	 Texture5 = loadDDS("camobk.DDS");
	 TextureID = glGetUniformLocation(programID, "myTextureSampler");

}
void Scene::DrawScene()
{	
	//ground data
	static const GLfloat g_vertex_buffer_data[] =
	{
		-10.0f, -1.0f, 10.0f,
		-10.0f, -1.0f, -10.0f,
		10.0f, -1.0f, -10.0f,
		10.0f, -1.0f,  10.0f,		
	};
	static const GLfloat g_uv_buffer_data[] =
	{
		1.0f, 1.0f,
		1.0f, 0.0f,

		0.0f, 0.0f,
		0.0f, 1.0f,
	};
	GLuint dnindices[] = {  
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	GLuint vertexbuffer1;
	glGenBuffers(1, &vertexbuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), &g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint uvbuffer1;
	glGenBuffers(1, &uvbuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), &g_uv_buffer_data, GL_STATIC_DRAW);

	GLuint EBOdn;
	glGenBuffers(1, &EBOdn);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOdn);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dnindices), dnindices, GL_STATIC_DRAW);
	//front	
	static const GLfloat g_vertex_buffer_dataft[] =
	{
		10.0f, 10.0f, 10.0f,
		10.0f, -1.0f, 10.0f,

		-10.0f, -1.0f,  10.0f,
		-10.0f, 10.0f, 10.0f,
	};
	static const GLfloat g_uv_buffer_dataft[] =
	{
		1.0f, 1.0f,
		1.0f, 0.0f,

		0.0f, 0.0f,
		0.0f, 1.0f,
	};
	GLuint indices[] = { 
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	GLuint vertexbuffer2;
	glGenBuffers(1, &vertexbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_dataft), &g_vertex_buffer_dataft, GL_STATIC_DRAW);

	GLuint uvbuffer2;
	glGenBuffers(1, &uvbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_dataft), &g_uv_buffer_dataft, GL_STATIC_DRAW);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//up	
	static const GLfloat g_vertex_buffer_dataup[] =
	{
		10.0f, 10.0f, 10.0f,
		10.0f, 10.0f, -10.0f,

		-10.0f, 10.0f,  -10.0f,
		-10.0f, 10.0f, 10.0f,
	};
	static const GLfloat g_uv_buffer_dataup[] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 1.0f,
		0.0f, 1.0f,
	};
	GLuint upindices[] = {  
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	GLuint vertexbuffer3;
	glGenBuffers(1, &vertexbuffer3);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_dataup), &g_vertex_buffer_dataup, GL_STATIC_DRAW);

	GLuint uvbuffer3;
	glGenBuffers(1, &uvbuffer3);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_dataup), &g_uv_buffer_dataup, GL_STATIC_DRAW);

	GLuint EBOup;
	glGenBuffers(1, &EBOup);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOup);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), upindices, GL_STATIC_DRAW);

	//left	
	static const GLfloat g_vertex_buffer_datalf[] =
	{
		-10.0f, 10.0f, 10.0f,
		-10.0f, -1.0f, 10.0f,

		-10.0f, -1.0f,  -10.0f,
		-10.0f, 10.0f, -10.0f,
	};
	static const GLfloat g_uv_buffer_datalf[] =
	{
		1.0f, 1.0f,
		1.0f, 0.0f,

		0.0f, 0.0f,
		0.0f, 1.0f,
	};
	GLuint lfindices[] = { 
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	GLuint vertexbuffer4;
	glGenBuffers(1, &vertexbuffer4);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_datalf), &g_vertex_buffer_datalf, GL_STATIC_DRAW);

	GLuint uvbuffer4;
	glGenBuffers(1, &uvbuffer4);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_datalf), &g_uv_buffer_datalf, GL_STATIC_DRAW);

	GLuint EBOlf;
	glGenBuffers(1, &EBOlf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOlf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lfindices), lfindices, GL_STATIC_DRAW);

	//right	
	static const GLfloat g_vertex_buffer_datart[] =
	{
		10.0f, 10.0f, 10.0f,
		10.0f, -1.0f, 10.0f,

		10.0f, -1.0f,  -10.0f,
		10.0f, 10.0f, -10.0f,
	};
	static const GLfloat g_uv_buffer_datart[] =
	{
		0.0f, 1.0f,
		0.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,

	};
	GLuint rtindices[] = {  
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	GLuint vertexbuffer5;
	glGenBuffers(1, &vertexbuffer5);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_datart), &g_vertex_buffer_datart, GL_STATIC_DRAW);

	GLuint uvbuffer5;
	glGenBuffers(1, &uvbuffer5);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_datart), &g_uv_buffer_datart, GL_STATIC_DRAW);

	GLuint EBOrt;
	glGenBuffers(1, &EBOrt);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOrt);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rtindices), rtindices, GL_STATIC_DRAW);

	//back	
	static const GLfloat g_vertex_buffer_databk[] =
	{
		10.0f, 10.0f, -10.0f,
		10.0f, -1.0f, -10.0f,

		-10.0f, -1.0f,  -10.0f,
		-10.0f, 10.0f, -10.0f,
	};
	static const GLfloat g_uv_buffer_databk[] =
	{
		0.0f, 1.0f,
		0.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,

	};
	GLuint bkindices[] = {  
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	GLuint vertexbuffer6;
	glGenBuffers(1, &vertexbuffer6);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_databk), &g_vertex_buffer_databk, GL_STATIC_DRAW);

	GLuint uvbuffer6;
	glGenBuffers(1, &uvbuffer6);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_databk), &g_uv_buffer_databk, GL_STATIC_DRAW);

	GLuint EBObk;
	glGenBuffers(1, &EBObk);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBObk);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bkindices), bkindices, GL_STATIC_DRAW);



	// skybox texture 1
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glUniform1i(TextureID, 0);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
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
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer1);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	//skybox  texture 2 
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Texture1);
	glUniform1i(TextureID, 1);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
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
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	//skybox  texture 3 
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, Texture2);
	glUniform1i(TextureID, 2);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);
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
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer3);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//skybox  texture 4 
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, Texture3);
	glUniform1i(TextureID, 3);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer4);
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
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer4);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//skybox  texture 5 
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, Texture4);
	glUniform1i(TextureID, 4);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer5);
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
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer5);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);


	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//skybox  texture 6 
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, Texture5);
	glUniform1i(TextureID, 5);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer6);
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
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer6);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDepthMask(GL_TRUE);

	glDeleteBuffers(1, &vertexbuffer1);
	glDeleteBuffers(1, &uvbuffer1);
	glDeleteBuffers(1, &EBO);

	glDeleteBuffers(1, &vertexbuffer2);
	glDeleteBuffers(1, &uvbuffer2);
	glDeleteBuffers(1, &EBOdn);

	glDeleteBuffers(1, &vertexbuffer3);
	glDeleteBuffers(1, &uvbuffer3);
	glDeleteBuffers(1, &EBOup);

	glDeleteBuffers(1, &vertexbuffer4);
	glDeleteBuffers(1, &uvbuffer4);
	glDeleteBuffers(1, &EBOlf);

	glDeleteBuffers(1, &vertexbuffer5);
	glDeleteBuffers(1, &uvbuffer5);
	glDeleteBuffers(1, &EBOrt);

	glDeleteBuffers(1, &vertexbuffer6);
	glDeleteBuffers(1, &uvbuffer6);
	glDeleteBuffers(1, &EBObk);

	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);

}
