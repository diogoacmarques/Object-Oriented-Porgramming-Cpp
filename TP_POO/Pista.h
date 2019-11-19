#pragma once
#include "Carro.h"
#include <string>
#include <vector>
class Pista
{
	const int comprimento;
	int nMax;
	std::vector<Carro*> carrosEmCompeticao;
public:
	Pista(int nM, int comp);
	~Pista();

	//poem os carros na pista
	bool insereCarro(Carro * c);

	int obtemComprimento() const;
	int obtemNMax() const;

	bool passaSegundo();

	bool terminarCorrida();

	//toString
	std::string obtemCorrida();

};

