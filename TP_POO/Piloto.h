#pragma once
#include <string>
#include <vector>
class Piloto
{
	const std::string nome;
	const std::string tipo;
	char idCarro;
public:
	Piloto(std::string n);
	~Piloto();

	//funcionalidades
	std::string obtemNome() const;
	   
		//carro
	bool temCarro() const;//verifica se esta dentro de algum carro
	bool entraNoCarro(char id);//insere piloto
	bool removeCarro();
	char obtemIdCarro() const;

	//toString
	std::string pilotoToString();
};