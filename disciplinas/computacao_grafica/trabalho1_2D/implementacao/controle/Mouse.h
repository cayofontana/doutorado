#ifndef MOUSE_H
#define MOUSE_H

class Cenario;

class Mouse {
public:
    Mouse();

    void clicar(int, int, int, int, Cenario&);
    void mover(int, int, Cenario&);

private:
    bool pressionado;
    int xInicial;
    int yInicial;
    int xAtual;
    int yAtual;
    float anguloReferencia;
};

#endif