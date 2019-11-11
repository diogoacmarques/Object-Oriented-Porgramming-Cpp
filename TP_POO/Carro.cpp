#include "Carro.h"
#include <iostream>

using namespace std;

char Carro::idStatic = 'a';//inicializar o 'cont'

Carro::Carro(int capInicial, int capMax, std::string marca, std::string modelo):mAh(capInicial), capcidadeMaxima(capMax),marca(marca),modelo(modelo), id(idStatic++)
{
	if (idStatic < 'a' || idStatic > 'z')
		idStatic = '?';
	cout << "Construtor[Carro]:" << marca << "," << modelo << " (" << mAh << "/" << capcidadeMaxima << ")" << endl;
}

Carro::~Carro()
{
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
