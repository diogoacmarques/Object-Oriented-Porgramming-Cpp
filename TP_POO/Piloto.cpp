#include "Piloto.h"

Piloto::Piloto(std::string n):nome(n)
{
	//funcao para confirmar que nao existe nenhum nome igual
}

Piloto::~Piloto()
{
}
std::string Piloto::obtemNome() const
{
	return nome;
}
/*
bool Piloto::checkCar() const
{
	if (carro != nullptr)
		return true;
	else
		return false;
}

bool Piloto::getInCar(Carro * c)
{
	carro = c;
	return true;
}

bool Piloto::getOutCar()
{
	carro = nullptr;
	return true;
}
*/