#pragma once
#include <string>
#include <vector>
#include "Carro.h"
#include "Piloto.h"
class DVG
{
	std::vector<Piloto*> todosPilotos;
	std::vector<Carro*> todosCarros;
public:
	DVG();
	~DVG();

	//Piloto
	Piloto * obtemPiloto(std::string nome);//devia ser privado?
	bool criaPiloto(std::string tipo,std::string nome);
	bool apagaPiloto(std::string nome);
	int obtemPosVectorPiloto(std::string nome) const;

	//Carro
	Carro * obtemCarro(char letra);
	bool criaCarro(int capInicial, int capMax, std::string marca, std::string modelo = "");
	bool apagaCarro(char letra);
	int obtemPosVectorCarro(char letra) const;




	//toString
	std::string obtemTodosCarros();
	std::string obtemTodosPilotos();

};