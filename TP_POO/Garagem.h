#pragma once
#include "Equipa.h"
#include <vector>
class Garagem
{
	std::vector<Equipa*> equipas;
public:
	Garagem();
	~Garagem();

	//funcionalidade
	bool recebeEquipa(std::vector<Equipa*> e);
	Equipa * obtemEquipaDisponivel();
	bool carregaTodasBaterias();

	std::string listaCarros() const;
};

