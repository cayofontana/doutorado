#ifndef VIEW_H
#define VIEW_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define TAMANHO_JANELA 500

class View {
public:
	void start(int*, char**);

private:
	Poligon* poligon;
	Keyboard* keyboard;
	Mouse* mouse;

};

#endif