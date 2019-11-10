#pragma once
#include <string>
#include "Piloto.h"

class Carro
{
	std::string marca, modelo;
	static char idStatic;
	const char id;	
	//bateria
	int mAh;
	static const int capMax = 100;//igual para todos e nao e possivel alterar
	static const int bateriaInicial = 20;////igual para todos e nao e possivel alterar
	//moviemento
	bool movimento = false;
	int kmH = 0;
	static const int kmHMax = 120;
	//estado
	bool danoIrreparavel = false;
	bool sinalEmergencia = false;
	//Piloto
	Piloto * p = nullptr;
public:
	Carro(std::string marca, int kmHMax);
	Carro(std::string marca,std::string modelo, int kmHMax);
	~Carro();

	//funcionalidades
	int carregaBateria(int n);
};

