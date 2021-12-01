#pragma once
#include "Renderer.h"
#include "Text.h"
#include "InputManager.h"
#include <deque>
#define MAXBALLCOUNT 200
#define MAXWALLCOUNT 4
#define MAXBLOCKCOLCOUNT 9
#define MAXBLOCKROWCOUNT 6

enum StageState
{
	WAIT = 0,
	SHOOT = 1,
	END = 2,
};
enum Wall
{
	BOTTOM,TOP,LEFT,RIGHT
};
class SceneManager
{
	private:
		Renderer* renderer;
		InputManager* inputManager;

		GameObject Balls[200]; // �ִ� ���� 200���� ���� 
		GameObject Blocks[MAXBLOCKCOLCOUNT][MAXBLOCKROWCOUNT];// ���� 5�� ���� 3*5�� �ִ� --> 75���� ���
		GameObject Walls[4];
		StageState stageState = END;
		GLboolean isGameOver = false;
		
		GLuint roundCount = 1;
		const GLuint screenWidth;
		const GLuint screenHeight;		
		
		const GLfloat GameWorldWidth;
		const GLfloat GameWorldHeight;
		std::deque<GLuint> BlockLineArr;
		GLuint GenBlockProbability = 6;

		std::chrono::system_clock::time_point lastTime = std::chrono::system_clock::now();
		GLfloat deltaTime;
		GLfloat durationTime = 0;
		GLint nowBallShootingCount = 0;
		int firtFallBallNum = -1;
		std::function<void()> renderFunc;
	public:
		SceneManager(GLuint width, GLuint height);
		~SceneManager();

		void updateScene();
		void setBallActiveTrue();
		void input(int32_t actionType, GLfloat x, GLfloat y);
		void initBlockLine();
		void setBlockPos(GLuint nowCol, GLuint nowRow, GLfloat afterCol, GLfloat afterRow);
		void checkCollision();
		void Timer(float& deltatime, GLfloat& durationSec, int endSecond,const std::function<void()>& renderFunc);
};

