#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Point.h"

class Keyboard {
public:
	Keyboard();

	void setValue(unsigned char key, int value);
	void keyEvent(unsigned char key, int value);
	void executeKeyAction(void);
	void setKeyPressed(bool);

private:
	int keyStatus[256];
	bool keyPressed;
};

#endif