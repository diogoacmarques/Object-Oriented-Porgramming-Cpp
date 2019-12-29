#pragma once
#include "Piloto.h"

class PilotoSurpresa : public Piloto
{
public:
	PilotoSurpresa(std::string n);
	~PilotoSurpresa();

	std::string obtemTipo() const;

	bool tomaDecisao(Carro * c, Pista * p);
	Piloto * dupilica();
};

