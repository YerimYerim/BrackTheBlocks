#pragma once
#ifdef __ANDROID__
#include <GLES3/gl3.h>
#elif __APPLE__
#include <OpenGLES/ES3/gl.h>
#endif
#include <iostream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <deque>
#include <chrono>
struct vec3
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

vec3 Normalize(vec3& Direction);
void transScreenToGL(GLfloat screenWidth, GLfloat screenHeight,
	GLfloat inputX, GLfloat inputY, GLfloat* convertedX, GLfloat* convertedY);

void updateDeltaTime(float& deltatime, std::chrono::system_clock::time_point& lastTime);
void transGameWorldToGL(GLfloat WorldWidth, GLfloat WorldHeight, GLfloat ScreenRatio,
	GLfloat gameWorldX, GLfloat gameWorldY, GLfloat* GLposX, GLfloat* GLposY);

