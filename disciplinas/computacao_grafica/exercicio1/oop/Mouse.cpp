#include "Mouse.h"

Mouse::Mouse() {
}

void
Mouse::click(int button, int state, int x, int y, const int width, const int height, std::vector<Point*> points) {
	// leftButtonClicked = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) ? state == GLUT_DOWN : false;

	GLfloat fX = (GLfloat)x/width;
    GLfloat fY = (GLfloat)(height - y)/height;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		choosingColor = 1;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		for (auto& point : points)
			if ((point->getX() - fX) * (point->getX() - fX) + (point->getY() - fY) * (point->getY() - fY) < (30.0 / width) * (30.0 / height))
				point->setDragging(1);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		choosingColor = 0;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		for (auto& point : points)
			point->setDragging(0);
	}
}

void
Mouse::clickMotion(int x, int y, const int width, const int height, std::vector<Point*> points, Point* clickPoint, Point* projectedPoint) {
	//Corrige a posicao do mouse para a posicao da janela de visualizacao
	y = height - y;
	GLfloat fX = (GLfloat)x/width;
	GLfloat fY = (GLfloat)y/height;

	if (choosingColor) {
		//Atualiza posicao do clique
		clickPoint->setX(fX);
		clickPoint->setY(fY);

		/**
		COLOQUE SEU CODIGO AQUI
		**/
	}
	else
		for (auto& point : points)
			if (point->getDragging()) {
				point->setX((GLfloat)x/width);
				point->setY((GLfloat)y/height);
			}
}

bool
Mouse::isLeftButtonClicked(void) {
	return (leftButtonClicked);
}

bool
Mouse::isMotionClickOnArea(void) {
	return (motionClickOnArea);
}

// Point
// Mouse::getPoint(void) {
// 	return (increasePoint);
// }

// Color
// Mouse::getColor(void) {
// 	return (color);
// }

bool
Mouse::isClickOnArea(std::vector<Point> points) {
	// for (auto initialPoint = points.begin(), currentPoint = std::next(initialPoint); currentPoint != points.end(); ++currentPoint)
	// 	if ((point.getX() <= max(initialPoint->getX(), currentPoint->getX())) && 
	// 		(point.getX() >= min(initialPoint->getX(), currentPoint->getX())) &&
	// 		(point.getY() <= max(initialPoint->getY(), currentPoint->getY())) &&
	// 		(point.getY() >= min(initialPoint->getY(), currentPoint->getY())))
	// 		return (true);
	return (false);
}

float
Mouse::min(float a, float b) {
	return ((a < b) ? a : b);
}

float
Mouse::max(float a, float b) {
	return ((a > b) ? a : b);
}