#include "ParticleManager.h"

ParticleManager::~ParticleManager()
{
}

void ParticleManager::RenderUpdate(GLfloat& deltaTime)
{
	for(int i = 0; i < particles.size(); ++i)
	{
		particles[i].PhysicsUpdate(deltaTime);
	}
}

ParticleManager::ParticleManager(GLint maxCount , GLfloat posX, GLfloat PosY, GLfloat VelX, GLfloat VelY, GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat lifetime)
{
	MaxParticle = maxCount;
	for (int i = 0; i < maxCount; ++i)
	{
		float x = rand() % 10;
		Particle Particle = { posX, PosY, VelX, VelY, R, G, B, A, lifetime };
		particles.push_back(Particle);
	}
}
