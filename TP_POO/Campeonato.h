#pragma once
#include "Carro.h"
#include "Piloto.h"
#include "Autodromo.h"


#include <vector>
#include <string>

class Campeonato
{
	//conjunto de corridas, cada corrida decorre num autodromo diferente, uma de cada vez numa certa ordem
	
	std::vector<Carro*> campCarros;
	std::vector<Piloto*> campPilotos;
	std::vector<Autodromo*> campAutodromos;
	
public:
	Campeonato(std::vector<Carro*> c, std::vector<Piloto*> p, std::vector<Autodromo*> a);
	~Campeonato();
};

