#ifndef MOUSE_H
#define MOUSE_H

#include "Point.h"

class Mouse {
public:
	Mouse();

	void click(int, int, int, int);
	void clicked(int, int) ;

private:
	// Point &point;
	bool leftButtonClicked;
};

#endif