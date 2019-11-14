#include "Carro.h"
#include <iostream>
#include <sstream>

using namespace std;

char Carro::idStatic = 'a';//inicializar o 'cont'

Carro::Carro(int capInicial, int capMax, string marca, string modelo):mAh(capInicial), capcidadeMaxima(capMax),marca(marca),modelo(modelo), id(idStatic++)
{
	if (idStatic < 'a' || idStatic > 'z')
		idStatic = '?';
	cout << "\tConstrutor_Carro:" << marca << "," << modelo << "(" << mAh << "/" << capcidadeMaxima << ")\n" << endl;
}

Carro::~Carro()
{
	cout << "Destrutor_Carro(" << marca << "/" << modelo << ")" << endl;
}

int Carro::carregaBateria(int n)
{
	if (n > 0 && !movimento) {// e positivo e esta parado
		if (mAh + n < capcidadeMaxima) {//nivel da bateria + n < capacidade maxima
			mAh += n;
		}
		else {
			cout << "A bateria esta no maximo, so pode carregar mais: " << capcidadeMaxima - mAh << endl;
		}
			
	}
	else {
		cout << "O carro esta em movimento ou n e negativo" << endl;
	}

	return 0;
}

char Carro::obtemId() const
{
	return id;
}

std::string Carro::obtemCarro() const
{
	ostringstream os;
	os << "Carro[" << id << "]:" << marca << "," << modelo << "(" << mAh << "/" << capcidadeMaxima << ")";
	return os.str();
}

bool Carro::temPiloto()
{
	if (nomePiloto.empty())
		return false;
	else
		return true;
}

bool Carro::entraPiloto(std::string nPiloto)
{
	if (!temPiloto()) {
		nomePiloto = nPiloto;
		return true;
	}
	else
		return false;
}

bool Carro::removePiloto()
{
	nomePiloto.clear();
	return true;
}

std::string Carro::obtemNomePiloto() const
{
	return nomePiloto;
}

std::string Carro::carroToString()
{
	ostringstream os;
	os << marca << "(" << modelo << "):" << endl;
	os << "\t\tId:" << id;
	os << "\n\t\tBateria:(" << mAh << "/" << capcidadeMaxima << ")";
	if(temPiloto())
	os << "\n\t\tPiloto:" << nomePiloto;
	return os.str();
}
