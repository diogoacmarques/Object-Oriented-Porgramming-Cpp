#include "PilotoRapido.h"
#include "Carro.h"
#include "Pista.h"
#include <cstdlib>
#include <ctime>

using namespace std;

PilotoRapido::PilotoRapido(std::string n):Piloto(n),tempoPassado(0)
{
}

PilotoRapido::~PilotoRapido()
{
}

bool PilotoRapido::tomaDecisao(Carro * c, Pista * p)
{
	srand((int)time(NULL));
	if (tempoPassado > 0 && tempoPassado%10 == 0) {
		if (rand() % 10)
			c->ativaSinalEmergencia();
	}

	if (c->obtemBateriaAtual() > (c->obtemBateriaMax() / 2)) {//ainda tem mais de metade da bateria
		c->acelera();
	}
	else {//tem menos de metade da bateria
		if (tempoPassado%3 == 0)//se passaram 3 segundos (multiplo de 3)
			c->acelera();
	}

	tempoPassado++;
	return false;
}
