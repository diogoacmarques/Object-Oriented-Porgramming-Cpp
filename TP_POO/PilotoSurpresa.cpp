#include "PilotoSurpresa.h"
#include <iostream>

using namespace std;

PilotoSurpresa::PilotoSurpresa(std::string n):Piloto(n)
{
	cout << "Construtor Piloto Supresa" << endl;
}

PilotoSurpresa::~PilotoSurpresa()
{
}

bool PilotoSurpresa::tomaDecisao(Carro * c, Pista * p)
{
	return false;
}
