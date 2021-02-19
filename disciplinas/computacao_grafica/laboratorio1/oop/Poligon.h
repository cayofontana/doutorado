#ifndef POLIGON_H
#define POLIGON_H

#include <list>

#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

class Poligon {
public:
	c();

	void (Poligon::* move)(int, int);
	bool isOnRectangle(t_point p1, t_point p2, t_point pc);
private:
	std::list<Point> points;

};

#endif