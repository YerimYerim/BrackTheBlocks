
#pragma once
#ifndef __HelloCubeNative__main__
#define __HelloCubeNative__main__

#include <stdio.h>
#ifdef __ANDROID__
#include <GLES3/gl3.h>
#elif __APPLE__
#include <OpenGLES/ES3/gl.h>
#endif

#include "GameObject.h"

enum shape
{
	CIRCLE = 0,
	RECTANGLE = 1,
};
class Renderer
{
private:
	GLuint shader;
	GLfloat screenRatio;

	GLfloat circleVertexBuffer[12 * 3 * 3];
	GLfloat circleColor[12 * 3 * 3 + 3];

	GLfloat rectangleVertexBuffer[18] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   1.0f,  1.0f, 0.0f,

	   1.0f,  1.0f, 0.0f,
	   -1.0f,  1.0f, 0.0f,
	   -1.0f,  -1.0f, 0.0f,
	};
	GLfloat rectangleColorBuffer[18] =
	{
		0.20f, 0.15f, 0.2f,
		0.20f, 0.15f, 0.2f,
		0.20f, 0.15f, 0.2f,
		  
		0.20f, 0.15f, 0.2f,
		0.20f, 0.15f, 0.2f,
		0.20f, 0.15f, 0.2f,
	};

	void makeCirCle();
	unsigned int loadShader();
public:
	                             
	Renderer(GLfloat width, GLfloat height);
	~Renderer();

	void setupRenderer( GameObject& gameObject, shape Shape);
	void updateRenderer();
	void drawGameObject(GameObject& gameObject);

};
#endif /* defined(__HelloCubeNative__main__) */
