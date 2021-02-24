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
	if (!View::getInstance().mouse->isLeftButtonClicked())
		View::getInstance().keyboard->keyEvent(key, 1);
}

void
View::keyUp(unsigned char key, int x, int y) {
	if (!View::getInstance().mouse->isLeftButtonClicked())
		View::getInstance().keyboard->keyEvent(key, 0);
}

void
View::mouseClick(int button, int state, int x, int y) {
	if (!View::getInstance().keyboard->hasKeyPressed())
		View::getInstance().mouse->click(button, state, x, y, View::getInstance().width, View::getInstance().height);
}

void
View::mouseClickMotion(int x, int y) {
	if (!View::getInstance().keyboard->hasKeyPressed()) {
		View::getInstance().mouse->clickMotion(x, y, View::getInstance().width, View::getInstance().height, View::getInstance().points);
		if (View::getInstance().mouse->isLeftButtonClicked() && View::getInstance().mouse->isMotionClickOnArea()) {
			View::getInstance().pointReference = View::getInstance().mouse->getPoint();
			View::getInstance().update();
		}
	}
}

void
View::idle(void) {
	if (View::getInstance().keyboard->hasKeyPressed()) {
		View::getInstance().pointReference = View::getInstance().keyboard->getPoint();
		View::getInstance().keyboard->move();
		View::getInstance().update();
	}

	glutPostRedisplay();
}

View::View() : pointReference(0.0f, 0.0f) {
	keyboard = new Keyboard();
	mouse = new Mouse();
	
	points.push_back(Point(0.25, 0.25));
	points.push_back(Point(0.50, 0.25));
	points.push_back(Point(0.50, 0.50));
	points.push_back(Point(0.25, 0.50));
}

View::~View() {
	delete keyboard;
}

void
View::initialize(const int width, const int height) {
	this->width = width;
	this->height = height;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void
View::update(void) {
	for (auto& point : View::getInstance().points)
		point.increase(pointReference.getX(), pointReference.getY());
}