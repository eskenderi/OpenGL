#include <Player.h>
#include <iostream>
using namespace std;

double tempZ = 0, deltaJumpZ;
Player::Player(GLfloat _playerSize) {
	playerSize = _playerSize;
	theta = 0;
	beta = 145;
	jumpZ = 0.3;
	deltaRotation = 1;
}
void Player::drawArms() {
//Draw arms
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3d(0, 0, 0);
	glRotated(-45, 0, 0, 1);
	glScaled(2, 0.2, 1.5);
	glTranslated(0,0, -0.08);
	glutSolidSphere(0.08, 10, 10);
	glPopAttrib();
	glPopMatrix();
}

void Player::drawPants() {
//Draw pants
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3d(0,0.2, 0.57);
	glScaled(1, 1, 1.2);
	glTranslated(0, 0, -0.1);
	glutSolidSphere(playerSize/1.8, 20, 20);
	glPopAttrib();
	glPopMatrix();
}
void Player::drawHead() {
//Draw Head
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3d(0.5, 0.5, 1);

	glScaled(0.85, 0.85, 0.6);
	glTranslated(-0.05,-0.05,0.17);
	glRotated(70, 1, 0, 0);
	glRotated(-45, 0, 1, 0);
		//Draw Eye
		glPushAttrib(GL_CURRENT_BIT);
		glColor3d(0.588,0.3333,0);
		glutSolidSphere(0.04, 15,15);
		glPopAttrib();
	glutSolidTorus(0.03, 0.05, 30, 10);
	glPopAttrib();
	glPopMatrix();
	//Draw Lips
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3d(1, 0, 0);

	glScaled(0.85, 0.85, 0.2);
	glTranslated(-0.06, -0.06, 0.08);
	glRotated(70, 1, 0, 0);
	glRotated(-45, 0, 1, 0);

	glutSolidTorus(0.03, 0.05, 30, 20);
	glPopAttrib();
	glPopMatrix();
}
void Player::drawBody() {
//Draw body
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3d(0.94, 0.953, 0.257);
	glScaled(1,1,2);
	glutSolidSphere(playerSize/2,20,20);
	glPopAttrib();
	glPopMatrix();
}

void Player::drawPlayer(bool gamePaused) {
	glPushMatrix();
	if (gameOver== false) {
		if (tempZ <= 0 ) {
				jumping = false;
			}
		if (gamePaused) {//Handle player in-place animation
			if (theta < -45 || theta > 45)
				deltaRotation *= -1;;
			theta += deltaRotation;
			glRotated(theta, 0, 0, 1);
		}
		else
			if (jumping) {
				if (tempZ >= jumpZ)
					deltaJumpZ *= -1;
				glTranslated(0, 0, tempZ);
				tempZ += deltaJumpZ;
				if (jumpDirection == 0) {//Jump on x axis
					glRotated(145, 0, 0, 1);
				}
				else {//y axis
					glRotated(215, 0, 0, 1);
				}
			}
			else {//right ->145, left -> 215
		if (beta == 216 || beta == 144)
			deltaRotation *= -1;
		beta += deltaRotation;

		glRotated(beta, 0, 0, 1);
		float angle = (2*(beta - 145) / 7) - 10;//Map 70 degrees to [-10,10] range for smooth rotation
		if (deltaRotation > 0)
			glRotated(angle, 1, 1, 0);
		else
			glRotated(angle, 1, 1, 0);
	}
	}
	drawArms();
	
	drawPants();
	
	drawHead();
	
	drawBody();
	glPopMatrix();
}
void Player::jump(int direction) {
	if (jumping)
		return;
	jumping = true;
	deltaJumpZ = 0.02;
	tempZ = deltaJumpZ;
	jumpDirection = direction; //0 for x-axis, 1 for y-axis
}