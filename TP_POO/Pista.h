#pragma once
#include "Carro.h"
#include <string>
#include <vector>
class Pista
{
	const int comprimento;
	int nMax;
	std::vector<Carro*> carrosNaPista;
	bool emCompeticao;
public:
	Pista(int nM, int comp);
	~Pista();

	//poem equipa na pista
	bool insereCarro(Carro * c);
	std::vector<Carro*> removeCarros();

	int obtemComprimento() const;
	int obtemNMax() const;

	bool passaTempo(int segundos);

	bool iniciaCorrida();
	bool terminarCorrida();
	bool obtemEstado() const;

	//toString
	std::string obtemPista() const;

};

