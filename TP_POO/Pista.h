#pragma once
#include <string>
class Pista
{
	const int comprimento;
	int nMax;
public:
	Pista(int nM, int comp);
	~Pista();

	int obtemComprimento() const;
	int obtemNMax() const;

	bool terminarCorrida();

	//toString
	std::string obtemCorrida();

};

