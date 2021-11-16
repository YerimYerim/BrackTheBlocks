#pragma once
#include "GameUtility.h"
enum CollisionDirection
{
	VERTICAL, HORIZONTAL
};
class GameObject
{
	private:
		vec3 Scale = { 1,1,1 };
		vec3 Color = {0,0,0};

	protected:	

	public:
		vec3 Position = { 0.0f,0.0f,0.0f};	
		GLfloat* vertexPosition;
		GLfloat* colorPosition;

		GLint vertexPoseSize;
		GLint colorPoseSize;

		GLint drawCount;
		GLuint vertexBuffer;
		GLuint colorBuffer;

		GLboolean isActive = false;
		GLboolean isMove= false;

		GLint hp = 0;
		vec3 moveDirection = { 0,0,0 };
		GameObject();	
		GameObject(const GLfloat* vertexPos, const GLfloat* colorPos, GLint vertexSize, GLint colorSize);
		~GameObject();

		vec3 getScale();
		void setScale(GLfloat x, GLfloat y);
		void changeDirection(CollisionDirection direction);
		void setPosition(GLfloat deltaX, GLfloat deltaY);
		GLboolean CheckCollider(GameObject& object);

		void addForce(vec3& direction);
		void physicsUpdate(GLfloat Speed);

};

