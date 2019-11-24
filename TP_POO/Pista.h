#pragma once
#include "Equipa.h"
#include <string>
#include <vector>
class Pista
{
	const int comprimento;
	int nMax;
	std::vector<Equipa*> equipasNaPista;
	bool emCompeticao;
public:
	Pista(int nM, int comp);
	~Pista();

	//poem equipa na pista
	bool insereEquipa(Equipa * e);
	std::vector<Equipa*> removeEquipas();

	int obtemComprimento() const;
	int obtemNMax() const;

	bool passaTempo(int segundos);

	bool iniciaCorrida();
	bool terminarCorrida();
	bool obtemEstado() const;

	//toString
	std::string obtemPista();

};

