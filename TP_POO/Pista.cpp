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

bool Pista::insere(Piloto * p)
{
	if (pilotosEmCompeticao.size() + 1 >= nMax) {
		pilotosEmCompeticao.push_back(p);
		cout << "A pista(" << nMax << ") ja nao aguenta com mais pilotos(" << pilotosEmCompeticao.size() << ")" << endl;	
		return false;
	}	
	else {
		pilotosEmCompeticao.push_back(p);
		cout << "A Pista inseriu o piloto " << p->obtemNome() << endl;
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
	bool check = true;
	if (pilotosEmCompeticao.size() == 0) {
		cout << "nao existem pilotos em competicao" << endl;
		terminarCorrida();
		return false;
	}
	//verificar o piloto e conforme o seu tipo, atua

	//e possivel obter a localiza��o do carro atrav�s do piloto

	for (int i = 0; i < segundos; i++) {
		for (int i = 0; i < pilotosEmCompeticao.size(); i++) {
			check = pilotosEmCompeticao.at(i)->passaSegundo();

			//verifica se ganhou
			if (pilotosEmCompeticao.at(i)->obtemDistanciaPercorrida() >= comprimento) {
				cout << "O piloto " << pilotosEmCompeticao.at(i)->obtemNome() << " acabou a corrida" << endl;
				pilotosEmCompeticao.at(i)->saiPista();
				pilotosEmCompeticao.erase(pilotosEmCompeticao.begin() + i);
				i--;
				continue;
			}

			if (!check) {//se nao consegue andar mais
				cout << "O piloto " << pilotosEmCompeticao.at(i)->obtemNome() << " nao pode andar mais" << endl;
				pilotosEmCompeticao.erase(pilotosEmCompeticao.begin() + i);
				i--;
				check = true;
				continue;
			}	
				
		}

	}
	

	cout << obtemPista();
	//for (int i = 0; i < pilotosEmCompeticao.size(); i++)
		//cout << "Piloto '" << pilotosEmCompeticao.at(i)->obtemNome() << "' com carro '" <<
		//pilotosEmCompeticao.at(i)->obtemIdCarro() << "' percorreu " << pilotosEmCompeticao.at(i)->obtemDistanciaPercorrida() << " metros" << endl;
	
	return true;
}

bool Pista::iniciaCorrida()
{
	emCompeticao = true;
	return true;
}

bool Pista::terminarCorrida()
{
	for (int i = 0; i < pilotosEmCompeticao.size(); i++)
		pilotosEmCompeticao.at(i)->saiPista();
	//Permite terminar a corrida.Os carros s�o removidos da pista e v�o para a garagem, e os pilotosaem dos ve�culos.
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
		for (int i = 0; i < pilotosEmCompeticao.size(); i++)
			os << pilotosEmCompeticao.at(i)->obtemCarro() << endl;
	}
	else {
		os << "A corrida ainda nao foi iniciada" << endl;
	}

	/*
	 indica se ela j� foi iniciada ou n�o, e, em caso afirmativo, detalhando a
	classifica��o atual. Um exemplo de classifica��o pode ser:
	Informa��o sobre a corrida no aut�dromo Silverstone(5000 m) :
	1. B Ferrari / Vettel(r�pido) - 5mAh, 290mAh - 2410m � 55m / s
	2. D Mercedes / Hamilton(crazy) - 5mAh, 350mAh - 2300m � 50m / s*/
	return os.str();
}
