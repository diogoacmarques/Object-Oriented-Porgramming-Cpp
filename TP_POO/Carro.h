#pragma once
#include <string>
#include "Piloto.h"
class Carro
{
	std::string marca, modelo;
	static char idStatic;//id (partilhado) que vai sendo alterado conforme o numero de carros
	const char id;//id do carro	
	//bateria
	int mAh;
	const int capcidadeMaxima;
	//moviemento
	bool movimento = false;
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
	int obtemBateriaMax() const;
	int obtemBateriaAtual() const;
	int carregaBateria(int n);
	bool carregamentoTotal();
	char obtemId() const;
	int obtemVelMax() const;
	std::string obtemCarro() const;

	//	//Equipa
	//bool temEquipa() const;//verifica se o carro tem algum piloto
	//bool adicionaEquipa(int id);
	//bool removeEquipa();

	//piloto
	bool temPiloto() const;
	bool adicionaPiloto(Piloto * p);
	bool removePiloto();
	std::string obtemNomePiloto() const;

	//Pista
	bool verificaPista() const;
	bool entraPista();
	bool saiPista();


	bool entraNaGaragem();
	//movimento
	int obtemVelocidade() const;
	bool acelera(int quantidade);
	bool para();
	int obtemDistanciaPercorrida() const;
	bool passaSegundo();
	bool resetDistancia();

	//toString
	std::string carroToString() const;

};

