#pragma once
#include "DVG.h"
#include "Autodromo.h"
#include "Campeonato.h"
#include <vector>
class Jogo
{
	DVG dvg;
	Campeonato * camp;
	std::vector <Autodromo*> todosAutodromos;

	Autodromo * obtemAutodromo(std::string nomeA) const;
	
	bool verificaDigitos(std::string parametros);
public:
	Jogo();
	~Jogo();

	//Ficheiro
	bool lerFicheiroPiloto(std::string fileName);
	bool lerFicheiroCarro(std::string fileName);
	bool lerFicheiroAutodromo(std::string fileName);

	//cria
	bool criaCarro(int velMax,int capMaxima, int capInicial, std::string marca, std::string modelo = "");
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
	//campeonato
	bool verificaAutodromo(std::string n) const;
	bool campeonato(std::vector<std::string> nomesAutodromoIn);

	//lista carros
	std::string listaCarros() const;

	//carregabat

	//carregatudo
	bool carregaTudo();

	//corrida
	bool insereEquipaAutodromo();
	bool corrida();

	//acidente

	//stop

	//destroi

	//passatempo
	bool passatempo(int segundos);

	//log
	

	

};

