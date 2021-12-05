#include "SceneManager.h"


SceneManager::SceneManager(GLuint width, GLuint height):screenWidth(width),screenHeight(height),
GameWorldWidth(300.0f) , GameWorldHeight(300.0f)
{
	//android.resource://BreaktheBlocks.Android.Packaging//holstein
	//initText2D("src/main/res/raw/Holstein.dds"); 
	//initText2D("/data/user/0/com.BreaktheBlocks/files/holstein.dds"); 
	//android.resource://com.your.package/raw/filename
	renderer = new Renderer(screenWidth, screenHeight);
	Particles = new ParticleManager(1,0,0,0,0,1,0,0,0.5,1000);
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
			Blocks[i][j].setColor(255.0f / 255.0f , 115.0f / 255.0f, 88 / 255.0f);
		}
		BlockLineArr.push_back(i);
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

	renderFunc = std::bind(&SceneManager::setBallActiveTrue, this);
	initBlockLine();


}

SceneManager::~SceneManager()
{
}

void SceneManager::updateScene()
{
	updateDeltaTime(deltaTime, lastTime);
	renderer->updateRenderer();

	Particles->RenderUpdate(deltaTime);
	renderer->drawParticle(Particles->particles[0], true, true, true);
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
		if (Balls[i].getActive() == true)
		{
			renderer->drawGameObject(Balls[i]);
			if (Balls[i].getMoveActive() == true)
			{
				Balls[i].physicsUpdate(15.0f, deltaTime);
			}
		}
	}
	#pragma endregion

	#pragma region WallUpdate
	for (int i = 0; i < MAXWALLCOUNT; ++i)
	{
		renderer->drawGameObject(Walls[i]);
	}
	#pragma endregion
	switch (stageState)
	{
	case WAIT:
	case SHOOT:
	{
		checkCollision();
		if (nowBallShootingCount < roundCount)
		{
			Timer(deltaTime, durationTime, 1, renderFunc);
		}
	}break;
	case END:
	{
		nowBallShootingCount = 1; 
	}break;
	default:
		break;
	}

	//printText2D(text, 0, 0, 50);
}

void SceneManager::setBallActiveTrue()
{
	Balls[nowBallShootingCount].setActive(true);
	++nowBallShootingCount;
}

void SceneManager::input(int32_t actionType, GLfloat x, GLfloat y)
{
	#ifdef __ANDROID__
 	if (stageState == END)
	{
		if (actionType == AKEY_EVENT_ACTION_UP) // 터치 off
		{
			for (int i = 0; i < roundCount; ++i)
			{
				if (inputManager->inputTouchOff(Balls[i]) == true && i == 0)
				{
					stageState = SHOOT;
				}
			}
			inputManager->inputBoolReset();
			
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
			GLint HP = std::min(MAXBALLCOUNT, (int)roundCount);
			GLfloat random = std::min(  HP * 0.005f + rand() % 100 * 0.01f + 0.2f, 0.7f);
			Blocks[BlockLineArr.front()][j].setHp(HP);
			Blocks[BlockLineArr.front()][j].setColor(255.0f, random, random);
			Blocks[BlockLineArr.front()][j].setActive(true);
		}
		//2. 마지막 칸이 active 되어있는지 확인한다.-->over인지 아닌지 결정
		if (isGameOver == false && Blocks[BlockLineArr.back()][j].getActive())
		{
			isGameOver = true;
		}
	}

	BlockLineArr.push_front(BlockLineArr.back());
	BlockLineArr.pop_back();

	//3. 모든칸을 무브!
	for (int i = 0; i < MAXBLOCKCOLCOUNT; ++i)
	{
		for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
		{
			setBlockPos(BlockLineArr.at(i), j, i, j);
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
	int moveFalseCount = 0;
	for (int ballcnt = 0; ballcnt < roundCount; ++ballcnt)
	{
		if (Balls[ballcnt].getMoveActive() == true)
		{
			#pragma region BlockCheckCollider
			for (int i = 0; i < MAXBLOCKCOLCOUNT; ++i)
			{
				for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
				{
					if (Blocks[i][j].getActive())
					{
						Blocks[i][j].CheckCollider(Balls[ballcnt]);
					}
				}
			}
			#pragma endregion

			#pragma region WallCheckCollider
			for (int i = 0; i < MAXWALLCOUNT; ++i)
			{
				if (Walls[i].CheckCollider(Balls[ballcnt]))
				{
					if (i == BOTTOM)
					{
						Balls[ballcnt].setPosition(Balls[ballcnt].Position.x, -150.0f + Balls[ballcnt].getScale().y * 0.5f + Walls[BOTTOM].getScale().y * 0.5f);
						Balls[ballcnt].setMoveActive(false);
						Balls[ballcnt].setActive(false);
	
						if (firtFallBallNum == -1)//첫공이 바닥과 충돌시 WAIT 로 설정 후 저장
						{
							firtFallBallNum = ballcnt;
							Balls[ballcnt].setActive(true);
							stageState = WAIT; 
						}
						else
						{
							Balls[ballcnt].setPosition(Balls[firtFallBallNum].Position.x , Balls[firtFallBallNum].Position.y);
						}
					}
				}
			}
			#pragma endregion
		}
		if (Balls[ballcnt].getMoveActive() == false)
		{
			moveFalseCount++;
		}
		if (moveFalseCount  == roundCount) // 공이 모두 떨어지면
		{
			stageState = END;
			roundCount += 1;
			//처음 떨어진공 안보이게 한후 첫번째공 보이도록
			Balls[firtFallBallNum].setActive(false);
			Balls[0].setActive(true);
			//다음꺼 위치 바꿔주기
			if (ballcnt < MAXBALLCOUNT)
			{
				Balls[ballcnt + 1].setPosition(Balls[firtFallBallNum].Position.x, Balls[firtFallBallNum].Position.y);
			}
			initBlockLine();
			firtFallBallNum = -1;
			moveFalseCount = 0;
		}
	}

}

void SceneManager::Timer(float& deltatime, GLfloat& durationSec, int endSecond,const std::function<void()>& Function)
{
	if (durationSec > endSecond)
	{
		Function();
		durationSec = 0;
	}
	else
	{
		durationSec += deltatime;
	}
}
