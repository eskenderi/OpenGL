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

