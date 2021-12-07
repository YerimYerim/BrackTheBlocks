#include "ParticleManager.h"

ParticleManager::~ParticleManager()
{
}

void ParticleManager::addLastUsedNum()
{
	if (LastUsed < MaxParticle - 1)
	{
		++LastUsed;
	}
	else
	{
		LastUsed = 0;
	}
}

void ParticleManager::setParticlesPosition( GLfloat x, GLfloat y, GLuint num)
{
	particles[num].setPosition(x, y);
}

void ParticleManager::durationTimeUpdate(GLfloat& deltaTime)
{
	for (int i = 0; i < MaxParticle; ++i)
	{
		particles[i].durationTimeUpdate(deltaTime);
	}
}

ParticleManager::ParticleManager(GLint maxCount , GLfloat posX, GLfloat PosY, GLfloat VelX, GLfloat VelY, GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat lifetime)
{
	MaxParticle = maxCount;
	for (int i = 0; i < maxCount; ++i)
	{
		Particle Particle = { posX, PosY, VelX, VelY, R, G, B, A, lifetime };
		particles.push_back(Particle);
	}
}

void ParticleManager::resetParticles(GLuint num)
{
	particles[num].reset();
}
