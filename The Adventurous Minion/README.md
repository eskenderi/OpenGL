# **OpenGL 3D Objects Implementation:**
# **The Adventurous Minion**









Introduction
In this project, I implemented a game by making use of the glut 3D primitives. The player character is supposed to be a Minion, a personage borrowed from the movie “Minions”. It is supposed to collect as many donuts as possible while making sure not to step on a red tile which would melt it down. The plane itself consists of an array of 400 tiles(20x20). Each tile is initially randomly initialized as red or green one. Player is positioned in the tile with coordinates (0,0). The program makes sure there always exist a RANDOM path for the player to follow. 

The controllers of this game are straight forward and can be found below. 

The project itself consists of two classes namely ‘Tile’ and ‘Player’. On each of these classes are implemented the drawing methods and the animation logic. Below I will attach the actual code for all classes and their respective header files.
Player.h
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
public:
	bool jumping = false, gameOver = false;
	int theta, beta;//Theta used for idle animation, beta for in-game animation
	Player(GLfloat _playerSize);
	void drawPlayer(bool _gamePaused);
	void jump(int direction);
};

Player.cpp
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


Tile.h
#pragma once
#include < gl/glut.h>

class Tile {

	private:
		GLfloat sideSizes;
		static constexpr float enabledColor[3] = { 0.0f,0.47f,0.196f },
		disabledColor[3] = { 1.0f,0.25f,0.0f };
		float donutColor[3];
		double donutDeltaX, donutDeltaY, donutTheta = 0, donutBeta = 0;
		bool animating = false;
		int theta = 0, axis = 0;
	public:
		bool enabled = false, hasDonut;
		Tile(GLfloat sideSize, bool enabled, bool hasDonut);
		void drawTile();
};





Tile.cpp
#include <tile.h>
#include <iostream>
using namespace std;


Tile::Tile(GLfloat _sideSizes, bool _enabled, bool _hasDonut) {
	enabled = _enabled;
	sideSizes = _sideSizes;
	hasDonut = _hasDonut;
	
	if (hasDonut) {
		donutColor[0] = (double)rand() / RAND_MAX;//Randomly assign donut color
		donutColor[1] = (double)rand() / RAND_MAX;
		donutColor[2] = (double)rand() / RAND_MAX;
		//Assign donut rotation speeds
		donutDeltaX = fmax((double)rand() / RAND_MAX, 0.5);
		donutDeltaY = fmax((double)rand() / RAND_MAX,0.5);
	}
}
void Tile::drawTile()
{	

	if(hasDonut){//Randomly add a donut on top
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glColor3fv(donutColor);
		glTranslated(0, 0, 0.2);
		donutTheta = (donutTheta > 360) ? 0 : donutTheta;
		donutBeta = (donutBeta > 360) ? 0 : donutBeta;
		donutTheta += donutDeltaX;
		donutBeta += donutDeltaY;
		glRotated(donutTheta, 1, 0, 0);
		glRotated(donutBeta, 0, 1, 0);

		glutSolidTorus(0.04, 0.08, 10, 20);
		glPopAttrib();
		glPopMatrix();
	}
	glPushAttrib(GL_CURRENT_BIT);
	if (enabled)
		glColor3fv(enabledColor);
	else
		glColor3fv(disabledColor);

	double pRatio = ((double)rand() / (RAND_MAX));
	if (enabled == false) {
		//Check if tile is animating
		if (animating) {
			if (theta == 180) {
				theta = 0;
				animating = false;
			}
			else {
				theta += 1;
				switch (axis)
				{
				case 0:
					glRotated(theta, 1, 0, 0);
					break;
				case 1:
					glRotated(theta, 0, 1, 0);
					break;
				}
			}
		}else
			if (pRatio < 0.001) {
				animating = true;
				axis = ((double)rand() / (RAND_MAX)) < 0.5 ? 0 : 1;
			}
	}
	
	glScaled(1,1,0.5);
	glutSolidCube(sideSizes);
	glPopAttrib();
}


