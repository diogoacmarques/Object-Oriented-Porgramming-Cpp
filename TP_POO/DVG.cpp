#include "DVG.h"

using namespace std;

DVG::DVG(string n):nome(n)
{
}

DVG::~DVG()
{
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
	Piloto * tmp;
	tmp = obtemPiloto(nome);
	if (tmp != nullptr) {
		delete tmp;
		return true;
	}
	return false;
}
