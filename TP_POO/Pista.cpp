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

std::vector<Equipa*> Pista::removeEquipas()
{
	vector<Equipa*> tmp = equipasNaPista;
	equipasNaPista.clear();
	return tmp;
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
		return true;
	}
	//verificar o piloto e conforme o seu tipo, atua

	//e possivel obter a localização do carro através do piloto

	if (segundos == 0) {
		cout << obtemPista();
		return true;
	}
	bool verifcaCorrida = false;

	for (int i = 0; i < segundos; i++) {
		verifcaCorrida = false;
		for (int j = 0; j < equipasNaPista.size(); j++) {
			
			if (equipasNaPista.at(j)->verificaPista()) {
				verifcaCorrida = true;
				check = equipasNaPista.at(j)->passaSegundo();

				//verifica se ganhou
				if (equipasNaPista.at(j)->obtemDistanciaTotal() >= comprimento) {
					cout << "A equipa " << equipasNaPista.at(j)->obtemId() << " acabou a corrida" << endl;
					equipasNaPista.at(j)->saiDaPista();
					//equipasNaPista.erase(equipasNaPista.begin() + j);
					continue;
				}

				if (!check) {//se nao consegue andar mais(falta bateria /acidente/...)
					cout << "O piloto " << equipasNaPista.at(j)->obtemId() << " nao pode andar mais" << endl;
					equipasNaPista.at(j)->saiDaPista();
					//equipasNaPista.erase(equipasNaPista.begin() + j);
					check = true;
					continue;
				}

			}
				
		}

		if (verifcaCorrida) {
			cout << obtemPista();
			cout << "Prima a tecla 'enter'..." << endl;
			getchar();
			
		}
		else {
			cout << "Ja nao existe equipas a competir(final da corrida)" << endl;
			return false;
		}
			
		
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

std::string Pista::obtemPista() const
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
