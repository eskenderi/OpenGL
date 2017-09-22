#pragma once
#include <gl/glut.h>

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
