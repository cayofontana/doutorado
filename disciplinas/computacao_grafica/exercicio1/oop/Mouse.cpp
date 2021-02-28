#include "Mouse.h"

Mouse::Mouse() : choosingColor(0) {
}

void
Mouse::click(int button, int state, int x, int y, const int width, const int height, std::vector<Point*> points) {
	GLfloat fX = (GLfloat)x / width;
	GLfloat fY = (GLfloat)(height - y) / height;

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
Mouse::clickMotion(int x, int y, const int width, const int height, std::vector<Point*> points, Point* clickPoint, Point* projectedPoint, Color* backgroundColor) {
	Point* _projectedPoint = nullptr;

	//Corrige a posicao do mouse para a posicao da janela de visualizacao
	y = height - y;
	GLfloat fX = (GLfloat)x / width;
	GLfloat fY = (GLfloat)y / height;

	if (choosingColor) {
		//Atualiza posicao do clique
		clickPoint->setX(fX);
		clickPoint->setY(fY);

		_projectedPoint = Point::calculateIntersection(*points.at(0), *points.at(1), *points.at(2), *clickPoint, projectedPoint->getColor());
		if (_projectedPoint) {
			projectedPoint->setX(_projectedPoint->getX());
			projectedPoint->setY(_projectedPoint->getY());

			backgroundColor->setRed(Point::getRedColorByInterpolation(*clickPoint, *points.at(2), *points.at(0)));
			backgroundColor->setGreen(Point::getGreenColorByInterpolation(*clickPoint, *points.at(0), *points.at(1)));
			backgroundColor->setBlue(Point::getBlueColorByInterpolation(*clickPoint, *points.at(1), *points.at(2)));
		}
	}
	else
		for (auto& point : points)
			if (point->getDragging()) {
				point->setX((GLfloat)x/width);
				point->setY((GLfloat)y/height);
			}

	delete _projectedPoint;
}