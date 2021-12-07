#include "Particle.h"
#include "GameUtility.h"

class ParticleManager
{
public:
	std::vector<Particle> particles;

	GLuint MaxParticle = 0;
	GLuint ParticleShader;
	GLuint LastUsed = 0;
	GLuint drawCount = 36;

	GLboolean isScaling = false;
	GLboolean isLooping = false;
	GLboolean isGravity = false;
	GLboolean isColorChange = false;

	GLfloat RateOverScale = 0.0f;
	GLfloat RateOverAlpha = 0.0f;
	shape Shape = CIRCLE;
	ParticleManager(GLint maxCount, GLfloat posX, GLfloat PosY, GLfloat VelX, GLfloat VelY, GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat lifetime);
	~ParticleManager();
	void RenderUpdate(GLfloat &deltaTime);
	void setParticlesPosition(GLfloat x, GLfloat y, GLuint num);
	void resetParticles(GLuint num);
	void addLastUsedNum();
};

