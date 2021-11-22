#include "SceneManager.h"

SceneManager::SceneManager(GLuint width, GLuint height):screenWidth(width),screenHeight(height)
{
	renderer = new Renderer(screenWidth, screenHeight);
	inputManager = new InputManager(screenWidth, screenHeight);
	for (int i = 0; i < MAXBLOCKCOLCOUNT; ++i)
	{
		for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
		{
			renderer->setupRenderer(Blocks[i][j], RECTANGLE);
			setBlockPos(i, j, screenWidth, screenHeight, i, j);
			Blocks[i][j].setMoveActive(false);
			Blocks[i][j].setActive(false);
		}
		Number.push_back(i);
	}
	for (int i = 0; i < MAXBALLCOUNT; ++i)
	{
		renderer->setupRenderer(Balls[i], CIRCLE);
		Balls[i].setScale(0.06f, 0.06f);
		Balls[i].setPosition(0,-1 + 0.1f);
		Balls[i].setActive(false);
		Balls[i].setMoveActive(false);
	}
	Balls[0].setActive(true);
	for (int i = 0; i < MAXWALLCOUNT; ++i)
	{
		renderer->setupRenderer(Walls[i], RECTANGLE);
		Walls[i].setScale(1.0f, 1.0f);
		Walls[i].setActive(true);
		Walls[i].setMoveActive(false);

	}
	Walls[0].setPosition(0, -2.0f);
	Walls[1].setPosition(0, 2.0f);
	Walls[2].setPosition(-2, 0);
	Walls[3].setPosition(2, 0);
	initBlockLine();
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
			if(Blocks[i][j].getActive())
				renderer->drawGameObject(Blocks[i][j]);
		}
	}
	for (int i = 0; i < MAXBALLCOUNT; ++i)
	{
		if (Balls[i].getActive())
			renderer->drawGameObject(Balls[i]);
		if (Balls[i].getMoveActive())
			Balls[i].physicsUpdate(0.02f);
	}
	checkCollision();
}



void SceneManager::input(int32_t actionType, GLfloat x, GLfloat y)
{
	if (actionType == AKEY_EVENT_ACTION_UP) // ��ġ off
	{
		if (stageState == WAIT)
		{
			inputManager->inputTouchOff(Balls[0]);
			stageState = SHOOT;
			roundCount += 1;
		}
	}
	else if (actionType == AKEY_EVENT_ACTION_DOWN)// ù ��ġ
	{
		inputManager->inputTouchOn(x, y);
	}
	else // �巡�� 
	{
		inputManager->inputTouchOn(x, y);
	}
}

void SceneManager::initBlockLine()
{
	for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
	{
		//1. �� ���� �ִ� �� ��� �������ְ�
		if (rand() % 10 < GenBlockProbability)
		{
			Blocks[Number.front()][j].setActive(true);
		}
		//2. ������ ĭ�� active �Ǿ��ִ��� Ȯ���Ѵ�.-->over���� �ƴ��� ����
		if (isGameOver == false && Blocks[Number.back()][j].getActive())
		{
			isGameOver = true;
		}
	}
	Number.push_front(Number.back());
	Number.pop_back();

	//3. ���ĭ�� ����!

	for (int i = 0; i < MAXBLOCKCOLCOUNT; ++i)
	{
		for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
		{
			setBlockPos(Number.at(i), j, screenWidth, screenHeight, i, j);
		}
	}

}

void SceneManager::setBlockPos(GLuint nowCol, GLuint nowRow, const GLuint& width, const GLuint& height,
	GLuint afterCol, GLuint afterRow)
{
	GLfloat xPos;
	GLfloat yPos;
	Blocks[nowCol][nowRow].setScale(1.0f / MAXBLOCKROWCOUNT, 1.0f / MAXBLOCKCOLCOUNT);
	transScreenToGL(width, height, width * Blocks[nowCol][nowRow].getScale().x * (afterRow + 0.5f),
		(height - width) * 0.5f + afterCol * width * Blocks[nowCol][nowRow].getScale().y, &xPos, &yPos);
	Blocks[nowCol][nowRow].setPosition(xPos, yPos);
	Blocks[nowCol][nowRow].setScale(1.0f / MAXBLOCKROWCOUNT * 0.95, 1.0f / MAXBLOCKCOLCOUNT * 0.95);
}

void SceneManager::checkCollision()
{
	if (stageState == SHOOT)
	{
		for (int i = 0; i < MAXBLOCKCOLCOUNT; ++i)
		{
			for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
			{
				if (Blocks[i][j].getActive())
				{
					Blocks[i][j].CheckCollider(Balls[0]);
				}
			}
		}
		for (int i = 0; i < MAXWALLCOUNT; ++i)
		{
			if (Walls[i].CheckCollider(Balls[0]) && i == 0)
			{
				Balls[0].setMoveActive(false);
				stageState = WAIT; // �ӽ÷� Wait --> ���߿� ��� ���� �Ʒ��� ������������ end ���·� �Ѱ�
				initBlockLine();
			}
		}
	}
}
