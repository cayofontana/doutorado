#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Point.h"
#include <vector>
#include <algorithm>

class Keyboard {
public:
	Keyboard();

	void keyEvent(unsigned char, int);
	void setValue(unsigned char, int);
	void move(void);
	Point getPoint(void);
	bool hasKeyPressed(void);

private:
	std::vector<int> keys;
	Point point;
};

#endif