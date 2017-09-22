#include <iostream>
#include <math.h>
#include <glut.h>
using namespace std;

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat slack = 0.06;
	GLfloat side = (2.0-4*slack) / 5.0, startX = -1.0, startY = -1.0;
 	glColor3f(0.0,0.0,0.0);

	for (GLint i = 0; i < 5; i++) {
		for (GLint j = 0; j < 5; j++) {
			GLfloat x1 = startX + i*(side+slack), y1 = startY + j*(side+slack);
			GLfloat x2 = x1 + side, y2 = y1 + side;
				glRectf(x1, y1, x2, y2);

		}
	}
	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Hermann Grid Illusion - Project 1_part B");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glutDisplayFunc(display);
	glutMainLoop();
}
