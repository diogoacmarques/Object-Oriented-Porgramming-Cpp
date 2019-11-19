#pragma once
#include "Carro.h"
#include "Piloto.h"
#include <vector>
class Garagem
{
	std::vector<Carro*> carrosNaGaragem;
	std::vector<Piloto*> pilotosNaGaragem;
public:
	Garagem();
	~Garagem();

	//funcionalidade
	bool recebeCarros(std::vector<Carro*> tmp);
	Piloto* saiParaPista();//envia o piloto para a pista

	std::string obtemCarros() const;
	std::string obtemPilotos() const;

};

