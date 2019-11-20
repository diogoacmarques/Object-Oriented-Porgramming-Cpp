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
	
	if (!carrosNaGaragem.empty()) {
		cout << "A garagem carregou com sucesso " << carrosNaGaragem.size() << " carros." << endl;
		return true;
	}
		
	else {
		return false;
		cout << "A garagem nao conseguiu armazenar os carros" << endl;
	}
		
}

bool Garagem::recebePilotos(std::vector<Piloto*> tmp)
{
	pilotosNaGaragem = tmp;
	if (!pilotosNaGaragem.empty()) {
		cout << "A garagem carregou com sucesso " << pilotosNaGaragem.size() << " pilotos." << endl;
		return true;
	}	
	else {
		cout << "Garagem:Nao recebi pilotos..." << endl;
		return false;
	}
	
}

Piloto * Garagem::retira()
{
	Piloto * tmp;

	if (!pilotosNaGaragem.empty()) {
		for (int i = 0; i < pilotosNaGaragem.size(); i++) {
			tmp = pilotosNaGaragem.at(i);
			if (tmp->temCarro() && !tmp->temPista()) {
				cout << "Garagem encontrou o piloto " << tmp->obtemNome() << " para a pista" << endl;
				return tmp;
			}
				
		}
	}
	
	cout << "Garagem nao tem nenhum piloto para a pista" << endl;
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

std::string Garagem::obtemPilotos() const
{
	ostringstream os;
	if (!pilotosNaGaragem.empty()) {
		//cout << "Autodromo(garagem) carregou os carros:" << endl;
		for (int i = 0; i < pilotosNaGaragem.size(); i++)
			os << pilotosNaGaragem.at(i)->pilotoToString() << endl;
	}
	else
		return "A garagem nao tem carros";

	return os.str();
}
