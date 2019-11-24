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

bool Equipa::entraGaragem()
{
	piloto->paraMovimento();
	carro->resetDistancia();
	return true;
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
	//meta 1
	/*o Nesta meta os carros movem - se sempre uma posição(metro / s) para a frente
		independentemente do piloto que o conduz.Não são carregados nem gastam
		energia*/
	bool verifica = true;
	if (carro->obtemVelocidade() == 0) {//meta 1
		piloto->passaSegundo();//verifica a posição e age conforme o tipo de piloto
	}
	else {
		return carro->passaSegundo();//mantem velocidade e aumenta a distancia percorrida
	}

	return true;
}

std::string Equipa::toStringEquipa()
{
	//1. B Ferrari / Vettel(rápido) - 5mAh, 290mAh - 2410m – 55m / s
	ostringstream os;
	os << carro->obtemId() << " " << piloto->obtemNome() << "(" << piloto->obtemTipo() << ") - " << carro->obtemBateriaAtual() << "mAh, " << carro->obtemBateriaMax() << "mAh - " <<
		carro->obtemDistanciaPercorrida() << "m - " << carro->obtemVelocidade() << "m/s";

	return os.str();
}

std::string Equipa::listaCarros()
{
	ostringstream os;
	os << carro->obtemId() << " " << piloto->obtemNome() << "(" << piloto->obtemTipo() << ") - " << carro->obtemBateriaAtual() << "mAh, " << carro->obtemBateriaMax() << "mAh - VelocidadeMax:" <<
		carro->obtemVelMax() << "m/s";
	return os.str();
}
