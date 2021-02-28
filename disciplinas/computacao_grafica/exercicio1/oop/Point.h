#ifndef POINT_H
#define POINT_H

#include "Color.h"

#include <math.h>

class Point {
public:
	Point(float, float, Color);

	float getX(void);
	void setX(float);
	float getY(void);
	void setY(float);
	Color getColor(void);
	int getDragging(void);
	void setDragging(int dragging);
	void increase(float, float);
	void setGLCoordinates(int, int, int, int);

	static Point* calculateIntersection(Point, Point, Point, Point, Color);
	static float getRedColorByInterpolation(Point, Point, Point);
	static float getGreenColorByInterpolation(Point, Point, Point);
	static float getBlueColorByInterpolation(Point, Point, Point);

private:
	float x;
	float y;
	Color color;
	int dragging;

	static float calculateEuclidianDistance(Point, Point);
	static float getDistanceCoeficient(Point, Point, Point);
};

#endif