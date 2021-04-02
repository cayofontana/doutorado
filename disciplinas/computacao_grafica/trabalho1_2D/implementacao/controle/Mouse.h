#ifndef MOUSE_H
#define MOUSE_H

class Cenario;

class Mouse {
public:
	Mouse();

	void clicar(int, int, int, int, Cenario&);
};

#endif