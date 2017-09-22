#include <iostream>
#include <math.h>
#include <glut.h>
using namespace std;

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.0);
		GLint x = 400, y = 200;
		GLint delta_x = x / 10;
		
		for (int i = 0; i <= 10; i++) {//Iterate 11 times, draw two lines per each time
			//Note that the vertical line will be drawn twice.
			glVertex2i(x, y);
			glVertex2i(-x, -y);

			glVertex2i(-x, y);
			glVertex2i(x, -y);

			x -= delta_x;
		}
	glEnd();


	glLineWidth(2.0);//Set the width of the horizontal lines
	glBegin(GL_LINES);
		// Draw the two red horizontal lines
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(1.0, 0.5);
		glVertex2f(-1.0, 0.5);

		glVertex2f(1.0, -0.5);
		glVertex2f(-1.0, -0.5);
	glEnd();
	glFlush();

}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 400);
	glutInitWindowPosition(400, 200);
	glutCreateWindow("Hering Illusion - Project 1_part A");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glutDisplayFunc(display);
	glutMainLoop();
}
