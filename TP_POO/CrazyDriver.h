#pragma once
#include "Piloto.h"
class CrazyDriver : public Piloto
{
	int iniciaCorridaApos;
	int pos;
public:
	CrazyDriver(std::string n);
	~CrazyDriver();

	bool tomaDecisao(Carro * c, Pista * p);
};