Source.cpp (This file contains the main method)
#include <gl/glut.h>
#include <tile.h>
#include <time.h>
#include <string>
#include <iostream>
#include <vector>
#include <Player.h>

using namespace std;

vector<vector<Tile>> tiles;

GLfloat lightPos[] = { -5,2,5,1 }, amb[] = { 0.6,0.5,0.3,6};
GLfloat front_amb_diff[] = { 0.5,0.5,0.1,0,0.8 };
GLfloat back_amb_diff[] = {0.4,0.7,0.1,1.0};
GLfloat specular[] = {0.25,0.25,0.25,0.5};
GLfloat lightTheta = 0, dt = 0.7;

Player player = Player(0.2);
GLfloat tileSide = 0.4, tileSlack = 0.1;
bool gamePaused = true, gameOver = false;
int tilesPerSide = 20, collectedDonuts = 0;
float gameOverZScale = 1;


void buildPath(int i, int j) {
	while (i<tilesPerSide && j<tilesPerSide)
	{
		tiles[i][j].enabled = true;
		if (i + 1 < tilesPerSide && tiles[i + 1][j].enabled) {//Check if adjacent cells are enabled
			i++;//If this is the case, proceed the path to that cell
		}
		else
		if (j + 1 < tilesPerSide && tiles[i][j+1].enabled) {
			j++;
		}
		else//Decide randomly
		if (((double)rand() / (RAND_MAX)) < 0.5)
			i++;
		else
			j++;
	}
}
void initGameObjects() {
	bool enabled, hasDonut;
	for (int i = 0; i < tilesPerSide; i++)
	{	
		vector<Tile> row;
		for (int j = 0; j < tilesPerSide; j++)
		{
			enabled = (double)rand() / (RAND_MAX) < 0.3 ? true : false;
			hasDonut = (double)rand() / (RAND_MAX) < 0.1 ? true : false;

			Tile temp = Tile(tileSide, enabled, hasDonut);
			row.emplace_back(temp);
		}
		tiles.emplace_back(row);
	}
	tiles[0][0].hasDonut = false;
	buildPath(0,0);
}

bool hasPathToSource(int i, int j) {
	if (i < 0 || j < 0)
		return false;
	if (i == 0 && j == 0)
		return true;
	return tiles[i][j].enabled && (hasPathToSource(i-1, j) || hasPathToSource(i, j-1));
}

