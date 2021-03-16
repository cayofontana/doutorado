#include "Mouse.h"
#include "../Cenario.h"

#include <GL/glut.h>

Mouse::Mouse() {
}

void
Mouse::clicar(int botao, int estado, int x, int y, Cenario* cenario) {
	if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
		cenario->obterJogadores().at(1)->socar(true);
	else
		cenario->obterJogadores().at(1)->socar(false);
}

// Point*
// Mouse::clickMotion(int x, int y, const int width, const int height, std::vector<Point*> points) {
// 	Point* pointArray = isClickOnArea(points, width, height);
// 	Point mousePoint(x, y, width, height);

// 	if ((motionClickOnArea = (leftButtonClicked && pointArray))) {
// 		increasePoint.setX(mousePoint.getX() - point.getX());
// 		increasePoint.setY(mousePoint.getY() - point.getY());
// 		point = mousePoint;
// 	}

// 	return (pointArray);
// }

// bool
// Mouse::isLeftButtonClicked(void) {
// 	return (leftButtonClicked);
// }

// bool
// Mouse::isMotionClickOnArea(void) {
// 	return (motionClickOnArea);
// }

// Point
// Mouse::getPoint(void) {
// 	return (increasePoint);
// }

// Color
// Mouse::getColor(void) {
// 	return (color);
// }

// Point*
// Mouse::isClickOnArea(std::vector<Point*> points, const int width, const int height) {
// 	float pixelWidth = (float)1 / (float)width;
// 	float pixelHeight = (float)1 / (float)height;

// 	for (auto& _point : points) 
// 		if ((this->point.getX() <= _point->getX() + (5 * pixelWidth)) && 
// 			(this->point.getX() >= _point->getX() - (5 * pixelWidth)) &&
// 			(this->point.getY() <= _point->getY() + ( 5 * pixelHeight)) && 
// 			(this->point.getY() >= _point->getY() - ( 5 * pixelHeight)))
// 			return (_point);
// 	return (NULL);
// }

// float
// Mouse::min(float a, float b) {
// 	return ((a < b) ? a : b);
// }

// float
// Mouse::max(float a, float b) {
// 	return ((a > b) ? a : b);
// }