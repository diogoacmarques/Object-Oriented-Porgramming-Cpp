#pragma once
#include "Carro.h"
#include <vector>
class Garagem
{
	std::vector<Carro*> carrosNaGaragem;
public:
	Garagem();
	~Garagem();

	//funcionalidade
	bool recebeCarros(std::vector<Carro*> tmp);
	Carro * saiParaPista();
	std::string obtemCarros() const;
};

