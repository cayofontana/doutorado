#ifndef VIEW_H
#define VIEW_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Point.h"
#include "Poligon.h"
#include "Keyboard.h"
#include "Mouse.h"

#define TAMANHO_JANELA 500

class View {
public:
	View(int, int, Poligon*);

	void start(int*, char**, const char*, int, int);
	int getWidth(void);
	int getHeight(void);
	Keyboard getKeyboard(void);
	Mouse getMouse(void);

private:
	Poligon* poligon;
	Keyboard* keyboard;
	Mouse* mouse;
	int width;
	int height;

	void initialize(void);
	static void display(void);
	static void keyPress(unsigned char, int, int);
	static void keyUp(unsigned char, int, int);
	static void mouse(int, int, int, int);
	static void mouseMotion(int, int);
	static void idle(void);
	static void idle(void);

};

#endif