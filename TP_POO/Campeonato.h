#pragma once
#include "Autodromo.h"
#include <vector>
#include <string>

class Campeonato
{
	//conjunto de corridas, cada corrida decorre num autodromo diferente, uma de cada vez numa certa ordem
	std::string nome;	
	std::vector<Autodromo*> autodromosCampeonato;//vector com o pointeiro para todos os campeoantos
	int autodromoEmCompeticao;//inteiro para o numero do autodromo em que a corrida esta a ser efetuada
public:
	Campeonato(std::string n);//conjunto de autodromos onde iram correr os carros (os carros já se encontram em cada autodromo)
	~Campeonato();

	//funcionalidades
	bool carregaAutodromos(std::vector<Autodromo*> a);
	bool proximoAutodromo();
	bool termina();

	Autodromo * obtemAutodromoCompeticao() const;
	int obtemNumAutodromoCompeticao() const;

	std::vector<Carro*> obtemCarrosAutodromoAnterior();

	bool verificaraExistenciaCorrida() const;
	bool passaTempo(int segundos);
};

