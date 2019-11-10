#pragma once
#include <string>
#include "Carro.h"
#include "Piloto.h"
class DVG
{
	std::string nome;
	std::vector<Piloto*> todosPilotos;
	std::vector<Carro*> todosCarros;
public:
	DVG(std::string n);
	~DVG();
};