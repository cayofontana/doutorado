#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Point.h"
#include "View.h"

class Keyboard {
public:
	Keyboard();

	void onKeyPress(unsigned char);
	void onKeyUp(unsigned char);
	void setValue(unsigned char, int);
	void keyEvent(unsigned char, int);
	void executeKeyAction(void);
	bool getKeyPressed(void);
	void setKeyPressed(bool);

private:
	int keyStatus[256];
	bool keyPressed;
};

#endif