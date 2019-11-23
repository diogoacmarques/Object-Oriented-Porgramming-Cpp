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

bool Garagem::recebeEquipa(std::vector<Equipa*> tmp)
{
	equipas = tmp;
	if (!equipas.empty()) {
		cout << "A garagem carregou com sucesso " << equipas.size() << " equipas." << endl;
		return true;
	}	
	else {
		cout << "Garagem:Nao recebi equipas..." << endl;
		return false;
	}
	
}

Equipa * Garagem::obtemEquipaDisponivel()
{
	
	for (int i = 0; i < equipas.size(); i++) {
		if (!equipas.at(i)->verificaPista()) {
			equipas.at(i)->entraNaPista();
			return equipas.at(i);
		}	
	}		

	cout << "Garagem nao tem mais equipas disponiveis" << endl;	
	return nullptr;
}

bool Garagem::carregaTodasBaterias()
{
	for (int i = 0; i < equipas.size(); i++) {
		equipas.at(i)->carregaBateriaTotal();		
	}
	cout << "Carreguei a bateria de todos os carros ao maximo" << endl;
	return true;
}

std::string Garagem::listaCarros() const
{
	ostringstream os;
	for (int i = 0; i < equipas.size(); i++)
		os << equipas.at(i)->obtemId() << endl;
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
