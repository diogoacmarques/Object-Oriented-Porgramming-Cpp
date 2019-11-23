#pragma once
#include "Carro.h"
#include <string>
#include <vector>
class Piloto
{
	static std::vector<std::string> todosNomesPilotos;
	std::string nome;
	const std::string tipo;
	bool naPista;
	int idEquipa;
public:
	Piloto(std::string n);
	~Piloto();

	//funcionalidades
	std::string obtemNome() const;
	std::string obtemTipo() const;

	//Equipa
	bool temEquipa() const;//verifica se o piloto tem equipa(carro)
	bool adicionaEquipa(int id);
	bool removeEquipa();


	bool passaSegundo();//meta 1

	//pista
	bool temPista() const;
	void entraPista();
	void saiPista();

	//toString
	std::string pilotoToString();
};