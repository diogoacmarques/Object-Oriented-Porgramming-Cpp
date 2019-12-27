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
	DVG(const DVG & original);
	~DVG();
	DVG & operator=(const DVG & original);

	//Piloto
	Piloto * obtemPiloto(std::string nome) const;//devia ser privado?
	std::vector<Piloto*> obtemVectorPilotos() const;
	bool criaPiloto(std::string tipo,std::string nome);
	bool apagaPiloto(std::string nome);
	int obtemPosVectorPiloto(std::string nome) const;


	//Carro
	Carro * obtemCarro(char letra) const;
	std::vector<Carro*> obtemVectorCarros() const;
	bool criaCarro(int velMax,int capInicial, int capMax, std::string marca, std::string modelo = "");
	bool apagaCarro(char letra);
	int obtemPosVectorCarro(char letra) const;
	bool destroiCarro(char idCarro);


	//Carro/Piloto
	bool associaCarroPiloto(char idCarro, std::string nomePiloto);
	bool removePilotoCarro(char idCarro);

	//toString
	std::string obtemTodosCarros() const;
	std::string obtemTodosPilotos() const;
	std::string obtemNome() const;

};