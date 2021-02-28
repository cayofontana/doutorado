#include "View.h"

int
main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("red 3D lighted cube");
	glutDisplayFunc(View::getInstance().display);
	View::getInstance().initialize();
	glutMainLoop();

	return (0);
}