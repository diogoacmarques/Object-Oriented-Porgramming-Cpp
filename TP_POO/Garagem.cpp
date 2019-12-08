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

bool Garagem::recebeCarros(std::vector<Carro*> tmp)
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

Carro * Garagem::obtemCarroDisponivel()
{
	Carro * tmp;
	for (int i = 0; i < carros.size(); i++) {
		if (!carros.at(i)->verificaPista()) {
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

std::string Garagem::listaCarros() const
{
	ostringstream os;
	for (int i = 0; i < carros.size(); i++)
		os << carros.at(i)->obtemCarro() << endl;
	return os.str();
}

//Piloto * Garagem::retira()
//{
//	Piloto * tmp;
//
//	if (!pilotosNaGaragem.empty()) {
//		for (int i = 0; i < pilotosNaGaragem.size(); i++) {
//			tmp = pilotosNaGaragem.at(i);
//			if (tmp->temCarro() && !tmp->temPista()) {
//				cout << "Garagem encontrou o piloto " << tmp->obtemNome() << " para a pista" << endl;
//				return tmp;
//			}
//				
//		}
//	}
//	
//	cout << "Garagem nao tem nenhum piloto para a pista" << endl;
//	return nullptr;
//}
//
//std::string Garagem::obtemCarros() const
//{
//	ostringstream os;
//	if (!carrosNaGaragem.empty()) {
//		//cout << "Autodromo(garagem) carregou os carros:" << endl;
//		for (int i = 0; i < carrosNaGaragem.size(); i++)
//			os << carrosNaGaragem.at(i)->carroToString() << endl;
//	}
//	else
//		return "A garagem nao tem carros";
//
//	return os.str();
//}
//
//std::string Garagem::obtemPilotos() const
//{
//	ostringstream os;
//	if (!pilotosNaGaragem.empty()) {
//		//cout << "Autodromo(garagem) carregou os carros:" << endl;
//		for (int i = 0; i < pilotosNaGaragem.size(); i++)
//			os << pilotosNaGaragem.at(i)->pilotoToString() << endl;
//	}
//	else
//		return "A garagem nao tem carros";
//
//	return os.str();
//}
