#pragma once
#include <Renderer.h>
#include <InputManager.h>
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

class SceneManager
{
	private:
		Renderer* renderer;

		GameObject Balls[200]; // 최대 개수 200개로 설정 
		GameObject Blocks[MAXBLOCKCOLCOUNT][MAXBLOCKROWCOUNT];// 가로 5개 세로 3*5개 최대 --> 75개면 충분
		GameObject Walls[4];

		InputManager* inputManager;
		StageState stageState = WAIT;
		GLboolean isGameOver = false;
		
		GLuint roundCount = 1;
		const GLuint screenWidth;
		const GLuint screenHeight;
		std::deque<GLuint> Number;
		GLuint GenBlockProbability = 6;

	public:
		SceneManager(GLuint width, GLuint height);
		~SceneManager();

		void updateScene();
		void input(int32_t actionType, GLfloat x, GLfloat y);
		void initBlockLine();
		void setBlockPos(GLuint nowCol, GLuint nowRow, const GLuint& width, const GLuint& height,
			GLuint afterCol, GLuint afterRow);
		void checkCollision();
};

