#include "View.h"

#include <iostream>

using namespace std;

View&
View::getInstance(void) {
	static View instance;
	return instance;
}

void
View::display(void) {
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	/* Desenha a curva aproximada por n+1 pontos. */
	int n = 30;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i <= n; i++)
		//Avaliacao do polinomio, retorna um vertice (equivalente a um glVertex3fv) 
		glEvalCoord1f((GLfloat) i/(GLfloat)n);
	glEnd();

	/* Desenha os pontos de controle. */
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (auto point : View::getInstance().points)
		glVertex3f(point->getX(), point->getY(), 0.0f);
	glEnd();

	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, View::getInstance().pointsArray);

	glutSwapBuffers();
}

void
View::mouseClick(int button, int state, int x, int y) {
	if (!View::getInstance().keyboard->hasKeyPressed())
		View::getInstance().mouse->click(button, state, x, y, View::getInstance().width, View::getInstance().height);
}

void
View::mouseClickMotion(int x, int y) {
	if (!View::getInstance().keyboard->hasKeyPressed()) {
		View::getInstance().pointUpdate = View::getInstance().mouse->clickMotion(x, y, View::getInstance().width, View::getInstance().height, View::getInstance().points);
		if (View::getInstance().mouse->isLeftButtonClicked() && View::getInstance().mouse->isMotionClickOnArea()) {
			cout << "Passei" << endl;
			View::getInstance().pointReference = View::getInstance().mouse->getPoint();
		// 	View::getInstance().color = View::getInstance().mouse->getColor();
			View::getInstance().update();
		}
	}
}

void
View::idle(void) {
	// if (View::getInstance().keyboard->hasKeyPressed()) {
	// 	View::getInstance().pointReference = View::getInstance().keyboard->getPoint();
	// 	View::getInstance().color = View::getInstance().keyboard->getColor();
	// 	View::getInstance().keyboard->move();
	// 	View::getInstance().update();
	// }

	// if (!View::getInstance().keyboard->hasKeyPressed() && !View::getInstance().mouse->isLeftButtonClicked())
	// 	View::getInstance().reset();

	glutPostRedisplay();
}

View::View() : pointReference(0.0f, 0.0f) {
	keyboard = new Keyboard();
	mouse = new Mouse();

	points.push_back(new Point(0.1, 0.1));
	points.push_back(new Point(0.3, 0.9));
	points.push_back(new Point(0.7, 0.1));
	points.push_back(new Point(0.9, 0.9));
}

View::~View() {
}

void
View::initialize(const int width, const int height) {
	this->width = width;
	this->height = height;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_MAP1_VERTEX_3);

	//Definicao do polinomio com os pontos de controle
	convertToArray(points, &pointsArray, 3);
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, pointsArray);

	//Muda para a matriz de projecao (aulas futuras)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho(-size, size, -size, size, -size, size);
	glOrtho(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
}

void
View::update(void) {
	for (auto& point : View::getInstance().points) {
		if (point == pointUpdate) {
			point->increase(pointReference.getX(), pointReference.getY());
			for (std::vector<Point>::size_type i, j = i = 0; j < points.size(); j++) {
				pointsArray[i++] = (*points[j]).getX();
				pointsArray[i++] = (*points[j]).getY();
				pointsArray[i++] = 0.0f;
			}
		}
	}
}

void
View::convertToArray(std::vector<Point*> points, float** pointsArray, int colunas) {
	*pointsArray = (float*)malloc(colunas * points.size() * sizeof(float));

	for (std::vector<Point>::size_type i, j = i = 0; j < points.size(); j++) {
		(*pointsArray)[i++] = (*points[j]).getX();
		(*pointsArray)[i++] = (*points[j]).getY();
		(*pointsArray)[i++] = 0.0f;
	}
}