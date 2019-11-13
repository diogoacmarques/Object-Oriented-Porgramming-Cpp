#include "Pista.h"
#include <iostream>

using namespace std;

Pista::Pista(int nM, int comp):comprimento(comp),nMax(nM)
{
	cout << "Construtor Pista" << endl;
}

Pista::~Pista()
{
}

int Pista::obtemComprimento() const
{
	return comprimento;
}

int Pista::obtemNMax() const
{
	return nMax;
}

bool Pista::terminarCorrida()
{
	//Permite terminar a corrida.Os carros são removidos da pista e vão para a garagem, e os pilotosaem dos veículos.	
	return false;
}

std::string Pista::obtemCorrida()
{
	/*
	 indica se ela já foi iniciada ou não, e, em caso afirmativo, detalhando a
	classificação atual. Um exemplo de classificação pode ser:
	Informação sobre a corrida no autódromo Silverstone(5000 m) :
	1. B Ferrari / Vettel(rápido) - 5mAh, 290mAh - 2410m – 55m / s
	2. D Mercedes / Hamilton(crazy) - 5mAh, 350mAh - 2300m – 50m / s*/
	return std::string();
}
