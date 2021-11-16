#include "GameUtility.h"

vec3 Normalize(vec3& Direction)
{
	
	GLfloat Norm = sqrtf(powf(Direction.x, 2) + powf(Direction.y, 2) + powf(Direction.z, 2));
	vec3 normalized = { Direction.x / Norm, Direction.y / Norm, Direction.z / Norm };

	return normalized;
}

void transScreenToGL(GLfloat screenWidth, GLfloat screenHeight,
	GLfloat inputX, GLfloat inputY, GLfloat* convertedX, GLfloat* convertedY)
{
	*convertedX = (GLfloat)((inputX - (GLfloat)screenWidth / 2.0f) * (GLfloat)(1.0f / (GLfloat)(screenWidth / 2.0f)));
	*convertedY = -(GLfloat)((inputY - (GLfloat)screenHeight / 2.0f) * (GLfloat)(1.0f / (GLfloat)(screenHeight / 2.0f)));
}
