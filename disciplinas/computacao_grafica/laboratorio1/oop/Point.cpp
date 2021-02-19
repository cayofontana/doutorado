#include "Point.h"

Point::Point(float x, float y) : x(x), y(y) {
}

Point::Point(int x, int y) : Point((float)x, (float)y) {
}

float
Point::getX(void) {
	return (x);
}

float
Point::getY(void) {
	return (y);
}

void
Point::setX(float x) {
	this->x = x;
}

void
Point::setY(float y) {
	this->y = y;
}