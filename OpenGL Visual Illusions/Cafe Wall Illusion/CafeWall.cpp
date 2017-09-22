#include <iostream>
#include <math.h>
#include <glut.h>
using namespace std;

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	GLint mortar_width = 2;
	GLint offset = 0, startX = 0, startY = 0, side = ceil((500 - 8*mortar_width)/9.0);
	GLint offset_step = ceil(side/3.0);

	for (GLint i = 0; i < 9; i++) {
		for (GLint j = 0; j < 18; j++) {
			if (j % 2 == 0) {
			//white block
				glColor3f(1.0, 1.0, 1.0);
			}
			else {
				glColor3f(0.0, 0.0, 0.0);
			}
			GLint x1 = startX + j*(side), y1 = startY + i*(side + mortar_width);
			GLint x2 = x1 + side, y2 = y1 + side;

			//add offset
			glRectf(x1+offset, y1, x2+offset, y2);

		}
		if (i % 2 == 0) 
			offset_step *= -1;
		offset += offset_step;
		
	}
	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(850, 500);//
	glutCreateWindow("Cafe Wall Illusion - Project 1_part C");
	glClearColor(76.0/255, 142.0/255, 142.0/255,0.50);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 850.0, 0.0, 500.0);
	glutDisplayFunc(display);
	glutMainLoop();
}
