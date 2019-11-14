#include "Piloto.h"
#include <iostream>
#include <sstream>

using namespace std;

Piloto::Piloto(std::string n):nome(n),tipo("normal"), idCarro('-')
{
	cout << "\tConstrutor_Piloto:(" << tipo << "," << nome << ")\n" << endl;
}

Piloto::~Piloto()
{
	cout << "Destrutor_Piloto:'" << nome << "'" << endl;
}
std::string Piloto::obtemNome() const
{
	return nome;
}

bool Piloto::temCarro() const
{
	if (idCarro == '-')
		return false;
	else
		return true;
}

bool Piloto::entraNoCarro(char id)
{
	if (!temCarro()) {
		idCarro = id;
		return true;
	}else
		return false;
}

bool Piloto::removeCarro()
{
	idCarro = '-';
	return true;
}

char Piloto::obtemIdCarro() const
{
	return idCarro;
}

std::string Piloto::pilotoToString()
{
	ostringstream os;
	os << nome << ":" << endl;
	os << "\t\t-Tipo:" << tipo;
	if(temCarro())
		os << "\n\t\tCarro:" << idCarro;
	return os.str();
}