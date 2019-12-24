#pragma once
#include "Piloto.h"

class PilotoRapido : public Piloto
{
	int tempoPassado;
public:
	PilotoRapido(std::string n);
	~PilotoRapido();

	bool tomaDecisao(Carro * c, Pista * p);
};

