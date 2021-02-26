#include "Point.h"

// Point::Point(float x, float y) : x(x), y(y) {
// }

Point::Point(float x, float y, float red, float green, float blue) : x(x), y(y), color(red, green, blue), dragging(0) {
}

// Point::Point(int x, int y, int width, int height) {
// 	setGLCoordinates(x, y, width, height);

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

Color
Point::getColor(void) {
	return (color);
}

int
Point::getDragging(void) {
	return (dragging);
}

void
Point::setDragging(int dragging) {
	this->dragging = dragging;
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