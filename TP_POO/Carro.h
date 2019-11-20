#pragma once
#include <string>
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
	static const int kmHMax = 120;
	//estado
	bool danoIrreparavel = false;
	bool sinalEmergencia = false;
	//Piloto
	std::string nomePiloto;
public:
	//capacidadeInicial capacidadeMaxima marca modelo (modelo pode n�o ser inserido)
	Carro(int capInicial,int capMax,std::string marca,std::string modelo = "modelo_base");
	~Carro();

	//funcionalidades
	int carregaBateria(int n);
	bool carregamentoTotal();
	char obtemId() const;
	std::string obtemCarro() const;

		//Piloto
	bool temPiloto();//verifica se o carro tem algum piloto
	bool entraPiloto(std::string nPiloto);
	bool removePiloto();
	std::string obtemNomePiloto() const;

	//movimento
	int obtemVelocidade() const;
	bool acelera(int quantidade);
	bool para();
	int obtemDistanciaPercorrida() const;
	void passaSegundo();

	//toString
	std::string carroToString();
};

