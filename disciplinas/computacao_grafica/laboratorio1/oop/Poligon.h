#ifndef POLIGON_H
#define POLIGON_H

#include <list>

#include "Point.h"
#include "Mouse.h"

#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

class Poligon {
public:
	Poligon();

	void (Poligon::* move)(int, int);
	bool isPointOnArea(Point);
	void addPoint(Point);
	void updatePoints(Point*, Mouse*);

private:
	std::list<Point> points;

};

#endif