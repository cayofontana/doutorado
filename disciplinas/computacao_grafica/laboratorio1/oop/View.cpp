#include "View.h"

View::View(int width, int height, Poligon* poligon) : poligon(poligon), width(width), height(height) {
	poligon->addPoint(Point(0.25, 0.25));
	poligon->addPoint(Point(0.50, 0.25));
	poligon->addPoint(Point(0.50, 0.50));
	poligon->addPoint(Point(0.25, 0.50));
}

void
View::start(int* argc, char** argv, const char* title, int positionX, int positionY) {

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(TAMANHO_JANELA, TAMANHO_JANELA);
	glutInitWindowPosition(positionX, positionY);
	glutCreateWindow(title);
	initialize();	
	glutDisplayFunc(display); 
	glutKeyboardFunc(keyPress);
	glutIgnoreKeyRepeat(true);
	glutKeyboardUpFunc(keyUp);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutIdleFunc(idle);
	atexit(onExit);
	glutMainLoop();	
}

int
View::getWidth(void) {
	return (width);
}

int
View::getHeight(void) {
	return (height);
}

Keyboard
View::getKeyboard(void) {
	return (*keyboard);
}

Mouse
View::getMouse(void) {
	return (*mouse);
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

static void
View::display(void)
{
	int i;

	/* Limpar todos os pixels  */
	glClear(GL_COLOR_BUFFER_BIT);

	/* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
	glColor3f(1.0, 1.0, 1.0);
	/* Desenhar um polígono branco (retângulo) */
	
	if (poligon->getPoints().size())
	{
		glBegin(GL_POLYGON);
		Point point = poligon->getPoints()[0];
		glVertex3f(point.getX(), point.getY(), 0.0);
		for (i = 1; i < poligon->getPoints().size(); i++)
			glVertex3f(poligon->getPoints()[i - 1].x + (poligon->getPoints()[i].getX() - poligon->getPoints()[i - 1].getX()), poligon->getPoints()[i - 1].getY() + (poligon->getPoints()[i].getY() - poligon->getPoints()[i - 1].getY()), 0.0);
		glEnd();
	}

	/* Desenhar no frame buffer! */
	glutSwapBuffers(); //Funcao apropriada para janela double buffer
}

static void
View::keyPress(unsigned char key, int x, int y)
{
	if (!mouse->isLeftButtonClicked()) {
		// set mouse point to 0.0 0.0 x e y
		keyboard->onKeyPress(key);
		//vectorPoints->move = &movePoints;
	}
}

static void
View::keyUp(unsigned char key, int x, int y) {
	if (!mouse->isLeftButtonClicked()) {
		keyboard->onKeyUp(key);
		// vectorPoints->move = NULL;
	}
}

static void
View::mouse(int button, int state, int x, int y) {
	if (!keyboard->getKeyPressed())
		mouse->click(button, state, x, y, this);
}	

static void
View::mouseMotion(int x, int y) {
	if (!keyboard->getKeyPressed())	{
		mouse->clicked(x, y, this);
		if (mouse->isLeftButtonClicked() && poligon->isPointOnArea(mouse->getPoint()))
			poligon->updatePoints(x, y);
	}
}

static void
View::idle(void) {
	if (keyboard->getKeyPressed())
		keyboard->executeKeyAction();
	
	glutPostRedisplay();
}

static void
View::onExit(void) {
	// free(vectorPoints->points);
	// free(vectorPoints);
}