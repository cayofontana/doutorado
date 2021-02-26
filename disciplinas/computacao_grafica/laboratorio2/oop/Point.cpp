#include "Point.h"

Point::Point(float x, float y) : x(x), y(y) {
}

Point::Point(int x, int y, int width, int height) {
	setGLCoordinates(x, y, width, height);
}


float
Point::getX(void) {
	return (x);
}

void
Point::setX(float x) {
	this->x = x;
}

float
Point::getY(void) {
	return (y);
}

void
Point::setY(float y) {
	this->y = y;
}

void
Point::increase(float x, float y) {
	this->x += x;
	this->y += y;
}

void
Point::setGLCoordinates(int x, int y, int width, int height) {
	this->x = (float)x / (float)width;
	this->y = 1 - (float)y / (float)height;
}