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

Piloto * Garagem::saiParaPista()
{
	Piloto * tmp;

	if (!pilotosNaGaragem.empty()) {

		/*for (int i = 0; i < carrosNaGaragem.size(); i++) {
			tmp = carrosNaGaragem.at(i);
			if (tmp->temPiloto())
				return tmp;
		}*/
	}
	
	return nullptr;
}

std::string Garagem::obtemCarros() const
{
	ostringstream os;
	if (!carrosNaGaragem.empty()) {
		//cout << "Autodromo(garagem) carregou os carros:" << endl;
		for (int i = 0; i < carrosNaGaragem.size(); i++)
			os << carrosNaGaragem.at(i)->carroToString() << endl;
	}
	else
		return "A garagem nao tem carros";

	return os.str();
}
