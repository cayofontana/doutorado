#include "Mouse.h"
#include "Keyboard.h"

int
main(int argc, char* argv[]) {
	Mouse mouse;
	Keyboard keyboard;

	mouse.clicked(10, 20);
	keyboard.executeKeyAction();

	return (1);
}