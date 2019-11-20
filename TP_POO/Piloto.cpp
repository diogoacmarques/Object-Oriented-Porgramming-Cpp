#include "Piloto.h"
#include <iostream>
#include <sstream>

using namespace std;

std::vector<std::string> Piloto::todosNomesPilotos;

Piloto::Piloto(std::string n) :tipo("normal"), naPista(false)
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

bool Piloto::temCarro() const
{
	if (carro ==  nullptr)
		return false;
	else
		return true;
}

bool Piloto::entraNoCarro(Carro * c)
{

	if (!temCarro()) {
		carro = c;
		return true;
	}else
		return false;
}

bool Piloto::removeCarro()
{
	carro =  nullptr;
	return true;
}

char Piloto::obtemIdCarro() const
{
	if (carro != nullptr)
		return carro->obtemId();
	else
		return '-';
}

bool Piloto::passaSegundo()
{
	if (carro->obtemVelocidade() == 0) {
		carro->acelera(1);
		cout << "Piloto '" << nome << "' arrancou da linha com o carro (" << carro->obtemId() << ")" << endl;
	}
	else {
		carro->passaSegundo();
		cout << "Piloto '" << nome << "' passaSegundo com o carro (" << carro->obtemId() << ") a " << carro->obtemVelocidade() << " metros por segundo" << endl;
	}
	return true;
}

int Piloto::obtemDistanciaPercorrida() const
{
	if (temCarro())
		return carro->obtemDistanciaPercorrida();
	else
		return -1;
}

int Piloto::obtemVelocidade() const
{
	if (temCarro())
		return carro->obtemVelocidade();
	else
		return -1;
}

std::string Piloto::obtemCarro() const
{
	if (temCarro())
		return carro->carroToString();
	else
		return "Piloto sem carro";
}

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
	carro->para();
}

std::string Piloto::pilotoToString()
{
	ostringstream os;
	os << "Piloto:" << nome << "(" << tipo << ")";
	if (temCarro())
		os << ", tem carro '" << carro->obtemId();
	if (temPista())
		os << "' e encontra - se na pista";
	return os.str();
}