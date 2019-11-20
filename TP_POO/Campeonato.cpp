#include "Campeonato.h"
#include <iostream>
using namespace std;

Campeonato::Campeonato(std::string n):nome(n), autodromoEmCompeticao(-1)
{
	cout << "Construtor Campeonato '" << nome << "'" << endl;
}

Campeonato::~Campeonato()
{
	cout << "Destrutor campeonato '" << nome << "'" << endl;
}

bool Campeonato::carregaAutodromos(std::vector<Autodromo*> a)
{
	autodromosCampeonato = a;
	return true;
}

bool Campeonato::proximoAutodromo()
{
	if ((autodromoEmCompeticao + 1) == autodromosCampeonato.size()) {
		cout << "ja nao existem mais autodromos para competira = final da comepeitcao" << endl;
		return false;
	}
	else {
		autodromoEmCompeticao++;

	
		cout << "[Campeonato]Autdromo em comepeticao = " << autodromoEmCompeticao + 1 << endl;
		return true;
	}

	return false;
}

Autodromo * Campeonato::obtemAutodromoCompeticao()
{
	if (autodromoEmCompeticao != -1)
		return autodromosCampeonato.at(autodromoEmCompeticao);
	else
		return nullptr;
}

bool Campeonato::verificaraExistenciaCorrida()
{
	if (autodromoEmCompeticao == -1)
		return false;
	else
		return true;
}

bool Campeonato::passaTempo(int segundos)
{
	if (verificaraExistenciaCorrida()) {
		cout << "Campeonato:irei passsar " << segundos << " segundos no campeonato" << endl;
		Autodromo * a = autodromosCampeonato.at(autodromoEmCompeticao);
		a->passaTempo(segundos);
		return true;
	}
	else {
		cout << "Nao existe corrida em curso..." << endl;
		return false;
	}
	
	
}
