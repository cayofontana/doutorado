#ifndef MOUSE_H
#define MOUSE_H

#include <GL/glut.h>
#include <vector>

#include "Point.h"
#include "Color.h"

class Mouse {
public:
	Mouse();

	void click(int, int, int, int, const int, const int, std::vector<Point*> points);
	void clickMotion(int, int, const int, const int, std::vector<Point*>, Point*, Point*);
	bool isLeftButtonClicked(void);
	bool isMotionClickOnArea(void);
	// Point getPoint(void);
	// Color getColor(void);

private:
	// Point point;
	// Point increasePoint;
	// Color color;
	bool leftButtonClicked;
	bool motionClickOnArea;
	int choosingColor;

	bool isClickOnArea(std::vector<Point>);
	float min(float a, float b);
	float max(float a, float b);
};

#endif