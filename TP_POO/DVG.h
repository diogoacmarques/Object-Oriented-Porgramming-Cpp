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
	std::vector<Piloto*> obtemVectorPilotos() const;
	bool criaPiloto(std::string tipo,std::string nome);
	bool apagaPiloto(std::string nome);
	int obtemPosVectorPiloto(std::string nome) const;


	//Carro
	Carro * obtemCarro(char letra);
	std::vector<Carro*> obtemVectorCarros() const;
	bool criaCarro(int capInicial, int capMax, std::string marca, std::string modelo = "");
	bool apagaCarro(char letra);
	int obtemPosVectorCarro(char letra) const;

	//Carro/Piloto
	bool associaCarroPiloto(char idCarro, std::string nomePiloto);
	bool removePilotoCarro(char idCarro);


	//toString
	std::string obtemTodosCarros();
	std::string obtemTodosPilotos();

};