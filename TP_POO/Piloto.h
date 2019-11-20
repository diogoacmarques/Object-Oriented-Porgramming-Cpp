#pragma once
#include "Carro.h"
#include <string>
#include <vector>
class Piloto
{
	static std::vector<std::string> todosNomesPilotos;
	std::string nome;
	const std::string tipo;
	Carro * carro;
	bool naPista;
public:
	Piloto(std::string n);
	~Piloto();

	//funcionalidades
	std::string obtemNome() const;
	   
		//carro
	bool temCarro() const;//verifica se esta dentro de algum carro
	bool entraNoCarro(Carro * carro);//insere piloto
	bool removeCarro();
	char obtemIdCarro() const;
	bool passaSegundo();//meta 1
	int obtemDistanciaPercorrida() const;
	int obtemVelocidade() const;
	std::string obtemCarro() const;

	//pista
	bool temPista() const;
	void entraPista();
	void saiPista();

	//toString
	std::string pilotoToString();
};