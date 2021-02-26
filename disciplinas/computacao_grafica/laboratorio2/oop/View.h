#ifndef VIEW_H
#define VIEW_H

#include <GL/glut.h>
#include <vector>

#include "Point.h"
#include "Mouse.h"
#include "Keyboard.h"

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
	Keyboard* keyboard;
	Mouse* mouse;
	Point pointReference;
	Point* pointUpdate;
	std::vector<Point*> points;
	float *pointsArray;
	int width;
	int height;

	View();

	void convertToArray(std::vector<Point*>, float**, int);
};

#endif