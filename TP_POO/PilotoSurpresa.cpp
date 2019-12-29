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

std::string PilotoSurpresa::obtemTipo() const
{
	return "surpresa";
}

bool PilotoSurpresa::tomaDecisao(Carro * c, Pista * p)
{
	return false;
}

Piloto * PilotoSurpresa::dupilica()
{
	return new PilotoSurpresa(*this);
}
