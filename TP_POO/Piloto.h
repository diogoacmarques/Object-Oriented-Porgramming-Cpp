#pragma once
//#include "Carro.h"
#include <string>
#include <vector>
class Piloto
{
	//const std::string nome;
	std::string nome;
public:
	Piloto(std::string n);
	~Piloto();

	//funcionalidades
		//carro
	bool checkCar() const;
	//bool getInCar(Carro * c);
	bool getOutCar();
};