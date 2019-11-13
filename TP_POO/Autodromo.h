#pragma once
#include "Pista.h"
#include "Garagem.h"
#include <string>
class Autodromo
{
	const std::string nome;
	Pista pista;
	Garagem garagem;
public:
	Autodromo(int n_Max, int comprimento, std::string n);
	~Autodromo();

	std::string obtemNome() const;
	std::string autodromoToString() const;
};

