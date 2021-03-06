#include "View.h"

View&
View::getInstance(void) {
	static View instance;
	return instance;
}

void
View::display(void) {
	//Define a cor do fundo
	glClearColor(View::getInstance().backgroundColor.getRed(), View::getInstance().backgroundColor.getGreen(), View::getInstance().backgroundColor.getBlue(), 0.0);

	/* Limpar todos os pixels  */
	glClear(GL_COLOR_BUFFER_BIT);

	/* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
	/* Desenhar um polígono branco (retângulo) */
	glBegin(GL_POLYGON);
	for (auto& point : View::getInstance().points) {
		glColor3f(point->getColor().getRed(), point->getColor().getGreen(), point->getColor().getBlue());
		glVertex3f(point->getX(), point->getY(), 0.0);
	}
	glEnd();

	/* Desenha o ponto de clique. */
	glPointSize(5.0);
	glColor3f(View::getInstance().clickPoint.getColor().getRed(), View::getInstance().clickPoint.getColor().getGreen(), View::getInstance().clickPoint.getColor().getBlue());
	glBegin(GL_POINTS);
	glVertex3f(View::getInstance().clickPoint.getX(), View::getInstance().clickPoint.getY(), 0.0);
	glEnd();

	/* Desenha o ponto projetado. */
	glPointSize(5.0);
	glColor3f(View::getInstance().projectedPoint.getColor().getRed(), View::getInstance().projectedPoint.getColor().getGreen(), View::getInstance().projectedPoint.getColor().getBlue());
	glBegin(GL_POINTS);
	glVertex3f(View::getInstance().projectedPoint.getX(), View::getInstance().projectedPoint.getY(), 0.0);
	glEnd();

	/* Desenhar no frame buffer! */
	glutSwapBuffers(); //Funcao apropriada para janela double buffer
}

void
View::mouseClick(int button, int state, int x, int y) {
	View::getInstance().mouse->click(button, state, x, y, View::getInstance().width, View::getInstance().height, View::getInstance().points);
}

void
View::mouseClickMotion(int x, int y) {
	View::getInstance().mouse->clickMotion(x, y, View::getInstance().width, View::getInstance().height, View::getInstance().points, &View::getInstance().clickPoint, &View::getInstance().projectedPoint, &View::getInstance().backgroundColor);
}

void
View::idle(void) {
	glutPostRedisplay();
}

View::View() : backgroundColor(0.0f, 0.0f, 0.0f), clickPoint(0.0f, 0.0f, Color(1.0, 1.0, 0.0)), projectedPoint(0.0f, 0.0f, Color(1.0, 1.0, 0.0)) {
	mouse = new Mouse();
	
	points.push_back(new Point(0.1, 0.1, Color(1.0, 0.0, 0.0)));
	points.push_back(new Point(0.9, 0.1, Color(0.0, 1.0, 0.0)));
	points.push_back(new Point(0.5, 0.9, Color(0.0, 0.0, 1.0)));
}

View::~View() {
	for (auto& point : points)
		delete point;
}

void
View::initialize(const int width, const int height) {
	this->width = width;
	this->height = height;

	/* selecionar cor de fundo (preto) */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* inicializar sistema de visualizacao */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}