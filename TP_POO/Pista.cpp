#include "Pista.h"
#include <iostream>
#include <sstream>

using namespace std;

Pista::Pista(int nM, int comp) :comprimento(comp), nMax(nM), emCompeticao(false)
{
	cout << "Construtor Pista" << endl;
}

Pista::~Pista()
{
	cout << "Destrutor da pista" << endl;
}

bool Pista::insereCarro(Carro * c)
{
	if (emCompeticao) {
		cout << "A corrida ja comecou" << endl;
		return false;
	}

	if (carrosNaPista.size() + 1 >= nMax) {
		carrosNaPista.push_back(c);
		cout << "A pista(" << nMax << ") ja nao aguenta com mais carros(" << carrosNaPista.size() << ")" << endl;
		return false;
	}
	else {
		carrosNaPista.push_back(c);
		cout << "A Pista inseriu o carro " << c->obtemId() << endl;
		return true;
	}

}

Carro * Pista::removeCarro(char idCarro)
{
	vector<Carro*>::iterator it = carrosNaPista.begin();
	while (it != carrosNaPista.end()) {
		if((*it)->obtemId() == idCarro){
			(*it)->saiPista();

		}

		it++;
	}
	return nullptr;
}

std::vector<Carro*> Pista::removeTodosCarros()
{
	vector<Carro*> tmp = carrosNaPista;
	carrosNaPista.clear();
	return tmp;
}

int Pista::obtemComprimento() const
{
	return comprimento;
}

int Pista::obtemNMax() const
{
	return nMax;
}

bool Pista::passaTempo(int segundos)
{
	if (!emCompeticao) {
		cout << "A pista nao se encontra em corrida" << endl;
		return false;
	}

	string lixo;
	bool check = true;
	if (carrosNaPista.size() == 0) {
		cout << "nao existem equipas em competicao" << endl;
		return true;
	}


	if (segundos == 0) {
		cout << obtemPista();
		return true;
	}


	int verifcaCorrida;
	for (int i = 0; i < segundos; i++) {
		verifcaCorrida = 0;
		for (int j = 0; j < carrosNaPista.size(); j++) {
		
			if (carrosNaPista.at(j)->verificaPista()) {

				if (carrosNaPista.at(j)->verificaEmergencia()) {//se tiver sinal de emergencia ligado
					cout << "O carro com o id '" << carrosNaPista.at(j)->obtemId() << "' tem o sinal de emergencia ligado, a remover da pista." << endl;
					removeCarro(carrosNaPista.at(j)->obtemId());
				}

				verifcaCorrida++;
				check = carrosNaPista.at(j)->decisaoPiloto(this);

				//verifica se ganhou
				if (carrosNaPista.at(j)->obtemDistanciaPercorrida() >= comprimento) {
					cout << "O carro " << carrosNaPista.at(j)->obtemId() << " acabou a corrida" << endl;
					int pos = obtemPosCorrida(carrosNaPista.at(j)->obtemId());
					if (pos == 0) {
						carrosNaPista.at(j)->acabaCorrida(10);
					}
					else if (pos == 1) {
						carrosNaPista.at(j)->acabaCorrida(5);
					}
					else if (pos == 2) {
						carrosNaPista.at(j)->acabaCorrida(2);
					}
					else {
						carrosNaPista.at(j)->acabaCorrida(0);
					}
					
					continue;
				}

				if (!check) {//se nao consegue andar mais(falta bateria /acidente/...)
					cout << "O carro " << carrosNaPista.at(j)->obtemId() << " nao pode andar mais" << endl;
					carrosNaPista.at(j)->acabaCorrida(0);
					check = true;//reset
					continue;
				}

			}
				
		}

		if (verifcaCorrida>0) {
			ordenaPosicoes();
			cout << obtemPista();
			cout << "Esta(o) " << verifcaCorrida << " carro(s) a competir. Prima a tecla 'enter'..." << endl;
			getchar();
		}
		else {
			cout << "Ja nao existe equipas a competir(final da corrida)" << endl;
			terminarCorrida();
			return false;
		}
			
		tempoCorrida++;
	}

	return true;
}

