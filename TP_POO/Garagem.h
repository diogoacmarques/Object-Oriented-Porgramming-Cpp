#pragma once
#include "Carro.h"
#include <vector>
class Garagem
{
	std::vector<Carro*> carros;
public:
	Garagem();
	~Garagem();

	//funcionalidade
	bool recebeCarros(std::vector<Carro*> c);
	Carro * obtemCarroDisponivel();
	bool carregaTodasBaterias();

	std::string listaCarros() const;
};

