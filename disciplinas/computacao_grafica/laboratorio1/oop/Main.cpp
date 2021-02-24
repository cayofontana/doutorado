#include "View.h"

int
main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(atoi(argv[1]), atoi(argv[2])); 
	glutInitWindowPosition(atoi(argv[3]), atoi(argv[4]));
	glutCreateWindow("Lab 1");
	View::getInstance().initialize(atoi(argv[1]), atoi(argv[2]));
	glutDisplayFunc(View::getInstance().display);
	glutKeyboardFunc(View::getInstance().keyPress);
	glutKeyboardUpFunc(View::getInstance().keyUp);
	glutMouseFunc(View::getInstance().mouseClick);
	glutMotionFunc(View::getInstance().mouseClickMotion);
	glutIdleFunc(View::getInstance().idle);
	glutMainLoop();

	return (0);
}