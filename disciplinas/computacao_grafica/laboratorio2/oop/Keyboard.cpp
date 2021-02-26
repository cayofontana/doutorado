#include "Keyboard.h"

Keyboard::Keyboard() : keys(256), color(0.0f, 1.0f, 0.0f) {
}

void
Keyboard::keyEvent(unsigned char key, int value, int* hits) {
	switch (key) {
		case 43:
			setValue(key, value);
			if (*hits < 100)
				(*hits)++;
			break;
		case 45:
			setValue(key, value);
			if (*hits > 2)
				(*hits)--;
			break;
	}
}

void
Keyboard::setValue(unsigned char key, int value) {
	keys.at((int)key) = value;
}

Color
Keyboard::getColor(void) {
	return (color);
}

bool
Keyboard::hasKeyPressed(void) {
	return (std::find(keys.begin(), keys.end(), (int)true) != keys.end());
}