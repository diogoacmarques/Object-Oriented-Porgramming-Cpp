#pragma once
#include "Carro.h"
#include "Consola.h"
#include <string>
#include <vector>

class Garagem;

class Pista
{
	const int comprimento;
	int nMax;
	std::vector<Carro*> carrosNaPista;
	bool emCompeticao;
	int tempoCorrida;
public:
	Pista(int nM, int comp);
	~Pista();

	//funcionalidades
	int obtemComprimento() const;
	int obtemNMax() const;
	bool passaTempo(int segundos, Garagem * g);
	int obtemTempoCorrida() const;
	int obtemNumCarrosNaPista() const;
	bool iniciaCorrida();
	bool terminarCorrida();
	bool obtemEstado() const;
	void ordenaPosicoes();
	void removeCarrosInuteis(Garagem * g);

	//Carro
	bool insereCarro(Carro * c);
	Carro * removeCarro(char idCarro);
	std::vector<Carro*> removeTodosCarros();
	bool danificaCarro(int pos);
	int obtemPosCorrida(char idCarro);
	
	//Piloto
	bool stopPiloto(std::string nomePiloto);

	//toString
	std::string obtemPista() const;
	void desenhaPista() const;

};

