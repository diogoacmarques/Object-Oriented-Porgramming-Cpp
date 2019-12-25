#include "Pista.h"
#include <iostream>
#include <sstream>

using namespace std;

Pista::Pista(int nM, int comp) :comprimento(comp), nMax(nM), emCompeticao(false)
{
	cout << "Construtor Pista" << endl;
}

Pista::~Pista()
{
	cout << "Destrutor da pista" << endl;
}

bool Pista::insereCarro(Carro * c)
{
	if (emCompeticao) {
		cout << "A corrida ja comecou" << endl;
		return false;
	}

	if (carrosNaPista.size() + 1 >= nMax) {
		carrosNaPista.push_back(c);
		cout << "A pista(" << nMax << ") ja nao aguenta com mais carros(" << carrosNaPista.size() << ")" << endl;
		return false;
	}
	else {
		carrosNaPista.push_back(c);
		cout << "A Pista inseriu o carro " << c->obtemId() << endl;
		return true;
	}

}

Carro * Pista::removeCarro(char idCarro)
{
	vector<Carro*>::iterator it = carrosNaPista.begin();
	while (it != carrosNaPista.end()) {
		if((*it)->obtemId() == idCarro){
			(*it)->saiPista();

		}

		it++;
	}
	return nullptr;
}

std::vector<Carro*> Pista::removeTodosCarros()
{
	vector<Carro*> tmp = carrosNaPista;
	carrosNaPista.clear();
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
	if (!emCompeticao) {
		cout << "A pista nao se encontra em corrida" << endl;
		return false;
	}

	string lixo;
	bool check = true;
	if (carrosNaPista.size() == 0) {
		cout << "nao existem equipas em competicao" << endl;
		return true;
	}


	if (segundos == 0) {
		cout << obtemPista();
		return true;
	}


	bool verifcaCorrida = false;
	for (int i = 0; i < segundos; i++) {
		verifcaCorrida = false;
		for (int j = 0; j < carrosNaPista.size(); j++) {
		

			if (carrosNaPista.at(j)->verificaPista()) {

				if (carrosNaPista.at(j)->verificaEmergencia())//se tiver sinal de emergencia ligado
					removeCarro(carrosNaPista.at(j)->obtemId());

				verifcaCorrida = true;
				check = carrosNaPista.at(j)->decisaoPiloto(this);

				//verifica se ganhou
				if (carrosNaPista.at(j)->obtemDistanciaPercorrida() >= comprimento) {
					cout << "A equipa " << carrosNaPista.at(j)->obtemId() << " acabou a corrida" << endl;
					int pos = obtemPosCorrida(carrosNaPista.at(j)->obtemId());
					if (pos == 0) {
						carrosNaPista.at(j)->acabaCorrida(10);
					}
					else if (pos == 1) {
						carrosNaPista.at(j)->acabaCorrida(5);
					}
					else if (pos == 2) {
						carrosNaPista.at(j)->acabaCorrida(2);
					}
					else {
						carrosNaPista.at(j)->acabaCorrida(0);
					}
					
					//equipasNaPista.erase(equipasNaPista.begin() + j);
					continue;
				}

				if (!check) {//se nao consegue andar mais(falta bateria /acidente/...)
					cout << "O piloto " << carrosNaPista.at(j)->obtemId() << " nao pode andar mais" << endl;
					carrosNaPista.at(j)->saiPista();
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
			terminarCorrida();
			return false;
		}
			
		
	}

	return true;
}

int Pista::obtemTempoCorrida() const
{
	return tempoCorrida;
}

int Pista::obtemCarrosNaPista() const
{
	return (int)carrosNaPista.size();
}

int Pista::obtemPosCorrida(char idCarro)
{
	for (int i = 0; i < carrosNaPista.size(); i++)
		if (carrosNaPista.at(i)->obtemId() == idCarro)
			return i;

	return -1;
}

bool Pista::danificaCarro(int pos)
{
	carrosNaPista.at(pos)->danificaCarro();
	return true;
}

bool Pista::iniciaCorrida()
{
	if(carrosNaPista.size() < 2){
		cout << "Nao existem carros suficientes para iniciar a corrida" << endl;
		return false;
	}
	tempoCorrida = 0;
	emCompeticao = true;
	return true;
}

bool Pista::terminarCorrida()
{
	for (int i = 0; i < carrosNaPista.size(); i++)
		carrosNaPista.at(i)->saiPista();
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
		for (int i = 0; i < carrosNaPista.size(); i++)
			os << carrosNaPista.at(i)->carroToString() << endl;
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
