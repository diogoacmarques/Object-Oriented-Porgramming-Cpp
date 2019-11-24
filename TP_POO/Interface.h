#pragma once
#include "Jogo.h"
#include <string>
class Interface
{
	Jogo jogo;

	std::string nome;
	int modo;

	std::string precisaNomeFicheiro();

	std::string splitLine(std::string str);

	bool cria(std::string parametros);

	bool apaga(std::string parametros);

	bool entraNoCarro(std::string parametros);

	bool saiDoCarro(std::string parametros);

	std::string listaTudo();

	bool campeonato(std::string parametros);

	bool passaTempo(std::string parametros);

	bool verificaDigitos(std::string parametros);

public:
	Interface(std::string n = "default");
	~Interface();

	//funcionalidades
	bool inciar();
	bool func();
};