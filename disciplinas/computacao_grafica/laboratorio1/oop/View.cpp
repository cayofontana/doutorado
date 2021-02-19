#include "View.h"

View::View(Poligon* poligon) {
	poligon->addPoint(0.25, 0.25);
	poligon->addPoint(0.50, 0.25);
	poligon->addPoint(0.50, 0.50);
	poligon->addPoint(0.25, 0.50);
}

void
View::start(int* argc, char** argv, char** title, int positionX, int positionY) {

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(TAMANHO_JANELA, TAMANHO_JANELA);
	glutInitWindowPosition(positionX, positionY);
	glutCreateWindow(title);
	init();	
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

void display(void)
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

void
View::keyPress(unsigned char key, int x, int y)
{
	if (!mouse->isLeftButtonClicked())
	{
		Point point(0.0f, 0.0f);
		mouse->setPoint(point);
		keyboard->setKeyPressed(true);
		//vectorPoints->move = &movePoints;
		keyboard->keyEvent(key, 1);
	}
}

void
View::keyUp(unsigned char key, int x, int y)
{
	if (!mouse->isLeftButtonClicked())
	{
		keyboard->keyEvent(key, 0);
		//vectorPoints->move = NULL;
		keyboard->setKeyPressed(false);
	}
}