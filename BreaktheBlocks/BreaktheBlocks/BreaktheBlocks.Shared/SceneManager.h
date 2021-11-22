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

		GameObject Balls[200]; // �ִ� ���� 200���� ���� 
		GameObject Blocks[MAXBLOCKCOLCOUNT][MAXBLOCKROWCOUNT];// ���� 5�� ���� 3*5�� �ִ� --> 75���� ���
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

