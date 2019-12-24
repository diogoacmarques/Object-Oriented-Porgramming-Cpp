#include "Carro.h"
#include "Pista.h"
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

bool Carro::verificaDano() const
{
	if (danoIrreparavel) {
		cout << "O carro esta danificado!" << endl;
		return true;
	}
	return false;
}

bool Carro::verificaEmergencia() const
{
	return sinalEmergencia;
}

int Carro::obtemBateriaMax() const
{
	return capcidadeMaxima;
}

int Carro::carregaBateria(int n)
{
	if (verificaDano())
		return false;

	if (n > 0 && metroSegundo == 0) {// e positivo e esta parado
		if (mAh + n <= capcidadeMaxima) {//nivel da bateria + n < capacidade maxima
			mAh += n;
		}
		else {
			mAh = capcidadeMaxima;
			cout << "O carro " << id << " foi carregado completamente " << mAh << "mAh/" << capcidadeMaxima << endl;
		}	
	}
	else {
		cout << "O carro esta em movimento ou o valor nao e valido" << endl;
	}

	return 0;
}

bool Carro::carregamentoTotal()
{
	if (verificaDano())
		return false;

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

void Carro::ativaSinalEmergencia()
{
	sinalEmergencia = true;
	return;
}

void Carro::danificaCarro()
{
	danoIrreparavel = true;
	return;
}

std::string Carro::obtemCarro() const
{
	ostringstream os;
	os << "Carro[" << id << "]:" << marca << "," << modelo << "(" << mAh << "/" << capcidadeMaxima << ")";
	return os.str();
}

bool Carro::verificaPiloto() const
{
	if (piloto == nullptr)
		return false;
	else
		return true;
}

bool Carro::adicionaPiloto(Piloto * p)
{
	if (!verificaDano()){
		piloto = p;
		return true;
	}
	else
		return false;
	
	
}

bool Carro::removePiloto()
{
	if (verificaDano())
		return false;

	piloto = nullptr;
	return true;
}

bool Carro::decisaoPiloto(Pista * p)
{
	piloto->tomaDecisao(this, p);
	return passaSegundo();

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
	if (verificaDano())
		return false;

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
	if (verificaDano())
		return false;

	metroSegundo = 0;
	naPista = false;
	return true;
}

int Carro::obtemVelocidade() const
{
	return metroSegundo;
}

bool Carro::acelera()
{

	if (verificaDano() && sinalEmergencia)
		return false;

	if (mAh > 0) {
		if (velcidadeMaxima < metroSegundo) {
			metroSegundo++;
			//passaSegundo
			return true;
		}
		else {
			cout << "O carro ja esta na sua velocidade maxima" << endl;
		}
		
	}
	else {
		cout << "Carro " << id << " ficou sem bateria" << endl;
		para();
		return false;
	}

	return false;
}

bool Carro::trava()
{
	if (metroSegundo > 0 && !verificaDano()) {
		metroSegundo--;
		if(metroSegundo > 0)
			passaSegundo();
		return true;
	}
	else {
		cout << "Carro " << id << " ficou sem bateria" << endl;
		para();
		return false;
	}

	return false;
}

bool Carro::para()
{
	metroSegundo = 0;
	return true;
}


int Carro::obtemDistanciaPercorrida() const
{
	return mPercorrido;
}

bool Carro::passaSegundo()
{
	if (verificaDano())
		return false;

	if (mAh <= metroSegundo) {//ainda tem energia
		mAh -= metroSegundo;
		mPercorrido += metroSegundo;
	}
	else {//nao tem energia
		mAh = 0;
		trava();
	}	

	return true;
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

