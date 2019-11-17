#include "Autodromo.h"
#include <iostream>
#include <sstream>

using namespace std;

std::vector<std::string> Autodromo::todosNomesAutodromos;

Autodromo::Autodromo(int n_Max, int comprimento, std::string n):pista(n_Max,comprimento)
{
	for (int i = 0; i < todosNomesAutodromos.size(); i++) {
		if (n == todosNomesAutodromos.at(i)) {
			n = n + "x";
			i = -1;
		}
	}

	todosNomesAutodromos.push_back(n);
	nome = n;
	cout << "\tConstrutor_Autodromo:" << n << "|max=" << n_Max << "(" << comprimento << " metros)\n" << endl;
}

Autodromo::~Autodromo()
{
	cout << "Destrutor_autodromo:'" << nome << "'" << endl;
	for (int i = 0; i < todosNomesAutodromos.size(); i++) {
		if (nome == todosNomesAutodromos.at(i)) {
			todosNomesAutodromos.erase(todosNomesAutodromos.begin() + i);
			break;
		}
	}
}

std::string Autodromo::obtemNome() const
{
	return nome;
}

std::string Autodromo::autodromoToString() const
{
	ostringstream os;
	os << "Autodromo:" << nome << "|max=" << pista.obtemNMax() << "(" << pista.obtemComprimento() << " metros)";
	return os.str();
}

bool Autodromo::carregaCarros(std::vector<Carro*> vectorCarros)
{
	return garagem.recebeCarros(vectorCarros);
}

std::string Autodromo::obtemCarrosGaragem() const
{
	return garagem.obtemCarros();
}