void drawTiles() {
	
	for (int i = 0; i < tilesPerSide; i++)
	{
		for (int j = 0; j < tilesPerSide; j++) {
			glPushMatrix();
			glTranslated(i*(tileSide + tileSlack)-1.8, j*(tileSide + tileSlack) - 1.8, 0.0);
			tiles[i][j].drawTile();
			glPopMatrix();
		}
	}
}
void drawPlayer() {
	glPushMatrix();
	glTranslated(-1.78, -1.78, 0.3);
	player.drawPlayer(gamePaused);
	glPopMatrix();
}
void writeText(float x, float y, char *string)//Generic method to write the text/digits in the gl window
{
	char *c;
	glRasterPos2i(x, y);

	for (c = string; *c != NULL; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	string text1 = string("Donuts:");
	writeText(-2, 1.5, &(text1)[0u]);
	writeText(-1.5, 1.5, &to_string(collectedDonuts)[0u]);
	//Rotate light position
	glPushMatrix();
	glRotated(lightTheta, 0, 0, 1);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glPopMatrix();
	//Draw game objects
	glPushMatrix();
	glRotated(-70, 1, 0, 0);//Tilt the whole gameobjects on an angle
	glRotated(45, 0, 0, 1);//Rotate around z axis
	drawTiles();
	if (gameOver) {//GameOver procedure and animation
		glPushMatrix();
		glScaled(1, 1, gameOverZScale);
		drawPlayer();
		glPopMatrix();
		gameOverZScale -= 0.005;
		if (gameOverZScale < 0) {
			gameOver = false;
			player.gameOver = false;
			gameOverZScale = 1;
			collectedDonuts = 0;
			initGameObjects();
		}
	}else
		drawPlayer();
	glPopMatrix();
	glutSwapBuffers();
}

void idle(void) {
	if (lightTheta < 360)
		lightTheta += dt;
	else
		lightTheta = dt;
	
	glutPostRedisplay();
}
void addTilesRow() {
	for (int i = 0; i < tilesPerSide; i++)//Swap respective rows
	{
		for (int j = 0; j < tilesPerSide-1; j++)
		{
			tiles[i][j] = tiles[i][j+1];
		}
	}
	int pathsFound = 0;
	for (int i = 0; i < tilesPerSide; i++)//Make sure there exist a path 
	{									//from source to any of the added cells
		bool enabled, hasDonut;
		enabled = (double)rand() / (RAND_MAX) < 0.3 ? true : false;
		hasDonut = (double)rand() / (RAND_MAX) < 0.1 ? true : false;
		tiles[i][tilesPerSide - 1] = Tile(tileSide, enabled, hasDonut);
		if (pathsFound < 2 && hasPathToSource(i, tilesPerSide - 2)) {//Make sure to always mantain at least 1 path
			//pathFound = true;
			buildPath(i, tilesPerSide - 2);
		}
	}
}
void addTilesCol() {
	for (int i = 0; i < tilesPerSide - 1; i++)//Swap respective columns
	{
		for (int j = 0; j < tilesPerSide ; j++)
		{
			tiles[i][j] = tiles[i+1][j];
		}
	}
	for (int j = 0; j < tilesPerSide; j++)//Make the added column feasible
	{
		int pathsFound = 0;
		for (int j = 0; j < tilesPerSide; j++)//Make sure there exists a path
		{									// from the path to any of the added cells
			bool enabled, hasDonut;
			enabled = (double)rand() / (RAND_MAX) < 0.3 ? true : false;
			hasDonut = (double)rand() / (RAND_MAX) < 0.1 ? true : false;
			tiles[tilesPerSide - 1][j] = Tile(tileSide, enabled, hasDonut);
			if (pathsFound <1 && hasPathToSource(tilesPerSide - 2, j)) {//Make sure to always mantain at least 1 path
				pathsFound++;
				buildPath(tilesPerSide - 2, j);
			}
		}
	}
}
void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'p'://pause game and start idle animation
		gamePaused = true;
		break;
	case 's'://unpause game and start game animation
		if(player.gameOver == false)
			gamePaused = false;
		break;
	case 'q'://Jump Left
		if (gamePaused || player.jumping)
			return;
		player.jump(1);
		addTilesRow();
		break;
	case 'w'://Jump right
		if (gamePaused || player.jumping)
			return;
		player.jump(0);
		addTilesCol();
		break;
	}
	if (tiles[0][0].enabled == false) {//GameOver
		player.gameOver = true;
		gameOver = true;
		gamePaused = true;
	}else
		if (tiles[0][0].hasDonut) {
			tiles[0][0].hasDonut = false;
			collectedDonuts++;
		}
}
void printDetails() {
	cout << "The Adventurous Minion\nControls:\n";
	cout << "'s' -> Start Game\t\t'p' -> Pause Game\n";
	cout << "'q' -> Jump on the Left\t\t'w' -> Jump on the Right\n";
	cout << "note: The pressed keys should be lowercased";
}
void main(int argc, char** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("The Adventurous Minion");
	glClearColor(0.588, 0.4, 0.588, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,8/6.0,2,10);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_amb_diff);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 60);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0, 0, -5);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	srand((unsigned)time(NULL));
	initGameObjects();
	printDetails();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
}
