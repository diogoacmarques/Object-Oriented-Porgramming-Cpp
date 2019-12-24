#pragma once
#include "Carro.h"
#include <string>
#include <vector>
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

	//poem equipa na pista
	bool insereCarro(Carro * c);
	Carro * removeCarro(char idCarro);
	std::vector<Carro*> removeTodosCarros();

	int obtemComprimento() const;
	int obtemNMax() const;

	bool passaTempo(int segundos);

	int obtemTempoCorrida() const;
	int obtemCarrosNaPista() const;
	int obtemPosCorrida(char idCarro);

	bool danificaCarro(int pos);

	bool iniciaCorrida();
	bool terminarCorrida();
	bool obtemEstado() const;

	//toString
	std::string obtemPista() const;

};

