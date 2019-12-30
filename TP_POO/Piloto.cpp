#include "Piloto.h"
#include "Carro.h"
#include <iostream>
#include <sstream>

using namespace std;

std::vector<std::string> Piloto::todosNomesPilotos;

Piloto::Piloto(std::string n) :idCarro('-'),pontuacao(0)
{

	for (int i = 0; i < todosNomesPilotos.size(); i++) {
		if (n == todosNomesPilotos.at(i)) {
			n = n + "x";
			i = -1;
		}
	}
	
	todosNomesPilotos.push_back(n);
	nome = n;
	cout << "\tConstrutor_Piloto:(" << "," << nome << ")\n" << endl;
}

Piloto::~Piloto()
{
	cout << "Destrutor_Piloto:'" << nome << "'" << endl;
	for (int i = 0; i < todosNomesPilotos.size(); i++) {
		if (nome == todosNomesPilotos.at(i)) {
			todosNomesPilotos.erase(todosNomesPilotos.begin() + i);
			break;
		}
	}
}

std::string Piloto::obtemNome() const
{
	return nome;
}

void Piloto::adicionaPontuacao(int pontos)
{
	pontuacao += pontos;
	return;
}

void Piloto::resetPontuacao()
{
	pontuacao = 0;
	return;
}

bool Piloto::stop(Carro * c)
{
	if (c == nullptr)
		return false;

	c->ativaSinalEmergencia();
	cout << nome << " forcado a parar" << endl;
	return true;
}


char Piloto::obtemIdCarro() const
{
	return idCarro;
}

bool Piloto::verificaCarro() const
{
	if (idCarro == '-')
		return false;
	else
		return true;
}

bool Piloto::adicionaCarro(char id)
{
	if (verificaCarro())
		return false;

	idCarro = id;
	return true;
}

bool Piloto::removeCarro()
{
	idCarro = '-';
	return true;
}

std::string Piloto::pilotoToString() const
{
	ostringstream os;
	os << "Piloto:" << nome << "(" << obtemTipo() << ")";
	if (verificaCarro())
		os << ", tem carro '" << idCarro;
	return os.str();
}