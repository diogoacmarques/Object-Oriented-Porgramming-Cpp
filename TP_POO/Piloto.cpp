#include "Piloto.h"
#include <iostream>
#include <sstream>

using namespace std;

std::vector<std::string> Piloto::todosNomesPilotos;

Piloto::Piloto(std::string n) :tipo("normal"), idCarro('-')
{

	for (int i = 0; i < todosNomesPilotos.size(); i++) {
		if (n == todosNomesPilotos.at(i)) {
			n = n + "x";
			i = -1;
		}
	}
	
	todosNomesPilotos.push_back(n);
	nome = n;
	cout << "\tConstrutor_Piloto:(" << tipo << "," << nome << ")\n" << endl;
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
std::string Piloto::obtemTipo() const
{
	return tipo;
}

//bool Piloto::temEquipa() const
//{
//	if (idEquipa == -1 && carro == nullptr)
//		return false;
//	else
//		return true;
//}
//
//bool Piloto::adicionaEquipa(int id, Carro * c)
//{
//	carro = c;
//	idEquipa = id;
//	return true;
//}
//
//bool Piloto::removeEquipa()
//{
//	idEquipa = -1;
//	carro = nullptr;
//	return true;
//}

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
	os << "Piloto:" << nome << "(" << tipo << ")";
	//if (temCarro())
		//os << ", tem carro '" << carro->obtemId();
	/*if (temEquipa())
		os << "' e encontra - se na equipa" << idEquipa;*/
	return os.str();
}