#pragma once
#include "Pista.h"
#include "Garagem.h"
#include "Carro.h"
#include "Piloto.h"
#include <string>
#include <vector>
class Autodromo
{
	static std::vector<std::string> todosNomesAutodromos;
	std::string nome;
	Pista pista;
	Garagem garagem;
public:
	Autodromo(int n_Max, int comprimento, std::string n);
	~Autodromo();
	std::string obtemNome() const;
	std::string autodromoToString() const;


	//garagem
	bool carregaCarros(std::vector<Carro*> vectorCarros);
	std::string obtemCarrosGaragem() const;
	bool carregaPilotos(std::vector<Piloto*> vectorPilotos);

	//pista
	bool inserePilotosPista();
	bool passaTempo(int segundos);

};

