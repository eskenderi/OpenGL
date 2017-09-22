# Implementation of an Interactive 
# Color Picker

```cpp
#include <vector>
#include <gl/glut.h>
#include <math.h>
#include <string>
using namespace std;

int width = 800, height = 600;
int showBoxWidth = 250, showBoxHeight = 250, gradientBoxWidth = 355, gradientBoxHeight = 75;
int dragStartY = 0, beforeDragValue = 0, activeSlider = -1;
float gradientColors[2][3] = { { 0.0,0.0,0.0 } ,{ 0.0,0.0,0.0 } };
bool rubberbanding = false;
class Slider;
vector<Slider> sliders;

//Class Slider - Begin
class Slider {
public:
	int x, y, value = 200, containerWidth = 100, containerHeight = 350,
		buttonWidth = 50, buttonHeight = 25, letterSize = 25;
	int sliderHeight = 255 + buttonHeight;
	bool mouseOver = false;
	string primaryName;
	Slider(int x_, int y_, string primaryName_) {
		x = x_;	y = y_;	primaryName = primaryName_;
	}
	void drawSlider() {
		setRespectiveColor();
		glBegin(GL_LINES);//Draw the line representing the bar of the slider
		glVertex2i(x + containerWidth / 2, y + letterSize);
		glVertex2i(x + containerWidth / 2, y + letterSize + sliderHeight);
		glEnd();
		if (mouseOver)glColor3f(1, 1, 1);
		glRecti(x + (containerWidth - buttonWidth) / 2,
			y + letterSize + value,
			x + (containerWidth - buttonWidth) / 2 + buttonWidth,
			y + letterSize + value + buttonHeight);
		if (mouseOver)setRespectiveColor();
		//Write letters on the bottom
		writeText(x + containerWidth / 3, y, &primaryName[0u]);
		//Write value on top of the slider
		if (value < 100) {//Reposition the value number if it has less than 3 digits
			writeText(x + containerWidth / 3 + letterSize/3, y + sliderHeight + 1.5*buttonHeight, &to_string(value)[0u]);
		}
		else
			writeText(x + containerWidth / 3, y + sliderHeight + 1.5*buttonHeight, &to_string(value)[0u]);
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
	void setRespectiveColor() {//Assign colors based on the type of the slider. 
			//This color is used to write the numbers on top and the name of the slider in the bottom 
		switch (primaryName.at(0))
		{
		case ('R'):
			glColor3f(1, 0, 0);
			break;
		case ('G'):
			glColor3f(0, 1, 0);
			break;
		case ('B'):
			glColor3f(0, 0, 1);
			break;
		}
	}
	bool isMouseOver(int x_, int y_) {//Check if the pointer with the given coordinates is over the slider's butn
		if (x_ > x + (containerWidth - buttonWidth) / 2
			&& x_ < x + (containerWidth - buttonWidth) / 2 + buttonWidth
			&& height - y_ > y + letterSize + value
			&& height - y_ < y + letterSize + value + buttonHeight)
			mouseOver = true;
		else
			mouseOver = false;
		glutPostRedisplay();
		return mouseOver;
	}
	bool barClicked(int x_, int y_) {//Here we manage the movement of the slider by clicking on its bar
		int margin = 5;//set a margin click around the x coordinate of the bar to make it easier to click
		if (x_ > x + containerWidth / 2 - margin//Check if coordinates represent a point in the bar's area.
			&& x_< x + containerWidth / 2 + margin
			&& height - y_ >= y + letterSize
			&& height - y_ <= y + letterSize + sliderHeight) {
			int delta = ((height - y_) - (y + letterSize + buttonHeight / 2)) - value;
			beforeDragValue = value;
			updateValueBy(delta);
			return true;
		}
		return false;
	}
	bool withinXRange(int x_) {//Check whether the x's value given as parameter is within this slider's width
		return (x_ > x && x_ < x + containerWidth);
	}
	void updateValueBy(int delta) {
		if (delta > 0)
			value = fmin(beforeDragValue + delta, 255);
		else
			value = fmax(beforeDragValue + delta, 0);
		glutPostRedisplay();
	}
};//End of the class Slider


void drawShowBox() {
	glColor3ub(sliders[0].value, sliders[1].value, sliders[2].value);
	glRecti(450, 300, 450 + showBoxWidth, 300 + showBoxHeight);
}
void drawGradientBox() {

	glBegin(GL_QUADS);
	//Draw left side...
	glColor3fv(gradientColors[0]);
	glVertex2i(400, 100);
	glVertex2i(400, 100 + gradientBoxHeight);
	//Draw right side
	glColor3fv(gradientColors[1]);
	glVertex2i(400 + gradientBoxWidth, 100 + gradientBoxHeight);
	glVertex2i(400 + gradientBoxWidth, 100);
	glEnd();
}
void display(void) {

	glColor3f(1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& s : sliders) {//Draw sliders
		s.drawSlider();
	}
	drawShowBox();
	drawGradientBox();
	glFlush();
}
void initSliders() {//To store the objects of type Slider I used a vertex of size 3
	sliders.emplace_back(75, 100, "Red");//Initialize each slider
	sliders.emplace_back(175, 100, "Green");
	sliders.emplace_back(275, 100, "Blue");
}
void pickGradientColor(int x, int y) {
	//First we check whether the coordinates given represent a point inside the gradient box
	if (x < 400 + gradientBoxWidth && x> 400 && height - y < 100 + gradientBoxHeight && height - y> 100) {
		double ratio = (x - 400.0) / gradientBoxWidth;
		for (int i = 0; i < 3; i++) {//For all three colors
			int value;
			double lValue = gradientColors[0][i], rValue = gradientColors[1][i];
			if (lValue < rValue) {
				value = floor(256 * ((rValue - lValue)*ratio + lValue));
			}
			else {
				value = floor(256 * (lValue - (lValue - rValue)*ratio));
			}
			sliders[i].value = value;
		}
		glutPostRedisplay();
	}
}
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (x < 400) {//Slider's region...
			switch (state)
			{
			case (GLUT_DOWN)://On mouse left click down check if mouse is over 
//either one of the slider's button
				if (activeSlider >= 0 && sliders[activeSlider].isMouseOver(x, y)) {
					rubberbanding = true;
					dragStartY = height - y;//Keep track of the start point
					beforeDragValue = sliders[activeSlider].value;
				}
				else {
					for (int i = 0; i < 3; i++)//Check if one of the bars got clicked
					{
						if (sliders[i].barClicked(x, y)) {
							activeSlider = i;
							bool t = sliders[i].isMouseOver(x, y);
							rubberbanding = true;
							dragStartY = height - y;
							beforeDragValue = sliders[activeSlider].value;
							break;
						}
					}
				}
				break;
			case (GLUT_UP)://On mouse button up...
				if (rubberbanding) {
					int delta = height - y - dragStartY;
					sliders[activeSlider].updateValueBy(delta);
				}
				rubberbanding = false;
				activeSlider = -1;
				break;
			}
		}
		else {//Gradient Box's region
			if (state == GLUT_UP) {
				pickGradientColor(x, y);
			}
		}
	}
}
void motion(int mouseX, int mouseY) {
	if (mouseX < 400) {// Slider's side
		if (rubberbanding) {//If any slider is being dragged, keep changing its value(position) 
			int delta = height - mouseY - dragStartY;
			sliders[activeSlider].updateValueBy(delta);
			if (sliders[activeSlider].withinXRange(mouseX) == false) {//Disengage
				rubberbanding = sliders[activeSlider].isMouseOver(mouseX, mouseY);
				activeSlider = -1;
			}
		}
	}
	else {//gradient box Side
		pickGradientColor(mouseX, mouseY);
	}
}
void passive(int mouseX, int mouseY) {
	int cnt = 0;
	for (auto& s : sliders) {
		if (s.isMouseOver(mouseX, mouseY)) {//Check whether the pointer is over the slider's button
			activeSlider = cnt;
			return;
		}
		cnt++;
	}
}
void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'l':
		gradientColors[0][0] = (sliders[0].value / 255.0);//Convert the integer value to float
		gradientColors[0][1] = (sliders[1].value / 255.0);
		gradientColors[0][2] = (sliders[2].value / 255.0);
		break;
	case 'r':
		gradientColors[1][0] = (sliders[0].value / 255.0);//Convert the integer value to float
		gradientColors[1][1] = (sliders[1].value / 255.0);
		gradientColors[1][2] = (sliders[2].value / 255.0);
		break;
	}
	glutPostRedisplay();
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(400, 200);
	glutCreateWindow("The Perfect Color Picker");
	glClearColor(0.8, 1.0, 1.0, 1.0);
	gluOrtho2D(0.0, width, 0.0, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	initSliders();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passive);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}

```
