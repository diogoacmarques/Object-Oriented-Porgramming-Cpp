#pragma once
#include <string>
#include <vector>
#include "Carro.h"
#include "Piloto.h"
class DVG
{
	std::string nome;
	std::vector<Piloto*> todosPilotos;
	std::vector<Carro*> todosCarros;
public:
	DVG(std::string n);
	~DVG();

	//Piloto
	Piloto * obtemPiloto(std::string nome);//devia ser privado?
	bool criaPiloto(std::string tipo,std::string nome);
	bool apagaPiloto(std::string nome);

	//Carro
	bool criaCarro(int capInicial, int capMax, std::string, std::string modelo);
	bool apagaCarro(char letra);



};