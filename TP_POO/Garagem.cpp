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
	cout << "Destrutor da garagem" << endl;
}

bool Garagem::recebeTodosCarros(std::vector<Carro*> tmp)
{
	carros = tmp;
	for (int i = 0; i < carros.size(); i++) {//reset
		carros.at(i)->entraNaGaragem();
	}
		

	if (!carros.empty()) {
		cout << "A garagem carregou com sucesso " << carros.size() << " equipas." << endl;
		return true;
	}	
	else {
		cout << "Garagem:Nao recebi equipas..." << endl;
		return false;
	}
	
}

bool Garagem::recebeCarro(Carro * c)
{
	carros.push_back(c);
	c->entraNaGaragem();
	return true;
}

Carro * Garagem::obtemCarroDisponivel()
{
	Carro * tmp;
	for (int i = 0; i < carros.size(); i++) {
		if (carros.at(i)->verificaAptidao()) {
			carros.at(i)->entraPista();
			tmp = carros.at(i);
			carros.erase(carros.begin() + i);
			return tmp;
		}
	}

	cout << "Garagem nao tem mais equipas disponiveis" << endl;	
	return nullptr;
}

bool Garagem::carregaTodasBaterias()
{
	for (int i = 0; i < carros.size(); i++) {
		carros.at(i)->carregamentoTotal();
	}
	//cout << "Carreguei a bateria de todos os carros ao maximo" << endl;
	return true;
}

int Garagem::obtemNumCarros() const
{
	return (int)carros.size();
}

std::vector<Carro*> Garagem::retiraTodosCarros()
{
	vector<Carro*> tmp = carros;
	carros.clear();
	return tmp;
}

std::string Garagem::listaCarros() const
{
	ostringstream os;
	for (int i = 0; i < carros.size(); i++)
		os << carros.at(i)->carroToString() << endl;
	return os.str();
}
