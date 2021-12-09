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

ParticleManager::ParticleManager(GLint maxCount, GLfloat posX, GLfloat PosY, GLfloat VelX, GLfloat VelY, GLfloat ScaleX, GLfloat ScaleY, GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat lifetime)
{
	MaxParticle = maxCount;
	for (int i = 0; i < maxCount; ++i)
	{
		Particle Particle = { posX, PosY, VelX, VelY,  ScaleX , ScaleY ,R, G, B, A, lifetime };
		particles.push_back(Particle);
	}
}
ParticleManager::ParticleManager(GLint maxCount, GLfloat posX, GLfloat PosY, GLfloat ScaleX, GLfloat ScaleY, GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat lifetime)
{
	MaxParticle = maxCount;
	for (int i = 0; i < maxCount; ++i)
	{
		vec3 temp = { rand() % 20 * 0.1f - 1, rand() % 10 * 0.1f - 0.5f , 8};
		temp = Normalize(temp);
		Particle Particle = { posX, PosY, temp.x, temp.y,ScaleX ,ScaleY ,R, G, B, A, lifetime };
		particles.push_back(Particle);
	}
}
ParticleManager::ParticleManager()
{
}

void ParticleManager::resetParticles(GLuint num)
{
	particles[num].reset();
}
