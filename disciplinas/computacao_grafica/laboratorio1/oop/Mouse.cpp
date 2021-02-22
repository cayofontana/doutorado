#include "Mouse.h"

Mouse::Mouse() {
}

void
Mouse::click(int button, int state, int x, int y, View* view) {
	if (!view->getKeyboard().getKeyPressed()) {
		point = new Point(x, y, view->getWidth(), view->getHeight());

		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			leftButtonClicked = state == GLUT_DOWN;
		else
			leftButtonClicked = false;
	}
}	

void
Mouse::clicked(int x, int y, View* view) {

	// t_point mouseMovePoint;

	// if (!keyboardControl->keyPressed)
	// {
	// 	mouseMovePoint = convertToGLCoordenates(x, y);
	// 	if (mouseControl->isLeftClicked && checkClickArea(mouseMovePoint))
	// 		move(x, y);
	// 	mouseControl->point = mouseMovePoint;
	// }
}

bool
Mouse::isLeftButtonClicked(void) {
	return (leftButtonClicked);
}

Point
Mouse::getPoint(void) {
	return (*point);
}