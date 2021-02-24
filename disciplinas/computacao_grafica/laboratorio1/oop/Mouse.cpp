#include "Mouse.h"

Mouse::Mouse() : point(0.0f, 0.0f), increasePoint(0.0f, 0.0f) {
}

void
Mouse::click(int button, int state, int x, int y, const int width, const int height) {
	point.setGLCoordinates(x, y, width, height);

	leftButtonClicked = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) ? state == GLUT_DOWN : false;
}

void
Mouse::clickMotion(int x, int y, const int width, const int height, std::list<Point> points) {
	Point mousePoint(x, y, width, height);
	
	if (motionClickOnArea = (leftButtonClicked && isClickOnArea(points))) {
		increasePoint.setX(mousePoint.getX() - point.getX());
		increasePoint.setY(mousePoint.getY() - point.getY());
		point = mousePoint;
	}
}

bool
Mouse::isClickOnArea(std::list<Point> points) {
	motionClickOnArea = false;
	for(auto initialPoint = points.begin(), currentPoint = std::next(initialPoint); currentPoint != points.end(); ++currentPoint) {
		if ((point.getX() <= max(initialPoint->getX(), currentPoint->getX())) && 
			(point.getX() >= min(initialPoint->getX(), currentPoint->getX())) &&
			(point.getY() <= max(initialPoint->getY(), currentPoint->getY())) &&
			(point.getY() >= min(initialPoint->getY(), currentPoint->getY()))) {
			motionClickOnArea = true;
			break;
		}
		else
			continue;
	}
	return (motionClickOnArea);
}

bool
Mouse::isLeftButtonClicked(void) {
	return (leftButtonClicked);
}

bool
Mouse::isMotionClickOnArea(void) {
	return (motionClickOnArea);
}

Point
Mouse::getPoint(void) {
	return (increasePoint);
}

float
Mouse::min(float a, float b) {
	return ((a < b) ? a : b);
}

float
Mouse::max(float a, float b) {
	return ((a > b) ? a : b);
}