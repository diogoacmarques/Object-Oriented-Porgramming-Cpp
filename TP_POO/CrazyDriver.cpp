#include "CrazyDriver.h"
#include "Pista.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

CrazyDriver::CrazyDriver(std::string n):Piloto(n), pos(-1)
{
	srand((int)time(NULL));
	iniciaCorridaApos = (rand() % 5) + 1;
	cout << "Construtor Piloto crazy" << endl;
}

CrazyDriver::~CrazyDriver()
{
}

bool CrazyDriver::tomaDecisao(Carro * c, Pista * p)
{//melhorar funcao

	int carrosNaPista = p->obtemCarrosNaPista();
	int posAtual = p->obtemPosCorrida(c->obtemId());
	if ((rand() % 100) < 5) {//faz algo que danifica o automovel
		c->danificaCarro();
		p->danificaCarro(posAtual - 1);
	}


	

	if (c->obtemBateriaAtual() == 0) {
		c->ativaSinalEmergencia();
		return false;
	}


	if (p->obtemTempoCorrida() >= iniciaCorridaApos) {
		if (pos > posAtual && posAtual != carrosNaPista) {//ficou para tras mas nao e o ultimo
			c->acelera();
			c->acelera();
		}

		pos = posAtual;

		if (pos != 1) {
			if (pos != carrosNaPista) {
				c->acelera();
			}
			else {//esta em ultimo lugar
				c->trava();
			}

		}
	}
	return true;
}


