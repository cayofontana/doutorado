#include "View.h"

View&
View::getInstance(void) {
	static View instance;
	return instance;
}

void
View::initialize(void) {
	/* selecionar cor de fundo (preto) */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* inicializar sistema de visualizacao */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void
View::display(void) {
	/* Limpar todos os pixels  */
	glClear(GL_COLOR_BUFFER_BIT);

	/* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
	glColor3f(0.0, 0.0, 1.0);
	/* Desenhar um polígono branco (retângulo) */
	glBegin(GL_POLYGON);
	for (auto point : View::getInstance().points)
		glVertex3f(point.getX(), point.getY(), 0.0);
	glEnd();

	/* Desenhar no frame buffer! */
	glutSwapBuffers(); //Funcao apropriada para janela double buffer
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
View::update(void) {
	for (auto& _point : View::getInstance().points)
		_point.increase(keyboard->getPoint().getX(), keyboard->getPoint().getY());
}