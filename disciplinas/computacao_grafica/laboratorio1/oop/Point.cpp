#include "Point.h"

Point::Point(float x, float y) : x(x), y(y) {
}

Point::Point(int x, int y, int width, int height) {
	convertToGLCoordenates(x, y, width, height);
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

void
Point::convertToGLCoordenates(int x, int y, int width, int height) {	
	this->x = (float)x / (float)width;
	this->y = 1 - (float)y / (float)height;
}