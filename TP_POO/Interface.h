#pragma once
#include "Carro.h"
#include <string>
class Interface
{
	std::string nome;
	int modo;

	std::string precisaNomeFicheiro();
	bool lerFicheiroPiloto(std::string fileName);
	bool lerFicheiroCarro(std::string fileName);
	bool lerFicheiroAutodromo(std::string fileName);
	std::string splitLine(std::string str);

	bool cria(std::string parametros);
	bool apaga(std::string parametros);
public:
	Interface(std::string n = "default");
	~Interface();

	//funcionalidades
	bool start();
	bool getCommand();
	

	bool func();
};

