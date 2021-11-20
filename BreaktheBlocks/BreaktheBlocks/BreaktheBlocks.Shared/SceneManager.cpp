#include "SceneManager.h"

SceneManager::SceneManager(GLuint width, GLuint height)
{
	renderer = new Renderer(width, height);
	inputManager = new InputManager(width, height);
	for (int i = 0; i < MAXBLOCKCOLCOUNT; ++i)
	{
		for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
		{
			renderer->setupRenderer(Blocks[i][j], RECTANGLE);
			GLfloat xPos;
			GLfloat yPos;
			Blocks[i][j].setScale(1.0f/ MAXBLOCKROWCOUNT, 1.0f / MAXBLOCKCOLCOUNT);
			transScreenToGL(width, height, width * Blocks[i][j].getScale().x * (j + 0.5f) ,
				(height - width)* 0.5f + i * width * Blocks[i][j].getScale().y, &xPos, &yPos);			
			Blocks[i][j].setPosition(xPos, yPos);
			Blocks[i][j].setScale(1.0f / MAXBLOCKROWCOUNT * 0.95, 1.0f / MAXBLOCKCOLCOUNT  * 0.95);
			Blocks[i][j].isActive = true;
			Blocks[i][j].isMove = false;
		}
	}
	for (int i = 0; i < MAXBALLCOUNT; ++i)
	{
		renderer->setupRenderer(Balls[i], CIRCLE);
		Balls[i].setScale(0.06f, 0.06f);
		Balls[i].setPosition(0,-1 + 0.1f);
		Balls[i].isActive = false;
		Balls[i].isMove = false;
	}
	Balls[0].isActive = true;
	for (int i = 0; i < MAXWALLCOUNT; ++i)
	{
		renderer->setupRenderer(Walls[i], RECTANGLE);
		Walls[i].setScale(1.0f, 1.0f);
		Walls[i].isActive = true;
		Walls[i].isMove = false;

	}
	Walls[0].setPosition(0, -2.0f);
	Walls[1].setPosition(0, 2.0f);
	Walls[2].setPosition(-2, 0);
	Walls[3].setPosition(2, 0);

}

SceneManager::~SceneManager()
{
}



void SceneManager::updateScene()
{
	renderer->updateRenderer();
	
	for (int i = 0; i < MAXBLOCKCOLCOUNT; ++i)
	{
		for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
		{
			if(Blocks[i][j].isActive)
				renderer->drawGameObject(Blocks[i][j]);
		}
	}
	for (int i = 0; i < MAXBALLCOUNT; ++i)
	{
		if (Balls[i].isActive)
			renderer->drawGameObject(Balls[i]);
		if (Balls[i].isMove)
			Balls[i].physicsUpdate(0.02f);
	}
	//for (int i = 0; i < MAXWALLCOUNT; ++i)
	//{
	//	renderer->drawGameObject(Walls[i]);

	//}
	checkCollision();
}



void SceneManager::input(int32_t actionType, GLfloat x, GLfloat y)
{
	if (actionType == AKEY_EVENT_ACTION_UP) // 터치 off
	{
		if (stageState == WAIT)
		{
			inputManager->inputTouchOff(Balls[0]);
			stageState = SHOOT;
			roundCount += 1;
		}
	}
	else if (actionType == AKEY_EVENT_ACTION_DOWN)// 첫 터치
	{
		inputManager->inputTouchOn(x, y);
	}
	else // 드래그 
	{
		inputManager->inputTouchOn(x, y);
	}
}

void SceneManager::initBlockLine(int RandomNum)
{
}

void SceneManager::checkCollision()
{
	if (stageState == SHOOT)
	{
		for (int i = 0; i < MAXBLOCKCOLCOUNT; ++i)
		{
			for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
			{
				if (Blocks[i][j].isActive)
				{
					Blocks[i][j].CheckCollider(Balls[0]);
				}
			}
		}
		for (int i = 0; i < MAXWALLCOUNT; ++i)
		{
			if (Walls[i].CheckCollider(Balls[0]) && i == 0)
			{
				Balls[0].isMove = false;
				stageState = WAIT; // 임시로 Wait --> 나중에 모든 공이 아래로 떨어질때까지 end 상태로 둘것
			}
		}
	}
}
