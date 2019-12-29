#pragma once
#include <string>
#include "Piloto.h"

class Pista;

class Carro
{
	std::string marca, modelo;
	static char idStatic;//id (partilhado) que vai sendo alterado conforme o numero de carros
	const char id;//id do carro	
	//bateria
	int mAh;
	const int capcidadeMaxima;
	//moviemento
	bool acelarador;//postiivo acelarar
	int metroSegundo = 0;
	int mPercorrido = 0;
	const int velcidadeMaxima;
	//estado
	bool danoIrreparavel = false;
	bool sinalEmergencia = false;
	
	//Pista
	bool naPista;

	//Piloto
	Piloto * piloto;

public:
	//capacidadeInicial capacidadeMaxima marca modelo (modelo pode não ser inserido)
	Carro(int velMax,int capInicial,int capMax,std::string marca,std::string modelo = "modelo_base");
	~Carro();

	//funcionalidades
	bool verificaDano() const;
	bool verificaEmergencia() const;
	int obtemBateriaMax() const;
	int obtemBateriaAtual() const;
	int carregaBateria(int n);
	bool carregamentoTotal();
	char obtemId() const;
	int obtemVelMax() const;
	void ativaSinalEmergencia();
	void danificaCarro();
	std::string infoCompeticao() const;

	//piloto
	bool verificaPiloto() const;
	bool adicionaPiloto(Piloto * p);
	bool removePiloto();
	bool decisaoPiloto(Pista * p);
	std::string obtemNomePiloto() const;
	bool verificaAptidao() const;//verifica se reune condições para correr

	//Pista
	bool verificaPista() const;
	bool entraPista();
	bool saiPista();
	bool acabaCorrida(int pontos);

	bool entraNaGaragem();
	//movimento
	int obtemVelocidade() const;
	bool acelera();
	bool trava();
	bool para();
	int obtemDistanciaPercorrida() const;
	bool passaSegundo();

	bool resetDistancia();

	//toString
	std::string carroToString() const;

};