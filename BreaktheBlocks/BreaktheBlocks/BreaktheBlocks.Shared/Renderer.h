
#pragma once

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
	GLuint particleShader;
	GLfloat screenRatio;
	GLfloat screenWidth;
	GLfloat screenHeight;
	GLfloat circleVertexBuffer[12 * 3 * 3];
	GLfloat circleColor[12 * 3 * 3 + 3];

	GLfloat rectangleVertexBuffer[18] = {
	   1.0f, -1.0f, 0.0f,
	   1.0f,  1.0f, 0.0f,
	   -1.0f, -1.0f, 0.0f,

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
	const char* objectVertexShader= "#version 300 es\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"uniform float aRatio;\n"
		"uniform float aSizeX;\n"
		"uniform float aSizeY;\n"
		"uniform float aTransX;\n"
		"uniform float aTransY;\n"
		"flat out vec3 startPos;\n"		
		"out vec3 v_Color;\n"
		"out vec3 vertPos;\n"
		"void main()\n"
		"{\n"
		" vec4 aSize = vec4(aSizeX , aSizeY * aRatio, 1.0f ,1.0f);\n"
		" vec4 aTrasnform = vec4(aTransX , aTransY, 0f, 0.0f);\n"
		" vec4 aPosition = vec4(aPos.x , aPos.y, 1.0f, 1.0f );\n"
		" vec4 pos = aPosition * aSize + aTrasnform;\n"
		" gl_Position = pos;\n"
		" vertPos = pos.xyz;\n"
		" startPos = pos.xyz;\n"
		" v_Color = aColor;\n"
		"}\n";                            

	const char* objectfragmentShader = "#version 300 es\n"
		"in vec3 v_Color;\n"
		"out vec4 FragColor;\n"
		"flat in vec3 startPos;\n"
		"in vec3 vertPos;\n"
		"uniform vec2  u_resolution;\n"
		"float u_dashSize = 0.01f;\n"
		"float u_gapSize = 0.01f;\n"
		"uniform int u_isDot;"
		"void main()\n"
		"{\n"
		"	if(u_isDot != 0)\n"
		"	{\n"
		"		vec2  dir = (vertPos.xy - startPos.xy) * 0.5f ;\n"
		"		float dist = length(dir);\n"
		"		if (fract(dist / (u_dashSize + u_gapSize)) > u_dashSize / (u_dashSize + u_gapSize))\n"
		"			discard; \n"
		"	}\n"
		"	FragColor = vec4(v_Color.x,v_Color.y,v_Color.z, 1.0f);\n"
		"}\n";

	//const char* particleVertexShader = "#version 300 es\n"
	//"layout (location = 0) in vec3 aPos;\n"
	//	"layout (location = 1) in vec3 aColor;\n"
	//	"uniform float aRatio;\n"
	//	"uniform float aSizeX;\n"
	//	"uniform float aSizeY;\n"
	//	"uniform float aTransX;\n"
	//	"uniform float aTransY;\n"
	//	//"const vec3 aGravity = vec3(0,-0.1,0);\n"
	//	//"const vec3 aEmitTime= vec3(0,-0.1,0);\n"
	//	//"const vec3 = vec3(0,-0.1,0);\n"
	//	"out vec3 v_Color;\n"
	//	"void main()\n"
	//	"{\n"
	//	" vec4 aSize = vec4(aSizeX , aSizeY * aRatio, 1.0f,1.0f);\n"
	//	" vec4 aTrasnform = vec4(aTransX , aTransY, 0.0f , 0.0f);\n"
	//	" vec4 aPosition = vec4(aPos.x , aPos.y, 1.0f , 1.0f);\n"
	//	" gl_Position = aPosition * aSize + aTrasnform;\n"
	//	" v_Color = aColor;\n"
	//	"}\n";

	//const char* particleFragmentShader = "#version 300 es\n"
	//	"in vec3 v_Color;\n"
	//	"out vec4 FragColor;\n"
	//	"void main()\n"
	//	"{\n"
	//	" FragColor = vec4(v_Color.x,v_Color.y,v_Color.z, 1.0f);\n"
	//	"}\n";

	void makeCirCle();

public:
	                             
	Renderer(GLfloat width, GLfloat height);
	~Renderer();

	void setupObjectRenderer( GameObject& gameObject, shape Shape);
	void updateRenderer();
	void drawGameObject(GameObject& gameObject);

	void drawParticle(GameObject& gameObject);

};