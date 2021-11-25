#include "SceneManager.h"

SceneManager::SceneManager(GLuint width, GLuint height):screenWidth(width),screenHeight(height),
GameWorldWidth(300.0f) , GameWorldHeight(300.0f)
{
	GLfloat tempx;
	GLfloat tempy;
	renderer = new Renderer(screenWidth, screenHeight);
	inputManager = new InputManager(screenWidth, screenHeight);
	#pragma region setBlocks
	for (int i = 0; i < MAXBLOCKCOLCOUNT; ++i)
	{		
		for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
		{
			renderer->setupObjectRenderer(Blocks[i][j], RECTANGLE);
			setBlockPos(i, j, i, j);
			Blocks[i][j].setMoveActive(false);
			Blocks[i][j].setActive(false);
		}
		Number.push_back(i);

	}
	#pragma endregion	
	#pragma region setWall
	//SET WALL
	for (int i = 0; i < MAXWALLCOUNT; ++i)	//SET WALL
	{
		renderer->setupObjectRenderer(Walls[i], RECTANGLE);
		Walls[i].setActive(true);
		Walls[i].setMoveActive(false);
	}
	Walls[BOTTOM].setPosition(0, -150.0f);
	Walls[BOTTOM].setScale(300.0f, 5.0f);

	Walls[TOP].setPosition(0, 150.0f);
	Walls[TOP].setScale(300.0f, 5.0f);

	Walls[LEFT].setPosition(-150.0f, 0);
	Walls[LEFT].setScale(5.0f, 300.0f);

	Walls[RIGHT].setPosition(150.0f, 0);
	Walls[RIGHT].setScale(5.0f, 300.0f);
	#pragma endregion
	#pragma region setBalls
	for (int i = 0; i < MAXBALLCOUNT; ++i)
	{
		renderer->setupObjectRenderer(Balls[i], CIRCLE);

		Balls[i].setScale(10.0f, 10.0f);
		Balls[i].setPosition(0, -150.0f + Balls[0].getScale().y * 0.5f + Walls[BOTTOM].getScale().y * 0.5f);
		Balls[i].setActive(false);
		Balls[i].setMoveActive(false);
	}
	Balls[0].setActive(true);
	#pragma endregion


	initBlockLine();
}

SceneManager::~SceneManager()
{
}

void SceneManager::updateScene()
{
	updateDeltaTime(deltaTime,lastTime);

	renderer->updateRenderer();

	#pragma region BlockUpdate
	for (int i = 0; i < MAXBLOCKCOLCOUNT; ++i)
	{
		for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
		{
			if(Blocks[i][j].getActive())
				renderer->drawGameObject(Blocks[i][j]);
		}
	}
	#pragma endregion

	#pragma region BallUpdate
	for (int i = 0; i < MAXBALLCOUNT; ++i)
	{
		if (Balls[i].getActive())
			renderer->drawGameObject(Balls[i]);
		if (Balls[i].getMoveActive())
			Balls[i].physicsUpdate(10.0f, deltaTime);
	}
	#pragma endregion

	#pragma region WallUpdate
	for (int i = 0; i < MAXWALLCOUNT; ++i)
	{
		renderer->drawGameObject(Walls[i]);
	}
	#pragma endregion
	checkCollision();
//	initBlockLine();
}


void SceneManager::input(int32_t actionType, GLfloat x, GLfloat y)
{
	#ifdef __ANDROID__
	if (stageState == WAIT)
	{
		if (actionType == AKEY_EVENT_ACTION_UP) // 터치 off
		{
			inputManager->inputTouchOff(Balls[0]);
			roundCount += 1;
			stageState = SHOOT;
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
	#elif __APPLE__

	#endif
}

void SceneManager::initBlockLine()
{
	for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
	{
		//1. 맨 위에 있는 블록 생성해주고
		if (rand() % 10 < GenBlockProbability)
		{
			Blocks[Number.front()][j].setActive(true);
			Blocks[Number.front()][j].setHp(roundCount);
		}
		//2. 마지막 칸이 active 되어있는지 확인한다.-->over인지 아닌지 결정
		if (isGameOver == false && Blocks[Number.back()][j].getActive())
		{
			isGameOver = true;
		}
	}
	//여기가 문젠가
	Number.push_front(Number.back());
	Number.pop_back();

	//3. 모든칸을 무브!
	for (int i = 0; i < MAXBLOCKCOLCOUNT; ++i)
	{
		for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
		{
			setBlockPos(Number.at(i), j, i, j);
		}
	}

}

void SceneManager::setBlockPos(GLuint nowCol, GLuint nowRow, GLfloat afterCol, GLfloat afterRow)
{
	GLfloat blockwidth = (GLfloat)(GameWorldWidth / MAXBLOCKROWCOUNT);
	GLfloat blockheight = (GLfloat)(GameWorldHeight / MAXBLOCKCOLCOUNT);

	Blocks[nowCol][nowRow].setScale(blockwidth, blockheight);
	Blocks[nowCol][nowRow].setPosition(-150.0f + blockwidth * (0.501f+ afterRow), 150.0f - blockheight *(0.501f + afterCol));
	Blocks[nowCol][nowRow].setScale(blockwidth * 0.95f, blockheight * 0.95f);
}

void SceneManager::checkCollision()
{
	if (stageState == SHOOT)
	{
		#pragma region BlockCheckCollider
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
		#pragma endregion

		#pragma region WallCheckCollider
		for (int i = 0; i < MAXWALLCOUNT; ++i)
		{
			if (Walls[i].CheckCollider(Balls[0]) && i == 0 && stageState == SHOOT)
			{
				initBlockLine();
				stageState = WAIT; // 임시로 Wait --> 나중에 모든 공이 아래로 떨어질때까지 end 상태로 둘것
				Balls[0].setPosition(Balls[0].Position.x, -150.0f + Balls[0].getScale().y * 0.5f + Walls[BOTTOM].getScale().y * 0.5f);
				Balls[0].setMoveActive(false);
			}
		}
		#pragma endregion
	}
}
