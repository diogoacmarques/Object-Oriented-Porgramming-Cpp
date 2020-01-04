#include "PilotoSurpresa.h"
#include "Pista.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

PilotoSurpresa::PilotoSurpresa(std::string n):Piloto(n)
{
	cout << "Construtor Piloto Supresa" << endl;
}

PilotoSurpresa::~PilotoSurpresa()
{
}

std::string PilotoSurpresa::obtemTipo() const
{
	return "surpresa";
}

bool PilotoSurpresa::tomaDecisao(Carro * c, Pista * p)
{
	srand((int)time(NULL));
	int prob = rand() % 100;
	int posAtual = p->obtemPosCorrida(c->obtemId());
	int carrosNaPista = p->obtemCarrosNaPista();

	if (prob < 10) {//faz algo que danifica o automovel
		c->danificaCarro();
		cout << c->obtemNomePiloto() << " danificou o carro " << c->obtemId() << endl;	
		if (p->obtemPosCorrida(c->obtemId()) + 1 < p->obtemNumCarrosEmCompeticao() && p->obtemPosCorrida(c->obtemId()) - 1 > 1) {  //Se nao estiver em ultimo, danifica o ultimo, nem em primeiro
			p->danificaCarro(posAtual + 1); //Danifica o antes
			p->danificaCarro(posAtual - 1); //Danifica o carro a frente
			cout << "ESTA NO MEIO";
			return true;
		}
		else if (p->obtemPosCorrida(c->obtemId()) == 1) {
			p->danificaCarro(posAtual + 1); //Danifica o carro atrás
			cout << "ESTA em primeiro";
			return true;
		}
		else if (p->obtemPosCorrida(c->obtemId()) == p->obtemNumCarrosEmCompeticao()) { // Se estiver em ultimo
			p->danificaCarro(posAtual - 1);
			cout << "ESTA em ultimo";
			return true;
		}
		/*else {
			p->danificaCarro(posAtual);
			cout << "NEM UM NEM OUTRO";
			return true;
		}*/
	}
	else {
		c->acelera();
	}

	return true;
}

Piloto * PilotoSurpresa::dupilica()
{
	return new PilotoSurpresa(*this);
}
