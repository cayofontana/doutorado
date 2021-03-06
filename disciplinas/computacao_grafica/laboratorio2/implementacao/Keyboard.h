#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <vector>
#include <algorithm>

#include "Point.h"
#include "Color.h"

class Keyboard {
public:
	Keyboard();

	void keyEvent(unsigned char, int, int*);
	void setValue(unsigned char, int);
	Color getColor(void);
	bool hasKeyPressed(void);

private:
	std::vector<int> keys;
	Color color;
};

#endif