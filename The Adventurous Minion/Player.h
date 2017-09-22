#pragma once
#include <gl/glut.h>
class Player {

private:
	static constexpr float enabledColor[3] = { 0.0f,0.47f,0.196f },
		disabledColor[3] = { 1.0f,0.25f,0.0f };
	GLfloat playerSize;
	int deltaRotation, jumpDirection;
	double jumpZ;
	void drawArms();
	void drawPants();
	void drawHead();
	void drawBody();
	void gameOverAnimation();
public:
	bool jumping = false, gameOver = false;
	int theta, beta;//Theta used for idle animation, beta for in-game animation
	Player(GLfloat _playerSize);
	void drawPlayer(bool _gamePaused);
	void jump(int direction);
};