int Pista::obtemTempoCorrida() const
{
	return tempoCorrida;
}

int Pista::obtemCarrosNaPista() const
{
	return (int)carrosNaPista.size();
}

int Pista::obtemPosCorrida(char idCarro)
{
	for (int i = 0; i < carrosNaPista.size(); i++)
		if (carrosNaPista.at(i)->obtemId() == idCarro)
			return i;

	return -1;
}

int Pista::obtemNumCarrosEmCompeticao() const
{
	return (int)carrosNaPista.size();
}

bool Pista::danificaCarro(int pos)
{
	carrosNaPista.at(pos)->danificaCarro();
	return true;
}

bool Pista::iniciaCorrida()
{
	if(carrosNaPista.size() < 2){
		cout << "Nao existem carros suficientes para iniciar a corrida" << endl;
		return false;
	}
	tempoCorrida = 0;
	emCompeticao = true;
	return true;
}

bool Pista::terminarCorrida()
{
	for (int i = 0; i < carrosNaPista.size(); i++)
		carrosNaPista.at(i)->saiPista();
	//Permite terminar a corrida. Os carros são removidos da pista e vão para a garagem, e os pilotosaem dos veículos.
	emCompeticao = false;
	return false;
}

bool Pista::obtemEstado() const
{
	return emCompeticao;
}

void Pista::ordenaPosicoes()
{
	//cout << "A ordenar...";
	bool checkOrdenacao;
	Carro * tmp;
	do {
		checkOrdenacao = false;
		for (int i = 0; i < carrosNaPista.size()-1; i++) {
			if (carrosNaPista.at(i)->obtemDistanciaPercorrida() < carrosNaPista.at(i + 1)->obtemDistanciaPercorrida()) {
				checkOrdenacao = true;
				tmp = carrosNaPista.at(i);
				carrosNaPista.at(i) = carrosNaPista.at(i + 1);
				carrosNaPista.at(i + 1) = tmp;
			}
		}

	} while (checkOrdenacao);
	//cout << " Done!" << endl;
	return;
}

std::string Pista::obtemPista() const
{
	ostringstream os;
	if (obtemEstado()) {//se tem corrida
		os << "Pista:" << comprimento << " metros, com max de " << nMax << " carros" << endl;
		for (int i = 0; i < carrosNaPista.size(); i++){
			os << carrosNaPista.at(i)->infoCompeticao();
			if (carrosNaPista.at(i)->obtemDistanciaPercorrida() >= comprimento)
				os << "(Fim!)";
			os << endl;
		}

	}
	else {
		os << "A corrida ainda nao foi iniciada" << endl;
	}

	/*
	 indica se ela já foi iniciada ou não, e, em caso afirmativo, detalhando a
	classificação atual. Um exemplo de classificação pode ser:
	Informação sobre a corrida no autódromo Silverstone(5000 m) :
	1. B Ferrari / Vettel(rápido) - 5mAh, 290mAh - 2410m – 55m / s
	2. D Mercedes / Hamilton(crazy) - 5mAh, 350mAh - 2300m – 50m / s*/
	return os.str();
}

void Pista::desenhaPista() const
{
	int tam = comprimento;
	while (tam > Consola::ScreeSizeY) {
		tam = tam / 2;
	}

	Consola::gotoxy(15, 0);
	cout << "Tamanho da pista:" << comprimento
		<< " | Tam=" << tam << ",nMax=" << nMax;

	Consola::setBackgroundColor(Consola::COR_DE_ROSA);

	for (int i = 0; i < tam; i++) {

		for (int j = 0; j < nMax; j++) {
			Consola::gotoxy((Consola::ScreeSizeX / 2) + 20 + j + 1, i + 1);
			cout << " ";
		}

	}

	Consola::setBackgroundColor(Consola::CINZENTO);
	cout << endl;
	return;
}
