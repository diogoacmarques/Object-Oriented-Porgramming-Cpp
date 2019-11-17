#pragma once
#include "DVG.h"
#include "Autodromo.h"
#include <vector>
class Jogo
{
	DVG dvg;
	std::vector <Autodromo*> todosAutodromos;

	//separaPalavra
	Autodromo * obtemAutodromo(std::string nomeA) const;
public:
	Jogo();
	~Jogo();

	//Ficheiro
	bool lerFicheiroPiloto(std::string fileName);
	bool lerFicheiroCarro(std::string fileName);
	bool lerFicheiroAutodromo(std::string fileName);

	//cria
	bool criaCarro(int capMaxima, int capInicial, std::string marca, std::string modelo = "");
	bool criaPiloto(std::string tipo, std::string nome);
	bool criaAutodromo(int nMax, int comprimento,std::string nome);
	std::string autodromoToString();

	//apaga
	bool apagaCarro(char id);
	bool apagaPiloto(std::string nome);
	bool apagaAutodromo(std::string nome);

	//entranocarro
	bool entraNoCarro(char idCarro, std::string nomePiloto);

	//saidocarro
	bool saiDoCarro(char idCarro);

	//lista
	std::string lista();

	//savedgv
	bool saveDGV(std::string nome);

	//loaddgv
	bool loadDGV(std::string nome);

	//deldgv
	bool delDGV(std::string nome);

	//modo 2
	//campeonato (recebe um array/vector com o nome dos autodromos)
	bool verificaAutodromo(std::string n) const;
	bool campeonato(std::vector<std::string> nomesAutodromoIn);


};

