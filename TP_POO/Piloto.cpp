#include "Piloto.h"
#include <iostream>
#include <sstream>

using namespace std;

std::vector<std::string> Piloto::todosNomesPilotos;

Piloto::Piloto(std::string n) :tipo("normal")
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

std::string Piloto::pilotoToString()
{
	ostringstream os;
	os << nome << ":" << endl;
	os << "\t\t-Tipo:" << tipo;
	if(temCarro())
		os << "\n\t\tCarro:" << carro->obtemId();
	return os.str();
}