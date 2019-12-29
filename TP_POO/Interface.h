#pragma once
#include "Jogo.h"
#include <string>
class Interface
{
	Jogo jogo;

	std::string nome;
	int modo;
	std::vector<std::string> log;

	std::string precisaNomeFicheiro();

	std::string splitLine(std::string str);

	bool cria(std::string parametros);

	bool apaga(std::string parametros);

	bool entraNoCarro(std::string parametros);

	bool saiDoCarro(std::string parametros);

	std::string listaTudo();

	bool saveDgv(std::string parametros);

	bool loadDgv(std::string parametros);

	bool deleteDgv(std::string parametros);

	bool campeonato(std::string parametros);

	bool passaTempo(std::string parametros);

	bool carregaBat(std::string parametros);

	bool acidente(std::string parametros);

	bool stop(std::string parametros);

	bool destroi(std::string parametros);
public:
	Interface(std::string n = "default");
	~Interface();

	//funcionalidades
	bool inciar();
	bool func();
};