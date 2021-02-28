#ifndef MOUSE_H
#define MOUSE_H

#include <GL/glut.h>
#include <vector>

#include "Point.h"
#include "Color.h"

class Mouse {
public:
	Mouse();

	void click(int, int, int, int, const int, const int, std::vector<Point*> points);
	void clickMotion(int, int, const int, const int, std::vector<Point*>, Point*, Point*, Color*);
private:
	int choosingColor;
};

#endif