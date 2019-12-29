#pragma once
#include "Piloto.h"
class CrazyDriver : public Piloto
{
	int iniciaCorridaApos;
	int pos;
public:
	CrazyDriver(std::string n);
	~CrazyDriver();

	std::string obtemTipo() const;

	bool tomaDecisao(Carro * c, Pista * p);
	Piloto * dupilica();
};

