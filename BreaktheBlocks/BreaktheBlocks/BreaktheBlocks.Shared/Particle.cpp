#include "Particle.h"

Particle::Particle()
{
}
Particle::~Particle()
{
}

Particle::Particle(GLfloat posX, GLfloat PosY, GLfloat VelX, GLfloat VelY, GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat lifetime)
{
	Position = { posX, PosY, 0.0 };
	
	//vec3 tempDirection = {  rand() % 10 * 0.1f - 0.5f, rand() % 10 * 0.1f - 1.0f, 0 };
	
	//vec3 tempColor = {  rand() % 10 * 0.1f , rand() % 10 * 0.1f , rand() % 10 * 0.1f };
	Scale = { 7, 7, 1};
	//Velocity = Normalize(tempDirection);
	Color = {R,G,B};
	Alpha = A;
	Life = lifetime;
}


void Particle::setPosition(GLfloat x, GLfloat y)
{
	Position.x = x;
	Position.y = y;
	
}

void Particle::reset()
{
	durationTime = 0;
}

void Particle::setPosition(vec3& pos)
{
	Position = pos;
}

void Particle::PhysicsUpdate(GLfloat& deltaTime)
{
	if (Life - deltaTime > 0)
	{
		durationTime += deltaTime;
	}
}
