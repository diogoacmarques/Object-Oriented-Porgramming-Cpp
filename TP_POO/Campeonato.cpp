#include "Campeonato.h"
#include <iostream>
#include <sstream>
using namespace std;

Campeonato::Campeonato(std::string n):nome(n), autodromoEmCompeticao(0)
{
	cout << "Construtor Campeonato '" << nome << "'" << endl;
}

Campeonato::~Campeonato()
{
	cout << "Destrutor campeonato '" << nome << "'" << endl;
}

std::string Campeonato::obtemPontuacao() const
{
	if (carrosPontuacao.size() <= 0)
		return "Inicia a primeira corrida para verificar os pontos";
	ostringstream os;
	for (auto c : carrosPontuacao)
		os << "Carro[" << c->obtemId() << "]: " << c->obtemPontuacao() << " pontos!" << endl;

	return os.str();
}

bool Campeonato::carregaCarros(std::vector<Carro*> v)
{
	carrosPontuacao = v;
	return true;
}

bool Campeonato::carregaAutodromos(std::vector<Autodromo*> a)
{
	autodromosCampeonato = a;
	return true;
}

bool Campeonato::proximoAutodromo()
{
	Autodromo * autodromo = obtemAutodromoCompeticao();
	autodromo->terminarCorrida();
	if ((autodromoEmCompeticao + 1) == autodromosCampeonato.size()) {
		Consola::clrscr();
		
		cout << "ja nao existem mais autodromos para competir = final da competicao" << endl;
		return false;
	}
	else {
		autodromoEmCompeticao++;
		cout << "[Campeonato]Autodromo em competicao = " << autodromoEmCompeticao + 1 << endl;
		return true;
	}

	return false;
}

bool Campeonato::termina()
{
	autodromoEmCompeticao = -1;



	return true;
}

Autodromo * Campeonato::obtemAutodromoCompeticao() const
{
	if (autodromoEmCompeticao != -1)
		return autodromosCampeonato.at(autodromoEmCompeticao);
	else
		return nullptr;
}

int Campeonato::obtemNumAutodromoCompeticao() const
{
	return autodromoEmCompeticao;
}

std::vector<Carro*> Campeonato::obtemCarrosAutodromoAnterior()
{
	if (autodromoEmCompeticao > 0) {
		return autodromosCampeonato.at(autodromoEmCompeticao - 1)->retiraCarros();	
	}
	else {
		cout << "Nao existe nenhum autodromo anterior para retirar os carros" << endl;
	}
	return std::vector<Carro*>();
}

bool Campeonato::verificaraExistenciaCorrida() const
{
	if (autodromoEmCompeticao == -1)
		return false;
	else
		return true;
}

bool Campeonato::passaTempo(int segundos)
{
	if (verificaraExistenciaCorrida()) {
		//cout << "Campeonato:irei passsar " << segundos << " segundos no campeonato" << endl;
		Autodromo * a = autodromosCampeonato.at(autodromoEmCompeticao);	
		return a->passaTempo(segundos);
	}
	else {
		cout << "Nao existe corrida em curso..." << endl;
		return false;
	}
	
}
