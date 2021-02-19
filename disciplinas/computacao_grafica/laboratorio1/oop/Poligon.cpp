#include "Poligon.h"

Poligon::Poligon() {
}

bool
Poligon::isOnRectangle(t_point p1, t_point p2, t_point pc) {

}

void
Poligon::move(int x, int y) {
	t_point point;

	vectorPoints->move = &movePoints;
	point = convertToGLCoordenates(x, y);
	vectorPoints->move(point);
}

void
Poligon::movePoints(Point point) {
	int i;

	for (i = 0; i < points.size(); i++) {
		points[i].setX(points[i].getX() + (points[i].getX() - mouse->getPoint().getX()));
		points[i].setY(points[i].getY() + (points[i].getY() - mouse->getPoint().getY()));
	}
}