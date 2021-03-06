#include "Projetil.h"

Projetil::Projetil(float raio, Pixel* pixel, float intervaloAngular, int tipo, float tamanhoPonto) : Circunferencia(raio, pixel, intervaloAngular, tipo, tamanhoPonto) {
}

Projetil::~Projetil() {
}

void
Projetil::desenhar(void) {
	mover(0.0f, 2.0f);
	Circunferencia::desenhar();
	notificar();
}

std::list<IConsumidor*>
Projetil::obterConsumidores(void) {
	return (consumidores);
}

void
Projetil::adicionar(IConsumidor* consumidor) {
	consumidores.push_back(consumidor);
}

void
Projetil::remover(IConsumidor* consumidor) {
	consumidores.remove(consumidor);
}

void
Projetil::notificar(void) {
	for (auto consumidor = consumidores.begin(); consumidor != consumidores.end(); ++consumidor)
		if ((*consumidor)->atualizou(this))
			consumidores.erase(consumidor--);
}