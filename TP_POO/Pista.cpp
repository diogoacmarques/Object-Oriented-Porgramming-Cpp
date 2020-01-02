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
	for (auto c : carrosNaPista)
		c->danificaCarro();
}

bool Pista::insereCarro(Carro * c)
{
	if (emCompeticao) {
		cout << "A corrida ja comecou" << endl;
		return false;
	}

	
	if (carrosNaPista.size() + 1 >= nMax) {
		carrosNaPista.push_back(c);
		c->iniciaCompeticao((int)carrosNaPista.size());
		cout << "A pista(" << nMax << ") ja nao aguenta com mais carros(" << carrosNaPista.size() << ")" << endl;
		return false;
	}
	else {
		carrosNaPista.push_back(c);
		c->iniciaCompeticao((int)carrosNaPista.size());
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
		Consola::gotoxy(0, 0);
		cout << "A pista nao se encontra em corrida" << endl;
		return true;
	}

	string lixo;
	if (carrosNaPista.size() == 0) {
		Consola::gotoxy(0, 0);
		cout << "nao existem carros em competicao" << endl;
		return true;
	}
	Consola::clrscr();

	if (segundos == 0) {
		desenhaPista();
		return true;
	}

	if (segundos > 999)
		segundos = 100;
	int verifcaCorrida;
	for (int i = 0; i < segundos; i++) {
		
		verifcaCorrida = 0;
		for (auto carro : carrosNaPista) {
			if (carro->verificaCompeticao()) {
				if (carro->verificaEmergencia() || carro->obtemBateriaAtual() == 0 || carro->verificaDano()) {//(falta bateria /acidente/sinal emergencia)
					g->recebeCarro(removeCarro(carro->obtemId()));//mete na garagem
					continue;
				}

				verifcaCorrida++;
				carro->decisaoPiloto(this);

				//verifica se ganhou
				if (carro->obtemDistanciaPercorrida() >= comprimento) {
					int pos = obtemPosCorrida(carro->obtemId());
					carro->fimCompeticao();//mas mantem na pista
					if (obtemPosCorrida(carro->obtemId()) == 0) {
						carro->adicionaPontuacao(10);
					}
					else if (obtemPosCorrida(carro->obtemId()) == 1) {
						carro->adicionaPontuacao(5);
					}
					else if (obtemPosCorrida(carro->obtemId()) == 2) {
						carro->adicionaPontuacao(2);
					}
					continue;
				}

			}
				
		}

		if (verifcaCorrida>0) {
			ordenaPosicoes();
			desenhaPista();
			cout << "Prima qualquer tecla...(ESCAPE para sair)" << endl;
			CHAR key = Consola::getch();
			if (key == Consola::ESCAPE)
				i = 101;

		}
		else {
			cout << "Ja nao existe carros a competir(final da corrida)" << endl;
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
			if (carrosNaPista.at(i)->obtemDistanciaPercorrida() >= comprimento)
				continue;

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
		os << "Pista:" << comprimento << " metros, tempo = " << tempoCorrida << endl;
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
	Consola::clrscr();
	int linhaInfo = 0;
	int numeroDeLinhasPorPista = 4; //(3 de pista + 1 barreira)
	int limiteEsquerdoPista = Consola::ScreenSizeX - (numeroDeLinhasPorPista * nMax) - 2;
	int limiteSuperiorPista = 1;
	Consola::gotoxy(0, 0);
	cout << obtemPista();
	linhaInfo += (int)carrosNaPista.size();

	int tam = comprimento;
	int fatorReducao = 0;
	while (tam > Consola::ScreenSizeY) {//reduz o tamanho da pista para caber no ecra
		tam = tam / 2;
		fatorReducao++;
	}

	cout << "Fator Reducao: " << fatorReducao << endl;
	cout << "Tamanho da pista reduzida: " << tam << endl;
	linhaInfo += 2;

	//Significado cores
	Consola::setBackgroundColor(Consola::CINZENTO);
	Consola::setTextColor(Consola::AZUL_CLARO);
	cout << "(Sem bateria)";
	Consola::setTextColor(Consola::AMARELO_CLARO);
	cout << "(Sinal Emergencia)";
	Consola::setTextColor(Consola::VERMELHO_CLARO);
	cout << "(Dano Irreparavel)";

	linhaInfo += 2;

	int linhaWarning = linhaInfo;
	Consola::gotoxy(0, linhaWarning);
	Consola::clearWarningArea(linhaInfo,(int)carrosNaPista.size());
	linhaInfo += (int)carrosNaPista.size();

	
	for (int y = 0; y < tam; y++) {//pista

		for (int x = 0; x < nMax*numeroDeLinhasPorPista; x++) {
			Consola::setBackgroundColor(Consola::PRETO);
			Consola::gotoxy(limiteEsquerdoPista + x - 1, y + limiteSuperiorPista);
			cout << " ";
			if (y == tam - 1 || y == 0 ) {//meta/linha partida
				Consola::setBackgroundColor(Consola::BRANCO_CLARO);
				Consola::gotoxy(limiteEsquerdoPista + x - 1, y + limiteSuperiorPista);
				cout << " ";
			}
		}


		for (int x = 0; x <= nMax * numeroDeLinhasPorPista; x += 4) {//barreira
			Consola::setTextColor(Consola::BRANCO_CLARO);
			Consola::gotoxy(limiteEsquerdoPista + x - 1, y + limiteSuperiorPista);
			cout << "|";
		}
	}

	Consola::setBackgroundColor(Consola::CINZENTO);
	Consola::setTextColor(Consola::CYAN_CLARO);
	 
	int distancia;
	for (int i = 0; i < carrosNaPista.size(); i++) {//carros

		//warnings
		if (carrosNaPista.at(i)->verificaEmergencia() || carrosNaPista.at(i)->obtemBateriaAtual() == 0 || carrosNaPista.at(i)->verificaDano()) {//(falta bateria /acidente/sinal emergencia)
			Consola::gotoxy(0, linhaWarning++);
			cout << "Carro[" << carrosNaPista.at(i)->obtemId() << "] ira ser removido da pista.";
		}

		distancia = carrosNaPista.at(i)->obtemDistanciaPercorrida();
		for(int f = 0;f<fatorReducao;f++)
			distancia = distancia / 2;
		Consola::gotoxy(0,i+ linhaInfo);
		Consola::setBackgroundColor(Consola::CINZENTO);
		Consola::setTextColor(Consola::PRETO);
		cout << "Carro " << carrosNaPista.at(i)->obtemId() << " percorreu:" << carrosNaPista.at(i)->obtemDistanciaPercorrida() << "m ou " << distancia << " na pista, via" << carrosNaPista.at(i)->obtemLinhaPista();

		if (distancia == 0) {//inicio 
			Consola::setBackgroundColor(Consola::BRANCO_CLARO);
			Consola::setTextColor(Consola::PRETO);
		}
		else if (distancia >= tam) {//fim
			Consola::setBackgroundColor(Consola::BRANCO_CLARO);
			if (carrosNaPista.at(i)->obtemDistanciaPercorrida() >= comprimento)
				Consola::setTextColor(Consola::VERDE);
			else
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

		
		Consola::gotoxy(limiteEsquerdoPista - numeroDeLinhasPorPista + (carrosNaPista.at(i)->obtemLinhaPista() * numeroDeLinhasPorPista) + 1, distancia + limiteSuperiorPista);
		cout << carrosNaPista.at(i)->obtemId();
	}

	linhaInfo += (int)carrosNaPista.size();

	//before exit
	Consola::setTextColor(Consola::CYAN_CLARO);
	Consola::setBackgroundColor(Consola::CINZENTO);
	Consola::gotoxy(0, linhaInfo);

	return;
}
