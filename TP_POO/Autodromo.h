#pragma once
#include "Pista.h"
#include "Garagem.h"
#include "Equipa.h"
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
	bool carregaEquipasGaragem(std::vector<Equipa *> e);
	bool carregaBaterias();
	//std::string obtemCarrosGaragem() const;

	//pista
	bool insereEquipaPista();

	std::string listaCarrosGaragem() const;


	void iniciaPista();
	void terminarCorrida();
	bool passaTempo(int segundos);

};

