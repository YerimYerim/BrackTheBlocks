
#pragma once

#include "GameObject.h"
#include "Particle.h"

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

	const char* objectfragmentShader = 
		"#version 300 es\n"
		"in vec3 v_Color;\n"
		"in vec3 vertPos;\n"
		"flat in vec3 startPos;\n"
		"uniform int u_isDot;\n"
		"uniform vec2  u_resolution;\n"
		"float u_dashSize = 0.01f;\n"
		"float u_gapSize = 0.01f;\n"
		"out vec4 FragColor;\n"
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

	const char* particleVertexShader = 
		"#version 300 es\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform vec4 v_Color;\n"
		"uniform vec3 scale;\n"
		"uniform vec3 direction;\n"
		"uniform vec3 transform;\n"
		"uniform float aRatio;\n"
		"uniform float durationTime;\n"
		"uniform float lifeTime;\n"
		"uniform int isGravity;\n"
		"uniform int isScaling;\n"
		"uniform int isAlphaChange;\n"
		"const float gravity = 0.0098f;\n"
		"out vec4 Color;\n"
		"void main()\n"
		"{\n"
		"	vec4 aTrasnform = vec4(transform.x + direction.x * durationTime * 0.05f , transform.y + direction.y * durationTime* 0.05f, 0.0f , 0.0f);\n"
		"	vec4 aLocalPosition = vec4(aPos.x , aPos.y, 1.0f , 1.0f);\n"
		"	vec4 color = v_Color;\n"
		"	float scalePerTime = pow(0.95f , durationTime);\n"
		"   float Accel = pow(durationTime, 2.0f);\n"
		"	vec4 aSize = vec4(scale.x / 300.0f, scale.y * aRatio / 300.0f, 1.0f,1.0f);\n"
		"	if(isGravity != 0) // true 일때\n"
		"	{\n"
		"		aTrasnform.y =  aTrasnform.y - 0.5f * gravity * Accel; \n"
		"	}\n"
		"	if(isScaling != 0) // true 일때\n"
		"	{\n"
		"		aSize.x = aSize.x * scalePerTime;\n"
		"		aSize.y = aSize.y * scalePerTime;\n"
		"	}\n"
		"	if(isAlphaChange != 0) // true 일때\n"  
		"	{\n"
		"		color.w = scalePerTime * color.w; \n"
		"	}\n"
		"	vec4 WorldPosition = aLocalPosition * aSize + aTrasnform ;\n"
		"	gl_Position = WorldPosition;\n"
		"	Color = color;\n"
		"}\n";

	const char* particleFragmentShader = 
		"#version 300 es\n"
		"in vec4 Color;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		" FragColor = vec4(Color.x, Color.y, Color.z,Color.w);\n"
		"}\n";

	void makeCirCle();

public:
	                             
	Renderer(GLfloat width, GLfloat height);
	~Renderer();

	void setupObjectRenderer( GameObject& gameObject, shape Shape);
	void updateRenderer();
	void drawGameObject(GameObject& gameObject);

	void drawParticle(Particle& particle, GLboolean isGravity, GLboolean isScaling, GLboolean isAlphaChange);


};