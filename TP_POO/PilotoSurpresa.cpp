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
	//Acelera sempre, mas tem 10% probablidade de se danificar e se isto acontecer danifica o de trás e o da frente(posicoes e nao pistas ao lado)
	srand((int)time(NULL));
	int prob = rand() % 100;
	int posAtual = p->obtemPosCorrida(c->obtemId());
	int carrosNaPista = p->obtemNumCarrosNaPista();

	if (prob < 10) {//faz algo que danifica o automovel
		c->danificaCarro();	
		if (carrosNaPista >= 2) {//verifica que existem mais pilotos na pista

			if (posAtual == 0) {//esta em primeiro
				p->danificaCarro(posAtual + 1);			
			}
			else if (posAtual == (carrosNaPista - 1)) {//se esta em ultimo
				p->danificaCarro(posAtual - 1);
			}
			else {//esta no meio
				p->danificaCarro(posAtual + 1);
				p->danificaCarro(posAtual - 1);
			}
		}
		else {
			//cout << "nao existem 2 carros em competicao" << endl;
			return false;
		}
		
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
