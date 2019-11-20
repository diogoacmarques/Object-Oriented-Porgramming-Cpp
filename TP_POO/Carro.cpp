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

bool Carro::carregamentoTotal()
{
	mAh = capcidadeMaxima;
	return true;
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

int Carro::obtemVelocidade() const
{
	return metroSegundo;
}

bool Carro::acelera(int quantidade)
{

	if (danoIrreparavel && sinalEmergencia)
		return false;

	if (mAh > 0) {
		metroSegundo += quantidade;
		movimento = true;
		passaSegundo();
		return true;
	}
	else {
		cout << "Carro " << id << " ficou sem bateria" << endl;
		para();
		return false;
	}
}

bool Carro::para()
{
	metroSegundo = 0;
	movimento = false;
	return true;
}


int Carro::obtemDistanciaPercorrida() const
{
	return mPercorrido;
}

void Carro::passaSegundo()
{
	if (mAh - metroSegundo >= 0) {//se tem bateria para a distancia
		mAh -= metroSegundo;
		mPercorrido += metroSegundo;
	}
	else
		para();
}

std::string Carro::carroToString()
{
	ostringstream os;
	os << "Carro[" << id << "]:" << marca << "(" << modelo << ") com " << mAh << "/" << capcidadeMaxima;
	if (temPiloto())
		os << " tem piloto " << nomePiloto; 

	if (movimento)
		os << " a andar " << metroSegundo << " mts/seg (" << mPercorrido << "metros total)";

	return os.str();
}
