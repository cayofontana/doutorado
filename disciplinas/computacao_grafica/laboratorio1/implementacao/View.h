#ifndef VIEW_H
#define VIEW_H

#include <GL/glut.h>
#include <list>

#include "Point.h"
#include "Color.h"
#include "Keyboard.h"
#include "Mouse.h"

class View {
public:
	~View();

	void initialize(const int, const int);
	void update(void);

	static View& getInstance(void);

	static void display(void);
	static void keyPress(unsigned char, int, int);
	static void keyUp(unsigned char, int, int);
	static void mouseClick(int, int, int, int);
	static void mouseClickMotion(int, int);
	static void idle(void);

private:
	View();

	Keyboard* keyboard;
	Mouse* mouse;
	std::list<Point> points;
	Point pointReference;
	Color color;
	int width;
	int height;

	void reset(void);
};

#endif