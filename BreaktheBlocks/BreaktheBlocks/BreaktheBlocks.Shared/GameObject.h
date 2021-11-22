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
		vec3 moveDirection = { 0,0,0 };

		GLboolean isActive = false;
		GLboolean isMove = false;
		GLint hp = 0;

public:
		vec3 Position;	
		GLfloat* vertexPosition;
		GLfloat* colorPosition;

		GLint vertexPoseSize;
		GLint colorPoseSize;

		GLint drawCount;
		GLuint vertexBuffer;
		GLuint colorBuffer;

		GameObject();	
		GameObject(const GLfloat* vertexPos, const GLfloat* colorPos, GLint vertexSize, GLint colorSize);
		~GameObject();

		void setScale(GLfloat x, GLfloat y);
		vec3 getScale();

		void setPosition(GLfloat deltaX, GLfloat deltaY);
		
		void setActive(GLboolean isactive);
		GLboolean getActive();

		void setMoveActive(GLboolean ismove);
		GLboolean getMoveActive();
		
		GLboolean CheckCollider(GameObject& object);
		void physicsUpdate(GLfloat Speed);
		void addForce(vec3& direction);
		void changeDirection(CollisionDirection direction);
};

