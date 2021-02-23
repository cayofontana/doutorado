#ifndef VIEW_H
#define VIEW_H

#include <GL/glut.h>
#include <list>

#include "Point.h"
#include "Keyboard.h"

class View {
public:
	~View();

	void initialize(void);
	void update(void);

	static View& getInstance(void);

	static void display(void);
	static void keyPress(unsigned char, int, int);
	static void keyUp(unsigned char, int, int);
	static void idle(void);

private:
	View();

	Keyboard* keyboard;
	std::list<Point> points;
};

#endif