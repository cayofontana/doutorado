#ifndef VIEW_H
#define VIEW_H

#include <GL/glut.h>
#include <vector>

#include "Point.h"
#include "Color.h"
#include "Mouse.h"

class View {
public:
	~View();

	void initialize(const int, const int);
	void update(void);

	static View& getInstance(void);

	static void display(void);
	static void mouseClick(int, int, int, int);
	static void mouseClickMotion(int, int);
	static void idle(void);

private:
	View();
	Mouse* mouse;
	Color backgroundColor;
	Point clickPoint;
	Point projectedPoint;
	std::vector<Point*> points;
	int width;
	int height;
};

#endif