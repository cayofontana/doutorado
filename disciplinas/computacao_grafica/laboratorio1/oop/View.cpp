#include "View.h"

View&
View::getInstance(void) {
	static View instance;
	return instance;
}

void
View::display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_POLYGON);
	for (auto point : View::getInstance().points)
		glVertex3f(point.getX(), point.getY(), 0.0);
	glEnd();

	glutSwapBuffers();
}

void
View::keyPress(unsigned char key, int x, int y) {
	View::getInstance().keyboard->keyEvent(key, 1);
}

void
View::keyUp(unsigned char key, int x, int y) {
	View::getInstance().keyboard->keyEvent(key, 0);
}

void
View::idle(void) {
	if (View::getInstance().keyboard->hasKeyPressed()) {
		View::getInstance().keyboard->move();
		View::getInstance().update();
	}

	glutPostRedisplay();
}

View::View() {
	keyboard = new Keyboard();
	
	points.push_back(Point(0.25, 0.25));
	points.push_back(Point(0.50, 0.25));
	points.push_back(Point(0.50, 0.50));
	points.push_back(Point(0.25, 0.50));
}

View::~View() {
	delete keyboard;
}

void
View::initialize(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void
View::update(void) {
	for (auto& _point : View::getInstance().points)
		_point.increase(keyboard->getPoint().getX(), keyboard->getPoint().getY());
}