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
	*convertedX = (GLfloat)((inputX - (GLfloat)screenWidth * 0.5f) * (GLfloat)(1.0f / (GLfloat)(screenWidth * 0.5f)));
	*convertedY = -(GLfloat)((inputY - (GLfloat)screenHeight * 0.5f) * (GLfloat)(1.0f / (GLfloat)(screenHeight * 0.5f)));
}
void transGameWorldToGL(GLfloat WorldWidth, GLfloat WorldHeight,GLfloat ScreenRatio,
	GLfloat gameWorldX, GLfloat gameWorldY, GLfloat* GLposX, GLfloat* GLposY)
{
		*GLposX = (GLfloat)(gameWorldX) / ((GLfloat)WorldWidth * 0.5f);
		*GLposY = (GLfloat)(gameWorldY) / ((GLfloat)WorldHeight * 0.5f) * (GLfloat)ScreenRatio;
}
GLboolean SetTimer(float StartTime, int durationSec, int endSecond)
{
	int Sec = 0;
	std::chrono::system_clock::time_point nowTime = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
	std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(endTime - nowTime);
	if (durationSec < endSecond)
	{
		durationSec++;
		return false;
	}
	return true;
}
void updateDeltaTime(float& deltatime, std::chrono::system_clock::time_point& lastTime)
{
	std::chrono::system_clock::time_point curTime = std::chrono::system_clock::now();
	deltatime = (curTime - lastTime).count() * 0.00001f;
	lastTime = curTime;
}
