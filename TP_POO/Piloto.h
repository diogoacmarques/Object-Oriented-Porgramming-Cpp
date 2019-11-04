#pragma once
#include <string>
#include <vector>
class Piloto
{
	const std::string nome;
	vector<Piloto*> todosPilotos;
	Carro * c = nullptr;
public:
	Piloto();
	~Piloto();
};