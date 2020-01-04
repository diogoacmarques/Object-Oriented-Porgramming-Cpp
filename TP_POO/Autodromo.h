#pragma once
#include "Pista.h"
#include "Garagem.h"
#include <string>
#include <vector>

class Autodromo
{
	static std::vector<std::string> todosNomesAutodromos;
	std::string nome;
	Pista pista;
	Garagem garagem;
	bool preparado;
public:
	Autodromo(int n_Max, int comprimento, std::string n);
	~Autodromo();
	std::string obtemNome() const;
	std::string autodromoToString() const;

	//garagem
	bool obtemEstado() const;
	bool insereCarrosNaGaragem(std::vector<Carro *> e);
	bool carregaBaterias();
	int verificaNumCarrosGaragem() const;
	std::string listaCarrosGaragem() const;
	std::vector <Carro*> retiraCarros();

	//pista
	bool obtemEstadoPista() const;
	bool insereCarroPista();
	void iniciaPista();

	//Carro
	bool destroiCarro(char idCarro);
	void terminarCorrida();
	bool passaTempo(int segundos);

	//Piloto
	bool stopPiloto(std::string nomePiloto);
};

