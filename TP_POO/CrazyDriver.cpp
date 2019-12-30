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

std::string CrazyDriver::obtemTipo() const
{
	return "crazy";
}

bool CrazyDriver::tomaDecisao(Carro * c, Pista * p)
{//melhorar funcao

	int carrosNaPista = p->obtemCarrosNaPista();
	int posAtual = p->obtemPosCorrida(c->obtemId());
	if ((rand() % 100) < 5) {//faz algo que danifica o automovel
		cout << c->obtemNomePiloto() << " danificou o carro " << c->obtemId() << endl;
		c->danificaCarro();
		if(p->obtemPosCorrida(c->obtemId()) + 1 < p->obtemNumCarrosEmCompeticao())
			p->danificaCarro(posAtual + 1);
	}


	if (c->obtemBateriaAtual() == 0) {
		cout << obtemNome() << "[crazy] ativar o sinal de emergencia por falta de bateria" << endl;
		c->ativaSinalEmergencia();
		return false;
	}


	if (p->obtemTempoCorrida() >= iniciaCorridaApos) {
		//cout << "ja passou o tempo iniciaCorridaApos" << endl;

		if (pos > posAtual && posAtual != carrosNaPista) {//ficou para tras mas nao e o ultimo
			cout << "a acelarar 2x" << endl;
			c->acelera();
			c->acelera();
			//return true;
		}

		pos = posAtual;
		//cout << "next test" << endl;

		if (pos != 1) {
			if (pos != carrosNaPista) {
				c->acelera();
			}
			else {//esta em ultimo lugar
				c->trava();
				cout << "estou em ultimo lugar... desisto" << endl;
			}

		}
	}//else
		//cout << "ainda nao passou o tempo(" << p->obtemTempoCorrida() << ") iniciaCorridaApos:" << iniciaCorridaApos <<  endl;

	return true;
}

Piloto * CrazyDriver::dupilica()
{
	return new CrazyDriver(*this);
}


