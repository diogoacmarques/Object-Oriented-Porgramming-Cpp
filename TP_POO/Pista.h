#pragma once
#include "Piloto.h"
#include <string>
#include <vector>
class Pista
{
	const int comprimento;
	int nMax;
	std::vector<Piloto*> pilotosEmCompeticao;
	bool emCompeticao;
public:
	Pista(int nM, int comp);
	~Pista();

	//poem o piloto na pista com o seu carro
	bool insere(Piloto * p);

	int obtemComprimento() const;
	int obtemNMax() const;

	bool passaTempo(int segundos);

	bool iniciaCorrida();
	bool terminarCorrida();
	bool obtemEstado() const;

	//toString
	std::string obtemPista();

};

