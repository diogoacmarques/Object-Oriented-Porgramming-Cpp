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
	cout << "Autdodromo '" << obtemNome() << "' vai tentar carregar os carros para a garagem" << endl;
	return garagem.recebeCarros(vectorCarros);
}

std::string Autodromo::obtemCarrosGaragem() const
{
	ostringstream os;
	os << "O Autodromo '" << obtemNome() << "' tem os seguintes carros:" << endl;
	os << garagem.obtemCarros();
	return os.str();
}

bool Autodromo::carregaPilotos(std::vector<Piloto*> vectorPilotos)
{
	garagem.recebePilotos(vectorPilotos);
	return false;
}

bool Autodromo::inserePilotosPista()
{
	Piloto * tmp;
	bool levaMais = true;//pista
	int pilotosInseridos = 0;
	while (levaMais) {//se houver espaço na pista
		tmp = garagem.retira();
		if (tmp == nullptr) {//se ja nao ha piloto
			//cout << "a garagem ja nao encontra mais pilotos disponiveis" << endl;
			break;
		}
		
		levaMais = pista.insere(tmp);
		tmp->entraPista();
		//cout << "inseri piloto e a pista =" << levaMais << endl;
		pilotosInseridos++;
		cout << "Autodromo:Done" << endl;
	}


	cout << "Final:Inseri " << pilotosInseridos << " pilotos na pista" << endl;
	return pilotosInseridos;
}

void Autodromo::iniciaPista()
{
	pista.iniciaCorrida();
}

void Autodromo::terminarCorrida()
{
	pista.terminarCorrida();
}

bool Autodromo::passaTempo(int segundos)
{
	return pista.passaTempo(segundos);
}
