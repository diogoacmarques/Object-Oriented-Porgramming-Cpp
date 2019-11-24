#pragma once
#include "Piloto.h"
#include "Carro.h"
#include <vector>

class Equipa
{
	static int idStatic;
	int id;
	Carro * carro;
	Piloto * piloto;
	bool naPista;
	int posicao, segundosCorrida;
public:
	Equipa(Carro * c, Piloto * p);
	~Equipa();

	//self
	int obtemId() const;
	bool entraGaragem();

	//Carro
	int obtemIdCarro() const;
	int obtemDistanciaTotal() const;

	//Pista
	bool entraNaPista();
	bool saiDaPista();
	bool verificaPista()const;

	bool carregaBateriaTotal();

	bool passaSegundo();

	std::string toStringEquipa();
	std::string listaCarros();
};

