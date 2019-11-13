#include "Piloto.h"
#include <iostream>
#include <sstream>

using namespace std;

Piloto::Piloto(std::string n):nome(n),tipo("normal")
{
	cout << "\tConstrutor_Piloto:(" << tipo << "," << nome << ")\n" << endl;
}

Piloto::~Piloto()
{
	cout << "Destrutor do piloto..." << endl;
}
std::string Piloto::obtemNome() const
{
	return nome;
}

std::string Piloto::pilotoToString()
{
	ostringstream os;
	os << "Piloto:(" << tipo << "," << nome << ")";
	return os.str();
}