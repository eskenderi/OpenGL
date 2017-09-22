#include <iostream>
#include <math.h>
#include <glut.h>
using namespace std;

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	GLint xy_coord = 0, width = 500;
	GLfloat r = 0.0, gr = 0.0, bl = 0.0;
	GLfloat color_change_step = (1.0 / (width/2.0));
	for (int i = 0; i < (width / 2.0); i++) {
		r += color_change_step;
		bl += color_change_step;
		glColor3f(r, gr, bl);
		glRecti(xy_coord, xy_coord, width - xy_coord, width - xy_coord);
		xy_coord += 1;
	}


		
	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);//
	glutCreateWindow("Pyramid - Project 1_part D");
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glutDisplayFunc(display);
	glutMainLoop();
}
