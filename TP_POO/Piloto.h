#pragma once
//#include "Carro.h"
#include <string>
#include <vector>
class Piloto
{
	const std::string nome;
	const std::string tipo;
public:
	Piloto(std::string n);
	~Piloto();

	//funcionalidades
	std::string obtemNome() const;
	   
		//carro
	bool verificaCarro() const;//verifica se esta dentro de algum carro
	bool entraNoCarro();
	bool saiDoCarro();

	//toString
	std::string pilotoToString();
};