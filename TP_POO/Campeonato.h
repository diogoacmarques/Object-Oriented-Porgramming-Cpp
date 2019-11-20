#pragma once
//#include "Corrida.h"
#include "Autodromo.h"
#include <vector>
#include <string>

class Campeonato
{
	std::string nome;
	//conjunto de corridas, cada corrida decorre num autodromo diferente, uma de cada vez numa certa ordem
	std::vector<Autodromo*> autodromosCampeonato;
	int autodromoEmCompeticao;//inteiro para o numero do autodromo que esta a ser corrido no vetor
	
public:
	Campeonato(std::string n);//conjunto de autodromos onde iram correr os carros (os carros já se encontram em cada autodromo)
	~Campeonato();

	//funcionalidades
	bool carregaAutodromos(std::vector<Autodromo*> a);
	bool proximoAutodromo();

	Autodromo * obtemAutodromoCompeticao();

	bool verificaraExistenciaCorrida();
	bool passaTempo(int segundos);
};

