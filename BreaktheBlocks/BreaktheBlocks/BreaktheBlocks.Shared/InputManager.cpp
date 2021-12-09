#pragma once

#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::InputManager(GLint ScreenWidth, GLint ScreeHeight)
{
	screenWidth = ScreenWidth;
	screenHeight = ScreeHeight;
	inputBoolReset();
}

InputManager::~InputManager()
{
}

void InputManager::setScreenSize(GLint ScreenWidth, GLint ScreeHeight)
{
	screenWidth = ScreenWidth;
	screenHeight = ScreeHeight;
	inputBoolReset();
}

void InputManager::inputTouchOn(GLfloat inputX, GLfloat inputY)
{
	GLfloat convertedX = 0;
	GLfloat convertedY = 0;


	transScreenToGL(screenWidth, screenHeight, inputX, inputY, &convertedX, &convertedY);
	nowPosition.x = convertedX;
	nowPosition.y = convertedY;

	// 첫 터치
	if (isTouched == false) 
	{
		isTouched = true;
		startTouchPosition.x = convertedX;
		startTouchPosition.y = convertedY;
	}
	// 터치 이후 아래로 내리진 않은상태 
	else if (isTouched == true && isShootReady == false) 
	{
		if (nowPosition.y < startTouchPosition.y)
		{
			isShootReady = true;
		}
	}
	// 터치 이후 아래로 내려 발사 준비 후 각도를 조절하는 상태
	else if (isTouched == true && isShootReady == true) 
	{
		direction.x = startTouchPosition.x - nowPosition.x;
		direction.y = startTouchPosition.y - nowPosition.y;

		float tempAngle = atan2(direction.y, direction.x) * 180.0f / 3.14f;
		if (tempAngle < 20)
		{
			direction.x = cos(20 * 3.14f / 180.0f);
			direction.y = sin(20 * 3.14f / 180.0f);
		}
		if (tempAngle > 160)
		{
			direction.x = cos(160 * 3.14f / 180.0f);
			direction.y = sin(160 * 3.14f / 180.0f);
		}
		direction = Normalize(direction);
	}
}
GLboolean InputManager::inputTouchOff(GameObject& gameobject)
{
	if (isShootReady == true)
	{
		// 발사!
		float tempAngle = atan2(direction.y, direction.x) * 180.0f / 3.14f ;
		if (tempAngle >= 20 && tempAngle <= 160)
		{	
			gameobject.addForce(direction);
			gameobject.setMoveActive(true); 
			return true;
		}
		else
		{

			return false;
		}
	}
	else if (isShootReady == false)
	{
	}
	return false;
}

void InputManager::inputBoolReset()
{
	isTouched = false;
	isShootReady = false;
	direction = { 0,0,0 };
}

