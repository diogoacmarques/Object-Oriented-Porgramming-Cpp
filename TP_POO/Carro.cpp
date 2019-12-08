#include "Carro.h"
#include <iostream>
#include <sstream>

using namespace std;

char Carro::idStatic = 'a';//inicializar o 'cont'

Carro::Carro(int velMax,int capInicial, int capMax, string marca, string modelo):velcidadeMaxima(velMax),mAh(capInicial), capcidadeMaxima(capMax),marca(marca),modelo(modelo), id(idStatic++), piloto(nullptr),naPista(false)
{
	if (idStatic < 'a' || idStatic > 'z')
		idStatic = '?';
	cout << "\tConstrutor_Carro:" << marca << "," << modelo << "(" << mAh << "/" << capcidadeMaxima << ")\n" << endl;
}

Carro::~Carro()
{
	cout << "Destrutor_Carro(" << marca << "/" << modelo << ")" << endl;
}

int Carro::obtemBateriaMax() const
{
	return capcidadeMaxima;
}

int Carro::carregaBateria(int n)
{
	if (n > 0 && !movimento) {// e positivo e esta parado
		if (mAh + n < capcidadeMaxima) {//nivel da bateria + n < capacidade maxima
			mAh += n;
		}
		else {
			mAh = capcidadeMaxima;
			cout << "O carro " << id << " foi carregado completamente " << mAh << "mAh/" << capcidadeMaxima << endl;
		}
			
	}
	else {
		cout << "O carro esta em movimento ou nao e negativo" << endl;
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

int Carro::obtemVelMax() const
{
	return velcidadeMaxima;
}

std::string Carro::obtemCarro() const
{
	ostringstream os;
	os << "Carro[" << id << "]:" << marca << "," << modelo << "(" << mAh << "/" << capcidadeMaxima << ")";
	return os.str();
}

//bool Carro::temEquipa() const
//{
//	if (idEquipa == -1)
//		return false;
//	else
//		return true;
//}
//
//bool Carro::adicionaEquipa(int id)
//{
//	if (!temEquipa()) {
//		idEquipa = id;
//		return true;
//	}
//	else
//		return false;
//}
//
//bool Carro::removeEquipa()
//{
//	idEquipa = -1;
//	return true;
//}


bool Carro::temPiloto() const
{
	if (piloto == nullptr)
		return false;
	else
		return true;
}

bool Carro::adicionaPiloto(Piloto * p)
{
	piloto = p;
	return true;
}

bool Carro::removePiloto()
{
	piloto = nullptr;
	return true;
}

std::string Carro::obtemNomePiloto() const
{
	return piloto->obtemNome();
}

bool Carro::verificaPista() const
{
	return naPista;
}

bool Carro::entraPista()
{
	naPista = true;
	return true;
}

bool Carro::saiPista()
{
	naPista = false;
	return true;
}

bool Carro::entraNaGaragem()
{
	movimento = false;
	naPista = false;
	return true;
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

bool Carro::passaSegundo()
{
	piloto->tomaDecisao(this);
	return false;
}

bool Carro::resetDistancia()
{
	mPercorrido = 0;
	return true;
}

std::string Carro::carroToString() const
{
	ostringstream os;
	os << "carro[" << id << "]:" << marca << "(" << modelo << ") com bateria " << mAh << "/" << capcidadeMaxima << " e velocidade maxima de " << velcidadeMaxima;
	/*if (tempiloto())
		os << " tem piloto " << nomepiloto;*/

	/*if (movimento)
		os << " a andar " << metrosegundo << " mts/seg (" << mpercorrido << "metros total)";
*/
	return os.str();
}

int Carro::obtemBateriaAtual() const
{
	return mAh;
}

