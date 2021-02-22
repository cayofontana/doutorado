#include "Poligon.h"

Poligon::Poligon() {
}

bool
Poligon::isPointOnArea(Point point) {
	//return ((pc.x <= max(p1.x, p2.x)) && (pc.x >= min(p1.x, p2.x)) && (pc.y <= max(p1.y, p2.y)) && (pc.y >= min(p1.y, p2.y)));
	return (true);
}

void
Poligon::move(int x, int y) {
	Point point(x, y);

	// vectorPoints->move = &movePoints;
	// vectorPoints->move(point);
}

void
Poligon::updatePoints(Point* point, Mouse* mouse) {
	int i;

	for (i = 0; i < points.size(); i++) {
		points[i].setX(points[i].getX() + (points[i].getX() - mouse->getPoint().getX()));
		points[i].setY(points[i].getY() + (points[i].getY() - mouse->getPoint().getY()));
	}
}

void
Poligon::addPoint(Point point) {
	points.push_back(point);
}