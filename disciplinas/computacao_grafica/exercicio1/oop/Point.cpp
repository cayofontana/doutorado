#include "Point.h"

Point::Point(float x, float y, Color color) : x(x), y(y), color(color) {
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

Point*
Point::calculateIntersection(Point initialPointLine1, Point finalPointLine1, Point initialPointLine2, Point finalPointLine2, Color color) {
	float determinant, parameterLine1, xProjection, yProjection;

	determinant = (finalPointLine2.getX() - initialPointLine2.getX()) * (finalPointLine1.getY() - initialPointLine1.getY()) - (finalPointLine2.getY() - initialPointLine2.getY()) * (finalPointLine1.getX() - initialPointLine1.getX());

	if (determinant == 0.0)
		return (nullptr);

	parameterLine1 = ((finalPointLine2.getX() - initialPointLine2.getX()) * (initialPointLine2.getY() - initialPointLine1.getY()) - (finalPointLine2.getY() - initialPointLine2.getY()) * (initialPointLine2.getX() - initialPointLine1.getX())) / determinant;

	xProjection = initialPointLine1.getX() + (finalPointLine1.getX() - initialPointLine1.getX()) * parameterLine1;
	yProjection = initialPointLine1.getY() + (finalPointLine1.getY() - initialPointLine1.getY()) * parameterLine1;

	return (new Point(xProjection, yProjection, color));
}

float
Point::getRedColorByInterpolation(Point currentPoint, Point initialPoint, Point finalPoint) {
	float distanceCoeficient;

	distanceCoeficient = Point::getDistanceCoeficient(currentPoint, initialPoint, finalPoint);
	return (distanceCoeficient * initialPoint.getColor().getRed() + (1 - distanceCoeficient) * finalPoint.getColor().getRed());
}

float
Point::getGreenColorByInterpolation(Point currentPoint, Point initialPoint, Point finalPoint) {
	float distanceCoeficient;

	distanceCoeficient = Point::getDistanceCoeficient(currentPoint, initialPoint, finalPoint);
	return (distanceCoeficient * initialPoint.getColor().getGreen() + (1 - distanceCoeficient) * finalPoint.getColor().getGreen());
}


float
Point::getBlueColorByInterpolation(Point currentPoint, Point initialPoint, Point finalPoint) {
	float distanceCoeficient;

	distanceCoeficient = Point::getDistanceCoeficient(currentPoint, initialPoint, finalPoint);
	return (distanceCoeficient * initialPoint.getColor().getBlue() + (1 - distanceCoeficient) * finalPoint.getColor().getBlue());
}

float
Point::getDistanceCoeficient(Point clickPoint, Point initialPoint, Point finalPoint) {
	float totalDistance, parcialDistance;

	totalDistance = calculateEuclidianDistance(initialPoint, finalPoint);
	parcialDistance = calculateEuclidianDistance(clickPoint, finalPoint);

	return (parcialDistance / totalDistance);
}

float
Point::calculateEuclidianDistance(Point initialPoint, Point finalPoint) {
	return (sqrt(pow((initialPoint.getX() - finalPoint.getX()), 2) + pow((initialPoint.getY() - finalPoint.getY()), 2)));
}