#ifndef MOUSE_H
#define MOUSE_H

#include <GL/glut.h>
#include <list>

#include "Point.h"
#include "Color.h"

class Mouse {
public:
	Mouse();

	void click(int, int, int, int, const int, const int);
	void clickMotion(int, int, const int, const int, std::list<Point>);
	bool isLeftButtonClicked(void);
	bool isMotionClickOnArea(void);
	Point getPoint(void);
	Color getColor(void);

private:
	Point point;
	Point increasePoint;
	Color color;
	bool leftButtonClicked;
	bool motionClickOnArea;

	bool isClickOnArea(std::list<Point>);
	float min(float a, float b);
	float max(float a, float b);
};

#endif