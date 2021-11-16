#pragma once
struct vec3
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

vec3 Normalize(vec3& Direction);
void transScreenToGL(GLfloat screenWidth, GLfloat screenHeight,
	GLfloat inputX, GLfloat inputY, GLfloat* convertedX, GLfloat* convertedY);