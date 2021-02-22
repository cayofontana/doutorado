#ifndef MOUSE_H
#define MOUSE_H

#include "Point.h"
#include "View.h"

class Mouse {
public:
	Mouse();

	void click(int, int, int, int, View*);
	void clicked(int, int, View*);
	bool isLeftButtonClicked(void);
	Point getPoint(void);

private:
	Point* point;
	bool leftButtonClicked;
};

#endif