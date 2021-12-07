#ifndef PARTICLE_H
#define PARTICLE_H
#include "GameUtility.h"

class Particle
{
public:
    vec3 Position;
    vec3 Velocity;
    vec3 Scale = {1, 1 ,1};
    vec3 Color;
    GLfloat Alpha;
    GLfloat Life;
    GLfloat durationTime = 0;
    GLuint vertexBuffer;

    Particle(GLfloat posX, GLfloat PosY, GLfloat VelX, GLfloat VelY, GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat lifetime);
    Particle();
    ~Particle();

    void PhysicsUpdate(GLfloat& deltaTime);
    void setPosition(GLfloat x, GLfloat y);
    void setPosition(vec3& pos);
    void reset();
};

#endif
