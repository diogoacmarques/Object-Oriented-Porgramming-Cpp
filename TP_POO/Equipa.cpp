#include "Equipa.h"
#include <iostream>
#include <sstream>

using namespace std;

int Equipa::idStatic = 0;//inicializar do id

Equipa::Equipa(Carro * c, Piloto * p):carro(c),piloto(p),id(idStatic++)
{
	cout << "Construtor equipa:" << id << endl;
}

Equipa::~Equipa()
{
	cout << "Destrutor da equipa" << endl;
	piloto->removeEquipa();
	carro->removeEquipa();
}

int Equipa::obtemId() const
{
	return id;
}

int Equipa::obtemIdCarro() const
{
	return carro->obtemId();
}

int Equipa::obtemDistanciaTotal() const
{
	return carro->obtemDistanciaPercorrida();
}

bool Equipa::entraNaPista()
{
	naPista = true;
	return true;
}

bool Equipa::saiDaPista()
{
	naPista =  false;
	return true;
}

bool Equipa::verificaPista() const
{
	return naPista;
}

bool Equipa::carregaBateriaTotal()
{
	int batMaxima = carro->obtemBateriaMax();
	carro->carregaBateria(batMaxima);
	return true;
}

bool Equipa::passaSegundo()
{
	return false;
}

std::string Equipa::toStringEquipa()
{
	//1. B Ferrari / Vettel(rápido) - 5mAh, 290mAh - 2410m – 55m / s
	ostringstream os;
	os << carro->obtemId() << " " << piloto->obtemNome() << "(" << piloto->obtemTipo() << ") - " << carro->obtemBateriaAtual() << "mAh, " << carro->obtemBateriaMax() << "mAh - " <<
		carro->obtemDistanciaPercorrida() << "m - " << carro->obtemVelocidade() << "m/s";

	return os.str();
}
