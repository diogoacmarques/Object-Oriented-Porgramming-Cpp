#include "Garagem.h"
#include <iostream>
#include <sstream>

using namespace std;


Garagem::Garagem()
{
	cout << "Construtor Garagem" << endl;
}

Garagem::~Garagem()
{
}

bool Garagem::recebeCarros(std::vector<Carro*> tmp)
{
	carrosNaGaragem = tmp;
	tmp.clear();
	
	if (!carrosNaGaragem.empty())
		return true;
	else
		return false;
}

std::string Garagem::obtemCarros() const
{
	ostringstream os;
	if (!carrosNaGaragem.empty()) {
		cout << "Carreguei os seguintes carros:" << endl;
		for (int i = 0; i < carrosNaGaragem.size(); i++)
			os << carrosNaGaragem.at(i)->carroToString() << endl;
	}
	else
		return "A garagem nao tem carros";

	return os.str();
}
