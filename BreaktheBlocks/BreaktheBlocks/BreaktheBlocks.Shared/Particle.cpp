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
	vec3 tempDirection = { rand() % 10, rand() % 10, 0 };	
	Velocity = Normalize(tempDirection);
	Color = { R, G, B };
	Alpha = A;
	Life = lifetime;
}

void Particle::PhysicsUpdate(GLfloat& deltaTime)
{
	if (Life > 0)
	{
		Life -= deltaTime;
		durationTime += deltaTime;
	}
}
