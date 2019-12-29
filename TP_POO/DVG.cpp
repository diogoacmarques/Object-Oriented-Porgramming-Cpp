#include "DVG.h"
#include "CrazyDriver.h"
#include "PilotoRapido.h"
#include "PilotoSurpresa.h"
#include <iostream>
#include <sstream>

using namespace std;

DVG::DVG(std::string n):nome(n)
{
}

DVG::DVG(const DVG & original)
{
	*this = original;
}

DVG::~DVG()
{
	cout << "Destrutor DVG" << endl;
	for (int i = 0; i < todosCarros.size(); i++)
		delete todosCarros.at(i);
	for (int i = 0; i < todosPilotos.size(); i++)
		delete todosPilotos.at(i);
}

DVG & DVG::operator=(const DVG & original)
{
	if (this == &original)
		return *this;

	//limpa
	for (Piloto * p : original.todosPilotos)
		delete p;
	todosPilotos.clear();
	for (Carro * c : original.todosCarros)
		delete c;
	todosCarros.clear();

	//adiciona
	for (int i = 0; i < original.todosPilotos.size(); i++)
		todosPilotos.push_back(original.todosPilotos.at(i)->dupilica());
	
	for (int i = 0; i < original.todosCarros.size(); i++)
		todosCarros.push_back(original.todosCarros.at(i));//confirmar isto

	nome = original.nome;


	return *this;
}

Piloto * DVG::obtemPiloto(std::string nome) const
{
	vector<Piloto*>::const_iterator it = todosPilotos.begin();

	while (it != todosPilotos.end()) {
		if((*it)->obtemNome() == nome)
			return (*it);
	it++;
	}
	return nullptr;
}

std::vector<Piloto*> DVG::obtemVectorPilotos() const
{
	return todosPilotos;
}

bool DVG::criaPiloto(string tipo, string nome)
{
	Piloto * tmp;
	if (tipo == "crazy")
		tmp = new CrazyDriver(nome);
	else if (tipo == "rapido")
		tmp = new PilotoRapido(nome);
	else if (tipo == "surpresa")
		tmp = new PilotoSurpresa(nome);
	else {
		cout << "erro" << endl;
		return false;
	}
		

	todosPilotos.push_back(tmp);
	return true;
}

bool DVG::apagaPiloto(std::string nome)
{
	int pos = obtemPosVectorPiloto(nome);

	if (todosPilotos.at(pos)->verificaCarro()) {
		cout << "Este piloto tem carro (sair do carro)" << endl;
		return false;
	}

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

Carro * DVG::obtemCarro(char letra) const
{
	vector<Carro*>::const_iterator it = todosCarros.begin();

	while (it != todosCarros.end()) {
		if ((*it)->obtemId() == letra)
			return (*it);
		it++;
	}
	return nullptr;
}

vector<Carro*> DVG::obtemVectorCarros()
{
	vector<Carro *> carros = todosCarros;
	todosCarros.clear();
	return carros;
}

bool DVG::criaCarro(int velMax,int capInicial, int capMax, std::string marca, std::string modelo)
{
	Carro * tmp;
	if (modelo.empty()) {
		tmp = new Carro(velMax, capInicial, capMax,marca);
	}
	else {
		tmp = new Carro(velMax,capInicial, capMax, marca, modelo);
	}
	
	todosCarros.push_back(tmp);
	return true;
}

bool DVG::apagaCarro(char letra)
{
	int pos = obtemPosVectorCarro(letra);

	if (todosCarros.at(pos)->verificaPiloto()) {
		cout << "Este carro tem piloto (sair do carro)" << endl;
		return false;
	}

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

bool DVG::destroiCarro(char idCarro)
{
	Carro * c = obtemCarro(idCarro);
	if(c == nullptr)
		return false;

	if (c->verificaPiloto()) {//tem piloto
		Piloto * p = obtemPiloto(c->obtemNomePiloto());
		if (p == nullptr)
			return false;

		p->removeCarro();	
	}

	delete c;

	return true;
}

bool DVG::associaCarroPiloto(char idCarro, std::string nomePiloto)
{
	Carro * carroP = obtemCarro(idCarro);
	Piloto * pilotoP = obtemPiloto(nomePiloto);

	if (carroP != nullptr && pilotoP != nullptr) {//se existe
		//cout << "Encontrei o carro e o piloto!" << endl;
		if (!carroP->verificaPiloto() && !pilotoP->verificaCarro()) {//se nao tem piloto/carro
			//cout << "Estao ambos livres" << endl;
			if (carroP->adicionaPiloto(pilotoP) && pilotoP->adicionaCarro(idCarro)) {
				cout << "Sucesso a associar carro/piloto" << endl;
				return true;
			}
			else {
				cout << "Erro a associar carro/piloto!" << endl;
				return false;
			}
				
		}
		else {
			//cout << "Carro ou piloto esta ocupado!" << endl;
			return false;
		}
		
	}
	else {
		//cout << "Não encontrei piloto  ou carro!" << endl;
		return false;
	}
}

bool DVG::removePilotoCarro(char idCarro)
{
	Carro * carroP = obtemCarro(idCarro);
	Piloto * pilotoP = obtemPiloto(carroP->obtemNomePiloto());

	if (carroP != nullptr && pilotoP != nullptr) {//se existe
		//cout << "Encontrei o carro e o piloto!" << endl;
		if (carroP->verificaPiloto() && pilotoP->verificaCarro()) {//se nao tem piloto/carro
			//cout << "Ambos estao ocupados" << endl;
			if (carroP->removePiloto() && pilotoP->removeCarro()) {
				cout << "Sucesso a remover carro/piloto" << endl;
				return true;
			}
			else {
				cout << "Erro a associar carro/piloto!" << endl;
				return false;
			}
		}
		else {
			//cout << "Carro ou piloto esta ocupado!" << endl;
			return false;
		}

		return false;
	}
	return false;
}

std::string DVG::obtemTodosCarros() const
{
	if (todosCarros.size() == 0)
		return "";

	ostringstream os;
	vector<Carro*>::const_iterator it = todosCarros.begin();

	while (it != todosCarros.end()) {
		os << "\t" << (*it)->carroToString() << endl;
		it++;
	}
	return os.str();
}

std::string DVG::obtemTodosPilotos() const
{
	if (todosPilotos.size() == 0)
		return "";

	ostringstream os;
	vector<Piloto*>::const_iterator it = todosPilotos.begin();

	while (it != todosPilotos.end()) {
		os << "\t" << (*it)->pilotoToString() << endl;
		it++;
	}
	return os.str();
}

std::string DVG::obtemNome() const
{
	return nome;
}
