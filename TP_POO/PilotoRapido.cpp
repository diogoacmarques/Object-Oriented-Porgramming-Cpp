#include "PilotoRapido.h"
#include "Carro.h"
#include "Pista.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

PilotoRapido::PilotoRapido(std::string n):Piloto(n),tempoPassado(0)
{
}

PilotoRapido::~PilotoRapido()
{
}

std::string PilotoRapido::obtemTipo() const
{
	return "rapido";
}

bool PilotoRapido::tomaDecisao(Carro * c, Pista * p)
{
	srand((int)time(NULL));
	int prob = rand() % 100;
	//cout << "piloto " << obtemNome() << " tem prob de panico = " << prob << endl;

	if (tempoPassado > 0 && tempoPassado%10 == 0) {
		if (prob < 10) {
			c->ativaSinalEmergencia();
			cout << "piloto " << obtemNome() << " teve panico e ativou emergencia!" << endl;
			return false;
		}
	}

	if (c->obtemBateriaAtual() > (c->obtemBateriaMax() / 2)) {//ainda tem mais de metade da bateria
		c->acelera();
	}
	else {//tem menos de metade da bateria
		if (tempoPassado%3 == 0)//se passaram 3 segundos (multiplo de 3)
			c->acelera();
	}

	tempoPassado++;
	return true;
}

Piloto * PilotoRapido::dupilica()
{
	return new PilotoRapido(*this);
}
