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
{
	srand((int)time(NULL));
	int carrosNaPista = p->obtemCarrosNaPista();
	int posAtual = p->obtemPosCorrida(c->obtemId());
	if ((rand() % 100) < 5) {//faz algo que danifica o automovel
		c->danificaCarro();
		//cout << c->obtemNomePiloto() << " danificou o carro " << c->obtemId() << endl;	
		if (p->obtemPosCorrida(c->obtemId()) + 1 < p->obtemNumCarrosEmCompeticao()) {
			p->danificaCarro(posAtual + 1);
			return true;
		}
			
	}


	if (c->obtemBateriaAtual() == 0) {//se ficar sem energia
		cout << obtemNome() << "[crazy] ativar o sinal de emergencia por falta de bateria" << endl;
		c->ativaSinalEmergencia();
		return false;
	}

	bool decisao = false;//veririfa se ja tomou alguma decisao

	if (p->obtemTempoCorrida() >= iniciaCorridaApos) {
		//cout << "ja passou o tempo iniciaCorridaApos" << endl;

		if (pos == 0 && !decisao) {//se esta em primeiro
			//mantem a velocidade
			decisao = true;
		}

		if (pos == carrosNaPista && !decisao) {//se esta em ultimo
			c->trava();
			decisao = true;
		}


		if (!decisao)
			c->acelera();//nao esta em primeiro ou em ultimo(esta no meio)


		if (pos < posAtual && !decisao) {//antiga < atual = perdeu lugares	
			c->acelera();
			decisao = true;
		}

		pos = posAtual;//atualiza posicao

	}//else
		//cout << "ainda nao passou o tempo(" << p->obtemTempoCorrida() << ") iniciaCorridaApos:" << iniciaCorridaApos <<  endl;

	return true;
}

Piloto * CrazyDriver::dupilica()
{
	return new CrazyDriver(*this);
}


