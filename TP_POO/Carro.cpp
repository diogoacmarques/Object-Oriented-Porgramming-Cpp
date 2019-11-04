#include "Carro.h"
#include <iostream>

using namespace std;

char Carro::idStatic = 'a';//inicializar o 'cont'

Carro::Carro(std::string marca, int kmHMax):marca(marca),modelo("modelo base"),id(idStatic++), mAh(bateriaInicial)
{
	cout << "Criei o carro com modelo:" << modelo << "e char:" << id << endl;

	if (idStatic < 'a' || idStatic > 'z')
		idStatic = '?';
}

Carro::Carro(std::string marca, std::string modelo, int kmHMax) : marca(marca), modelo(modelo), id(idStatic++), mAh(bateriaInicial)
{
	cout << "Criei o carro sem modelo:" << modelo << "e char:" << id << endl;
	if (idStatic < 'a' || idStatic > 'z')
		idStatic = '?';
}

Carro::~Carro()
{
}

int Carro::carregaBateria(int n)
{
	if (n > 0 && !movimento) {// e positivo e esta parado
		if (mAh + n < capMax) {//nivel da bateria + n < capacidade maxima
			mAh += n;
		}
		else {
			cout << "A bateria esta no maximo, so pode carregar mais: " << capMax - mAh << endl;
		}
			
	}
	else {
		cout << "O carro esta em movimento ou n e negativo" << endl;
	}

	return 0;
}
