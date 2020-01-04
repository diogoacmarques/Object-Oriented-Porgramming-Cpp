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

	//Carro
	bool insereCarro(Carro * c);
	Carro * removeCarro(char idCarro);
	std::vector<Carro*> removeTodosCarros();
	

	int obtemComprimento() const;
	int obtemNMax() const;

	bool passaTempo(int segundos, Garagem * g);

	int obtemTempoCorrida() const;
	int obtemNumCarrosNaPista() const;
	int obtemPosCorrida(char idCarro);

	bool danificaCarro(int pos);

	bool iniciaCorrida();
	bool terminarCorrida();
	bool obtemEstado() const;

	void ordenaPosicoes();
	void removeCarrosInuteis(Garagem * g);

	//toString
	std::string obtemPista() const;
	void desenhaPista() const;

};

