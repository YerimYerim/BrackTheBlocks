#pragma once
#include "GameUtility.h"

class Particle
{
private:
	
	GLfloat StartTime = 0.0f;
	GLfloat EndTime = 0.0f;
	GLfloat CurTime = 0.0f;

	vec3 transfrom = { 0.0f,0.0f, 1.0f};
	GLfloat* vertexPosition;
	GLfloat* colorPosition;

	GLuint drawCount;
	GLuint vertexBuffer;
	GLuint colorBuffer;

	GLuint Count = 12;
};

