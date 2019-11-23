#include "Piloto.h"
#include <iostream>
#include <sstream>

using namespace std;

std::vector<std::string> Piloto::todosNomesPilotos;

Piloto::Piloto(std::string n) :tipo("normal"), naPista(false),idEquipa(-1)
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
//
//bool Piloto::temCarro() const
//{
//	if (carro ==  nullptr)
//		return false;
//	else
//		return true;
//}
//
//bool Piloto::entraNoCarro(Carro * c)
//{
//
//	if (!temCarro()) {
//		carro = c;
//		return true;
//	}else
//		return false;
//}
//
//bool Piloto::removeCarro()
//{
//	carro =  nullptr;
//	return true;
//}
//
//char Piloto::obtemIdCarro() const
//{
//	if (carro != nullptr)
//		return carro->obtemId();
//	else
//		return '-';
//}

bool Piloto::temEquipa() const
{
	if (idEquipa == -1)
		return false;
	else
		return true;
}

bool Piloto::adicionaEquipa(int id)
{
	idEquipa = id;
	return true;
}

bool Piloto::removeEquipa()
{
	idEquipa = -1;
	return true;
}

//std::string Piloto::obtemCarro() const
//{
//	if (temCarro())
//		return carro->carroToString();
//	else
//		return "Piloto sem carro";
//}

bool Piloto::temPista() const
{ 
	cout << "Piloto " << nome << " a verificar se tem pista" << endl;
	 return naPista;
}

void Piloto::entraPista()
{ 
	cout << "Piloto " << nome << " a entrar na pista" << endl;
	naPista = true;
}

void Piloto::saiPista()
{
	naPista = false;
}

std::string Piloto::pilotoToString()
{
	ostringstream os;
	os << "Piloto:" << nome << "(" << tipo << ")";
	//if (temCarro())
		//os << ", tem carro '" << carro->obtemId();
	if (temPista())
		os << "' e encontra - se na pista";
	return os.str();
}