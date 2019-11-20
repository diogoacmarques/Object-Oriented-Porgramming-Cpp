#pragma once
#include "Piloto.h"
#include <string>
#include <vector>
class Pista
{
	const int comprimento;
	int nMax;
	std::vector<Piloto*> pilotosEmCompeticao;
public:
	Pista(int nM, int comp);
	~Pista();

	//poem o piloto na pista com o seu carro
	bool insere(Piloto * p);

	int obtemComprimento() const;
	int obtemNMax() const;

	bool passaSegundo();

	bool terminarCorrida();

	//toString
	std::string obtemCorrida();

};

