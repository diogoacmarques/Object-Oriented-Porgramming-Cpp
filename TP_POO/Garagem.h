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
	Carro * obtemCarro(char idCarro) const;
	bool destroiCarro(char idCarro);
	bool carregaTodasBaterias();
	int obtemNumCarros() const;
	std::vector<Carro *> retiraTodosCarros();

	std::string listaCarros() const;
};

