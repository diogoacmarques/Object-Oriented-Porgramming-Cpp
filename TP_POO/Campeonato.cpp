#include "Campeonato.h"
#include <iostream>
using namespace std;

Campeonato::Campeonato(std::vector<Carro*> c, std::vector<Piloto*> p, std::vector<Autodromo*> a):campCarros(c), campPilotos(p), campAutodromos(a)
{
	cout << "construtor campeonato!" << endl;
}

Campeonato::~Campeonato()
{
	cout << "Destrutor campeonato!" << endl;
}
