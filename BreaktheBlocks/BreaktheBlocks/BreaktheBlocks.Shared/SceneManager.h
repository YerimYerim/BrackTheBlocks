#pragma once
#include <Renderer.h>
#include <InputManager.h>
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
		GLuint roundCount = 1;

	public:
		SceneManager(GLuint width, GLuint height);
		~SceneManager();

		void updateScene();
		void input(int32_t actionType, GLfloat x, GLfloat y);
		void initBlockLine(int lineNum);
		
		void checkCollision();
};

