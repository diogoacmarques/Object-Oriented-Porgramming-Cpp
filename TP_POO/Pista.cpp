#include "Pista.h"
#include "Garagem.h"
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
	Carro * tmp;
	vector<Carro*>::iterator it = carrosNaPista.begin();
	while (it != carrosNaPista.end()) {
		if((*it)->obtemId() == idCarro){
			(*it)->fimCompeticao();
			tmp = *it;
			carrosNaPista.erase(it);
			return tmp;
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

bool Pista::passaTempo(int segundos, Garagem * g)//false = fim da corrida
{
	if (!emCompeticao) {
		cout << "A pista nao se encontra em corrida" << endl;
		return false;
	}

	string lixo;
	if (carrosNaPista.size() == 0) {
		cout << "nao existem equipas em competicao" << endl;
		return false;
	}


	if (segundos == 0) {
		//cout << obtemPista();
		desenhaPista();
		return true;
	}

	Consola::clrscr();

	int verifcaCorrida;
	for (int i = 0; i < segundos; i++) {
		verifcaCorrida = 0;
		for (auto carro : carrosNaPista) {
			if (carro->verificaCompeticao()) {
				if (carro->verificaEmergencia() || carro->obtemBateriaAtual() == 0 || carro->verificaDano()) {//(falta bateria /acidente/sinal emergencia)
					cout << "O carro com o id '" << carro->obtemId() << "' tem o sinal de emergencia ligado, a remover da pista." << endl;	
					g->recebeCarro(removeCarro(carro->obtemId()));//mete na garagem
					continue;
				}

				verifcaCorrida++;
				carro->decisaoPiloto(this);

				//verifica se ganhou
				if (carro->obtemDistanciaPercorrida() >= comprimento) {
					cout << "O carro " << carro->obtemId() << " acabou a corrida" << endl;
					int pos = obtemPosCorrida(carro->obtemId());
					carro->fimCompeticao();//mas mantemna pista
					//adicionar pontos da competicao (to do)-------------------------------------------------------------------------------------------------
					continue;
				}

			}
				
		}

		if (verifcaCorrida>0) {
			ordenaPosicoes();
			desenhaPista();
			//cout << obtemPista();
			cout << "Prima a tecla 'enter'..." << endl;
			getchar();
		}
		else {
			cout << "Ja nao existe equipas a competir(final da corrida)" << endl;
			terminarCorrida();
			return true;
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
		carrosNaPista.at(i)->fimCompeticao();
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
		Consola::gotoxy(10, 15);
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
	//int comprimento = 40;//parametros teste (comprimento da pista)
	//int nMax = 4;//parametros teste (numero maximo de carros na pista)
	
	int numeroDeLinhasPorPista = 4; //(3 de pista + 1 barreira)


	int tam = comprimento;
	int fatorReducao = 1;
	while (tam > Consola::ScreeSizeY) {//reduz o tamanho da pista para caber no ecra
		tam = tam / 2;
		fatorReducao++;
	}

	int linhaInfo = (int)carrosNaPista.size() + 1;
	Consola::gotoxy(0, linhaInfo);
	cout << "Numero de carros da pista: " << nMax << endl;
	cout << "Numero de carros a competir: " << carrosNaPista.size() << endl;
	cout << "Tamanho da pista real: " << comprimento << endl;
	cout << "Tamanho da pista reduzida: " << tam << endl;
	cout << "Fator Reducao: " << fatorReducao << endl;
	linhaInfo += 5;

	for (int y = 0; y < tam; y++) {//pista

		for (int x = 0; x < nMax*numeroDeLinhasPorPista; x++) {
			Consola::setBackgroundColor(Consola::PRETO);
			Consola::gotoxy((Consola::ScreeSizeX / 2) + 20 + x + 1, y + 1);
			cout << " ";
			if (y == tam - 1 || y == 0 ) {//meta/linha partida
				Consola::setBackgroundColor(Consola::BRANCO_CLARO);
				Consola::gotoxy((Consola::ScreeSizeX / 2) + 20 + x + 1, y + 1);
				cout << " ";
			}
		}


		for (int x = 0; x <= nMax * numeroDeLinhasPorPista; x += 4) {//barreira
			Consola::setTextColor(Consola::BRANCO_CLARO);
			Consola::gotoxy((Consola::ScreeSizeX / 2) + 20 + x + 1, y + 1);
			cout << "|";
		}
	}

	Consola::setBackgroundColor(Consola::CINZENTO);
	Consola::setTextColor(Consola::CYAN_CLARO);
	Consola::gotoxy(0, linhaInfo++);
	cout << "fim do desenho da pista" << endl;
	//getchar();
	

	int distancia;
	for (int i = 0; i < carrosNaPista.size(); i++) {//carros
		distancia = carrosNaPista.at(i)->obtemDistanciaPercorrida() / (fatorReducao);
		Consola::gotoxy(0,i);
		Consola::setBackgroundColor(Consola::CINZENTO);
		Consola::setTextColor(Consola::PRETO);
		cout << "Carro " << carrosNaPista.at(i)->obtemId() << " percorreu:" << carrosNaPista.at(i)->obtemDistanciaPercorrida() << "m ou " << distancia << " na pista";

		if (distancia == 0) {//inicio 
			Consola::setBackgroundColor(Consola::BRANCO_CLARO);
			Consola::setTextColor(Consola::PRETO);
		}
		else if (distancia >= tam) {//fim
			Consola::setBackgroundColor(Consola::BRANCO_CLARO);
			Consola::setTextColor(Consola::PRETO);
			distancia = tam - 1;
		}
		else {
			Consola::setBackgroundColor(Consola::PRETO);
			Consola::setTextColor(Consola::BRANCO_CLARO);
		}

		if (carrosNaPista.at(i)->verificaDano()) {
			Consola::setTextColor(Consola::VERMELHO_CLARO);
		}
		else if (carrosNaPista.at(i)->verificaEmergencia()) {
			Consola::setTextColor(Consola::AMARELO_CLARO);
		}
		else if (carrosNaPista.at(i)->obtemBateriaAtual() <= 0) {
			Consola::setTextColor(Consola::AZUL_CLARO);
		}

		Consola::gotoxy((Consola::ScreeSizeX / 2) + 20 + 3 + (i * numeroDeLinhasPorPista), distancia + 1);
		cout << carrosNaPista.at(i)->obtemId();
	}

	//Significado cores
	Consola::setBackgroundColor(Consola::CINZENTO);
	Consola::setTextColor(Consola::CYAN_CLARO);
	Consola::gotoxy(0, linhaInfo++);
	cout << "fim do desenho dos carros" << endl;
	cout << "Cores:" << endl;
	Consola::setTextColor(Consola::AZUL_CLARO);
	cout << "\tSem bateria" << endl;
	Consola::setTextColor(Consola::AMARELO_CLARO);
	cout << "\tSinal Emergencia" << endl;
	Consola::setTextColor(Consola::VERMELHO_CLARO);
	cout << "\tDano Irreparavel" << endl;

	//before exit
	Consola::setTextColor(Consola::CYAN_CLARO);
	linhaInfo += 5;
	Consola::gotoxy(0, linhaInfo);

	return;
}
