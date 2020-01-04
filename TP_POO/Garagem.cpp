#include "Garagem.h"
#include <iostream>
#include <sstream>
#include <vector>

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
		cout << "A garagem carregou com sucesso " << carros.size() << " carros." << endl;
		return true;
	}	
	else {
		cout << "Garagem:Nao recebi carros..." << endl;
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
	Carro * tmp = nullptr;
	vector<Carro*>::iterator it;
	for (int i = 0; i < carros.size(); i++) {
		if (carros.at(i)->verificaAptidao() && carros.at(i)->verificaPiloto()) {
			if (tmp == nullptr || carros.at(i)->obtemPontuacao() > tmp->obtemPontuacao()) {
				tmp = carros.at(i);
				it = carros.begin() + i;
			}			
		}
	}

	if (tmp != nullptr) {
		carros.erase(it);
		return tmp;
	}
	

	cout << "Garagem nao tem mais carros disponiveis" << endl;	
	return nullptr;
}

Carro * Garagem::obtemCarro(char idCarro) const
{
	for (auto c : carros)
		if (c->obtemId() == idCarro)
			return c;
	return nullptr;
	
}

bool Garagem::destroiCarro(char idCarro)
{
	Carro * c;
	std::vector<Carro*>::iterator it = carros.begin();
	while (it != carros.end()) {
		if ((*it)->obtemId() == idCarro) {
			c = (*it);
			carros.erase(it);
			delete c;
			return true;
		}
	}
	return false;
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
