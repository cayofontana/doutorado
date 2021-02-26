#include "View.h"

View&
View::getInstance(void) {
	static View instance;
	return instance;
}

void
View::display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	//Definicao do polinomio com os atuais pontos de controle
	View::getInstance().convertToArray(View::getInstance().points, &View::getInstance().pointsArray, 3);
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, View::getInstance().pointsArray);

	/* Desenha a curva aproximada por n+1 pontos. */
	glColor3f(View::getInstance().colorLine.getRed(), View::getInstance().colorLine.getGreen(), View::getInstance().colorLine.getBlue());
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= View::getInstance().curvePoints; i++)
		//Avaliacao do polinomio, retorna um vertice (equivalente a um glVertex3fv) 
		glEvalCoord1f((GLfloat) i/(GLfloat)View::getInstance().curvePoints);
	glEnd();

	/* Desenha os pontos de controle. */
	glPointSize(5.0);
	glColor3f(View::getInstance().colorPoints.getRed(), View::getInstance().colorPoints.getGreen(), View::getInstance().colorPoints.getBlue());
	glBegin(GL_POINTS);
	for (auto point : View::getInstance().points)
		glVertex3f(point->getX(), point->getY(), 0.0f);
	glEnd();

	

	glutSwapBuffers();
}

void
View::keyPress(unsigned char key, int x, int y) {
	if (!View::getInstance().mouse->isLeftButtonClicked()) {
		View::getInstance().keyboard->keyEvent(key, 1, &View::getInstance().curvePoints);
		View::getInstance().colorLine = View::getInstance().keyboard->getColor();
	}
}

void
View::keyUp(unsigned char key, int x, int y) {
	if (!View::getInstance().mouse->isLeftButtonClicked()) {
		View::getInstance().keyboard->keyEvent(key, 0, &View::getInstance().curvePoints);
		View::getInstance().colorLine = View::getInstance().keyboard->getColor();
	}
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
			View::getInstance().pointReference = View::getInstance().mouse->getPoint();
			View::getInstance().colorPoints = View::getInstance().mouse->getColor();
			View::getInstance().update();
		}
	}
}

void
View::idle(void) {
	if (!View::getInstance().keyboard->hasKeyPressed() && !View::getInstance().mouse->isLeftButtonClicked())
		View::getInstance().reset();

	glutPostRedisplay();
}

View::View() : colorPoints(1.0, 1.0, 0.0), colorLine(1.0, 1.0, 1.0), pointReference(0.0f, 0.0f), curvePoints(30) {
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
	for (auto& point : View::getInstance().points)
		if (point == pointUpdate)
			point->increase(pointReference.getX(), pointReference.getY());
}

void
View::reset(void) {
	colorPoints.setRed(1.0f);
	colorPoints.setGreen(1.0f);
	colorPoints.setBlue(0.0f);

	colorLine.setRed(1.0f);
	colorLine.setGreen(1.0f);
	colorLine.setBlue(1.0f);
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