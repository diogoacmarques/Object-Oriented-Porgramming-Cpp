#pragma once
#include <string>
#include <vector>

class Carro;

class Piloto
{
	static std::vector<std::string> todosNomesPilotos;
	std::string nome;
	const std::string tipo;
	char idCarro;
	
public:
	Piloto(std::string n);
	~Piloto();

	//funcionalidades
	std::string obtemNome() const;
	std::string obtemTipo() const;

	//Equipa
	//bool temEquipa() const;//verifica se o piloto tem equipa(carro)
	//bool adicionaEquipa(int id,Carro * c);
	//bool removeEquipa();

	//Carro
	bool temCarro() const;
	bool adicionaCarro(char id);
	bool removeCarro();


	bool tomaDecisao(Carro * c);//meta 1

	//toString
	std::string pilotoToString() const;
};