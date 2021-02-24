#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <vector>
#include <algorithm>

#include "Point.h"
#include "Color.h"

class Keyboard {
public:
	Keyboard();

	void keyEvent(unsigned char, int);
	void setValue(unsigned char, int);
	void move(void);
	Point getPoint(void);
	Color getColor(void);
	bool hasKeyPressed(void);

private:
	std::vector<int> keys;
	Point point;
	Color color;
};

#endif