#ifndef POINT_H
#define POINT_H

#include "Color.h"

#include <math.h>

class Point {
public:
	Point(float, float, Color);
	// Point(float, float, float, float, float);
	// Point(int, int, int, int);

	float getX(void);
	void setX(float);
	float getY(void);
	void setY(float);
	Color getColor(void);
	int getDragging(void);
	void setDragging(int dragging);
	void increase(float, float);
	void setGLCoordinates(int, int, int, int);
	float calculateEuclidianDistance(Point point);

	static Point* calculateIntersection(Point, Point, Point, Point, Color);

private:
	float x;
	float y;
	Color color;
	int dragging;
};

#endif