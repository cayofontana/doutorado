#include "Keyboard.h"

Keyboard::Keyboard() : keys(256), point(0.0f, 0.0f) {
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
Keyboard::setValue(unsigned char key, int value) {
	keys.at((int)key) = value;
}

void
Keyboard::move(void) {
	point.setX(0.0f);
	point.setY(0.0f);

	if (keys.at((int)'w') || keys.at((int)'W'))
		point.increase(0.0f, 0.01f);
	if (keys.at((int)'s') || keys.at((int)'S'))
		point.increase(0.0f, -0.01f);
	if (keys.at((int)'a') || keys.at((int)'A'))
		point.increase(-0.01f, 0.0f);
	if (keys.at((int)'d') || keys.at((int)'D'))
		point.increase(0.01f, 0.0f);
}

Point
Keyboard::getPoint(void) {
	return (point);
}

bool
Keyboard::hasKeyPressed(void) {
	return (std::find(keys.begin(), keys.end(), (int)true) != keys.end());
}