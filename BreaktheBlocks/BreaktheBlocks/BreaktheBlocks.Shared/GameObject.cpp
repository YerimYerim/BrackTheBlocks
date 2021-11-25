#include "GameObject.h"

void GameObject::changeDirection(CollisionDirection direction)
{
	switch (direction)
	{
	case VERTICAL:
		moveDirection.x = -moveDirection.x;
		break;
	case HORIZONTAL:
		moveDirection.y = -moveDirection.y;
		break;
	default:
		break;
	}
}

void GameObject::setPosition(GLfloat deltaX = NULL, GLfloat deltaY = NULL)
{
	if (deltaX == NULL)
	{
		deltaX = Position.x;
	}
	if (deltaY == NULL)
	{
		deltaY = Position.y;
	}
	
	Position.x = deltaX;
	Position.y = deltaY;
}

GameObject::GameObject()
{
}

GameObject::GameObject(const GLfloat *vertexPos, const GLfloat *colorPos , GLint vertexSize, GLint colorSize)
{
	Position = { 0.0f,0.0f,0.0f };
	vertexPoseSize = vertexSize / sizeof(GLint);
	colorPoseSize = colorSize / sizeof(GLint);

	vertexPosition = new GLfloat [vertexPoseSize];
 	colorPosition = new GLfloat[colorPoseSize];

	memcpy(&vertexPosition, &vertexPos, sizeof(vertexPos));
	memcpy(&colorPosition, &colorPos, sizeof(colorPos));
}

GameObject::~GameObject()
{
}

vec3 GameObject::getScale()
{
	return Scale;
}

void GameObject::setScale(GLfloat x, GLfloat y)
{
	Scale.x = x;
	Scale.y = y;
}

GLboolean GameObject::CheckCollider(GameObject& Circle)
{
	vec3 LeftTop = {0,0,0};
	LeftTop.x = Position.x - getScale().x * 0.5f;
	LeftTop.y = Position.y + getScale().y * 0.5f;

	vec3 RightBottom = { 0,0,0 };
	RightBottom.x = Position.x + getScale().x * 0.5f;
	RightBottom.y = Position.y - getScale().y * 0.5f;

	GLfloat circleScale = Circle.getScale().x * 0.5f;
	
	//vertical 확장 후 충돌
	if (Circle.Position.x > LeftTop.x - circleScale	&& Circle.Position.x < RightBottom.x + circleScale )	 //-----------
	{																										 //r 만큼 확장된 범위
		if (Circle.Position.y > RightBottom.y - circleScale && Circle.Position.y < LeftTop.y + circleScale)	 //----------
		{
			if (Circle.Position.y > RightBottom.y && Circle.Position.y < LeftTop.y) // ㅇ좌 & 우 
			{
				// 왼쪽 오른쪽에서 충돌
				Circle.changeDirection(VERTICAL);
				isActive = false;
				return true;
			}
			else if (Circle.Position.x > LeftTop.x && Circle.Position.x < RightBottom.x) //위or 아래에서 충돌된것
			{
				Circle.changeDirection(HORIZONTAL);
				isActive = false;
				return true;
			}
			else if(powf(Position.x - Circle.Position.x,2) + powf(Position.y - Circle.Position.y,2) 
				< powf(circleScale + getScale().x,2) + powf(circleScale + getScale().y, 2))// 꼭짓점
			{
				Circle.changeDirection(VERTICAL);
				Circle.changeDirection(HORIZONTAL);
				isActive = false;
				return true;
			}
		}
	}
	return false;
}

void GameObject::addForce(vec3& direction)
{
	moveDirection.x = direction.x;
	moveDirection.y = direction.y;
}

void GameObject::physicsUpdate(GLfloat Speed, GLfloat& deltatime)
{
	Position.x += moveDirection.x * Speed *( 1.0f/deltatime);
	Position.y += moveDirection.y * Speed *( 1.0f/deltatime);
}
void GameObject::setActive(GLboolean isactive)
{
	isActive = isactive;
}

void GameObject::setHp(GLint hp)
{
	Hp = hp;
}

GLint GameObject::getHp()
{
	return Hp;
}

void GameObject::setMoveActive(GLboolean ismove)
{
	isMove = ismove;
}

GLboolean GameObject::getActive()
{
	return isActive;
}

GLboolean GameObject::getMoveActive()
{
	return isMove;
}

void GameObject::addPosition(GLfloat x, GLfloat y)
{
	Position.x += x;
	Position.y += y;

}

