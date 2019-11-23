#include "Pista.h"
#include <iostream>
#include <sstream>

using namespace std;

Pista::Pista(int nM, int comp):comprimento(comp),nMax(nM), emCompeticao(false)
{
	cout << "Construtor Pista" << endl;
}

Pista::~Pista()
{
	cout << "Destrutor da pista" << endl;
}

bool Pista::insereEquipa(Equipa * e)
{
	if (equipasNaPista.size() + 1 >= nMax) {
		equipasNaPista.push_back(e);
		cout << "A pista(" << nMax << ") ja nao aguenta com mais equipa(" << equipasNaPista.size() << ")" << endl;
		return false;
	}	
	else {
		equipasNaPista.push_back(e);
		cout << "A Pista inseriu a equipa " << e->obtemId() << endl;
		return true;
	}
		
}

int Pista::obtemComprimento() const
{
	return comprimento;
}

int Pista::obtemNMax() const
{
	return nMax;
}

bool Pista::passaTempo(int segundos)
{
	string lixo;
	bool check = true;
	if (equipasNaPista.size() == 0) {
		cout << "nao existem equipas em competicao" << endl;
		terminarCorrida();
		return false;
	}
	//verificar o piloto e conforme o seu tipo, atua

	//e possivel obter a localização do carro através do piloto

	if (segundos == 0) {
		cout << obtemPista();
		return true;
	}

	for (int i = 0; i < segundos; i++) {
		for (int i = 0; i < equipasNaPista.size(); i++) {
			check = equipasNaPista.at(i)->passaSegundo();

			//verifica se ganhou
			if (equipasNaPista.at(i)->obtemDistanciaTotal() >= comprimento) {
				cout << "A equipa " << equipasNaPista.at(i)->obtemId() << " acabou a corrida" << endl;
				equipasNaPista.at(i)->saiDaPista();
				equipasNaPista.erase(equipasNaPista.begin() + i);
				i--;
				continue;
			}

			if (!check) {//se nao consegue andar mais(falta bateria /acidente/...)
				cout << "O piloto " << equipasNaPista.at(i)->obtemId() << " nao pode andar mais" << endl;
				equipasNaPista.erase(equipasNaPista.begin() + i);
				i--;
				check = true;
				continue;
			}	
				
		}
		cout << "Prima a tecla 'enter'..." << endl;
		getchar();
		cout << obtemPista();
	}


	return true;
}

bool Pista::iniciaCorrida()
{
	emCompeticao = true;
	return true;
}

bool Pista::terminarCorrida()
{
	for (int i = 0; i < equipasNaPista.size(); i++)
		equipasNaPista.at(i)->saiDaPista();
	//Permite terminar a corrida. Os carros são removidos da pista e vão para a garagem, e os pilotosaem dos veículos.
	emCompeticao = false;
	return false;
}

bool Pista::obtemEstado() const
{
	return emCompeticao;
}

std::string Pista::obtemPista()
{
	ostringstream os;
	if (obtemEstado()) {//se tem corrida
		os << "Pista:" << comprimento << "metros, com max de " << nMax << " carros" << endl;
		for (int i = 0; i < equipasNaPista.size(); i++)
			os << equipasNaPista.at(i)->toStringEquipa() << endl;
	}
	else {
		os << "A corrida ainda nao foi iniciada" << endl;
	}

	/*
	 indica se ela já foi iniciada ou não, e, em caso afirmativo, detalhando a
	classificação atual. Um exemplo de classificação pode ser:
	Informação sobre a corrida no autódromo Silverstone(5000 m) :
	1. B Ferrari / Vettel(rápido) - 5mAh, 290mAh - 2410m – 55m / s
	2. D Mercedes / Hamilton(crazy) - 5mAh, 350mAh - 2300m – 50m / s*/
	return os.str();
}
