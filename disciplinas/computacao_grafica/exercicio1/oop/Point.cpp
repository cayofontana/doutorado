#include "Point.h"

Point::Point(float x, float y, Color color) : x(x), y(y), color(color) {
}

// Point::Point(float x, float y, float red, float green, float blue) : x(x), y(y), color(red, green, blue), dragging(0) {
// }

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

float
Point::calculateEuclidianDistance(Point point) {
	return (sqrt(pow((x - point.getX()), 2) + pow((y - point.getY()), 2)));
}

Point*
Point::calculateIntersection(Point initialPointLine1, Point finalPointLine1, Point initialPointLine2, Point finalPointLine2, Color color) {
	Point* projectionPoint = nullptr;
	float determinant, parameterLine1, xProjection, yProjection;

	determinant = (finalPointLine2.getX() - initialPointLine2.getX()) * (finalPointLine1.getY() - initialPointLine1.getY()) - 
	(finalPointLine2.getY() - initialPointLine2.getY()) * (finalPointLine1.getX() - initialPointLine1.getX());

	if (determinant == 0.0)
		return (projectionPoint);

	parameterLine1 = ((finalPointLine2.getX() - initialPointLine2.getX()) * (initialPointLine2.getY() - initialPointLine1.getY()) - 
	(finalPointLine2.getY() - initialPointLine2.getY()) * (initialPointLine2.getX() - initialPointLine1.getX())) / determinant;

	// parameterLine2 = ((finalPointLine1.getX() - initialPointLine1.getX()) * (initialPointLine2.getY() - initialPointLine1.getY()) - 
	// (finalPointLine1.getY() - initialPointLine1.getY()) * (initialPointLine2.getX() - initialPointLine1.getX())) / determinant;

	xProjection = initialPointLine1.getX() + (finalPointLine1.getX() - initialPointLine1.getX()) * parameterLine1;
	yProjection = initialPointLine1.getY() + (finalPointLine1.getY() - initialPointLine1.getY()) * parameterLine1;

	projectionPoint = new Point(xProjection, yProjection, color);

	return (projectionPoint);
}