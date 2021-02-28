#include "View.h"

int
main(int argc, char** argv) {
	View* view = View::getInstance();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("red 3D lighted cube");
	glutDisplayFunc(view->display);
	view->initialize();
	glutMainLoop();

	delete view;

	return (0);
}