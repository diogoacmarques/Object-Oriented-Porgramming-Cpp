#include "DVG.h"
#include <iostream>
#include <sstream>

using namespace std;

DVG::DVG()
{
}

DVG::~DVG()
{
	//delete [] todosCarros;
	//delete [] todosPilotos;
	todosCarros.clear();
	todosPilotos.clear();
	cout << "Destrutor DVG a não apagar carros e pilotos..." << endl;
}

Piloto * DVG::obtemPiloto(std::string nome)
{
	vector<Piloto*>::iterator it = todosPilotos.begin();

	while (it != todosPilotos.end()) {
		if((*it)->obtemNome() == nome)
			return (*it);
	it++;
	}
	return nullptr;
}

bool DVG::criaPiloto(string tipo, string nome)
{
	Piloto * tmp;
	do {
		tmp = obtemPiloto(nome);
		if (tmp != nullptr) {//existe este nome
			nome = nome + "x";
		}
		else {//nao existe nenhum com este nome
			tmp = new Piloto(nome);
			todosPilotos.push_back(tmp);
			return true;
		}
	} while (1);

	return false;
}

bool DVG::apagaPiloto(std::string nome)
{
	int pos = obtemPosVectorPiloto(nome);
	if (pos != -1) {
		delete todosPilotos.at(pos);//apaga memoria alocada
		todosPilotos.erase(todosPilotos.begin() + pos);//apaga pos do vector
		return true;
	}
	else {
		return false;
	}
	
	return false;
}

int DVG::obtemPosVectorPiloto(std::string nome) const
{
	for (int i = 0; i < todosPilotos.size(); i++)
		if (todosPilotos.at(i)->obtemNome() == nome)
			return i;

	return -1;
}

Carro * DVG::obtemCarro(char letra)
{
	vector<Carro*>::iterator it = todosCarros.begin();

	while (it != todosCarros.end()) {
		if ((*it)->obtemId() == letra)
			return (*it);
		it++;
	}
	return nullptr;
}

bool DVG::criaCarro(int capInicial, int capMax, std::string marca, std::string modelo)
{
	Carro * tmp;
	if (modelo.empty()) {
		tmp = new Carro(capInicial, capMax,marca);
	}
	else {
		tmp = new Carro(capInicial, capMax, marca, modelo);
	}
	
	todosCarros.push_back(tmp);
	return true;
}

bool DVG::apagaCarro(char letra)
{
	int pos = obtemPosVectorCarro(letra);
	if (pos != -1) {
		delete todosCarros.at(pos);//apaga memoria alocada
		todosCarros.erase(todosCarros.begin() + pos);//apaga pos do vector
		return true;
	}
	else {
		return false;
	}
	return false;
}

int DVG::obtemPosVectorCarro(char letra) const
{
	for (int i = 0; i < todosCarros.size(); i++) 
		if (todosCarros.at(i)->obtemId() == letra)
			return i;

	return -1;
}

std::string DVG::obtemTodosCarros()
{
	ostringstream os;
	vector<Carro*>::iterator it = todosCarros.begin();

	while (it != todosCarros.end()) {
		os << "\t" << (*it)->carroToString() << endl;
		it++;
	}
	return os.str();
}

std::string DVG::obtemTodosPilotos()
{
	ostringstream os;
	vector<Piloto*>::iterator it = todosPilotos.begin();

	while (it != todosPilotos.end()) {
		os << "\t" << (*it)->pilotoToString() << endl;
		it++;
	}
	return os.str();
}
