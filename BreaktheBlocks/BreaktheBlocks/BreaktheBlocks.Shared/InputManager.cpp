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

		direction = Normalize(direction);
	}
}
void InputManager::inputTouchOff(GameObject& gameobject)
{
	if (isShootReady == true)
	{
		// 발사!
		gameobject.addForce(direction);
		gameobject.setMoveActive(true);
	}
	else if (isShootReady == false)
	{
	}
	inputBoolReset();
}

void InputManager::inputBoolReset()
{
	isTouched = false;
	isShootReady = false;
	direction = { 0,0,0 };
}

