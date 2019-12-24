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
	bool recebeTodosCarros(std::vector<Carro*> c);
	bool recebeCarro(Carro * c);
	Carro * obtemCarroDisponivel();
	bool carregaTodasBaterias();

	std::string listaCarros() const;
};

