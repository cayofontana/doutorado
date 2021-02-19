#include "Keyboard.h"

Keyboard::Keyboard() {
}

void
Keyboard::setValue(unsigned char key, int value) {
	keyStatus[(int)key] = value;
}

void
Keyboard::keyEvent(unsigned char key, int value) {
	switch (key) {
		case 'w':
		case 's':
		case 'a':
		case 'd':
			setValue(key, value);
			setValue(key & 0x5f, value);
			break;
		case 'W':
		case 'S':
		case 'A':
		case 'D':
			setValue(key, value);
			setValue(key ^ 0x20, value);
			break;
	}
}

void
Keyboard::executeKeyAction(void) {
	Point point(0.0f, 0.0f);

	if (keyStatus[(int)'w'] || keyStatus[(int)'W'])
		point.setY(point.getY() + 0.01f);
	if (keyStatus[(int)'s'] || keyStatus[(int)'S'])
		point.setY(point.getY() - 0.01f);
	if (keyStatus[(int)'a'] || keyStatus[(int)'A'])
		point.setX(point.getX() - 0.01f);
	if (keyStatus[(int)'d'] || keyStatus[(int)'D'])
		point.setX(point.getX() + 0.01f);

	// if (vectorPoints->move)
	// 	vectorPoints->move(point);
}