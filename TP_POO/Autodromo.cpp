#include "Autodromo.h"
#include <iostream>
#include <sstream>

using namespace std;

Autodromo::Autodromo(int n_Max, int comprimento, std::string n):pista(n_Max,comprimento),nome(n)
{
	cout << "\tConstrutor_Autodromo:" << n << "|max=" << n_Max << "(" << comprimento << " metros)\n" << endl;
}

Autodromo::~Autodromo()
{
	cout << "Destrutor autodromo '" << nome << "'" << endl;
}

std::string Autodromo::obtemNome() const
{
	return nome;
}

std::string Autodromo::autodromoToString() const
{
	ostringstream os;
	os << "Autodromo:" << nome << "|max=" << pista.obtemNMax() << "(" << pista.obtemComprimento() << " metros)";
	return os.str();
}
