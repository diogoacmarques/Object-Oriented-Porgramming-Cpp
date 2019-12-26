#pragma once
#include <string>
#include <vector>

class Carro;
class Pista;

class Piloto
{
	static std::vector<std::string> todosNomesPilotos;
	std::string nome;
	const std::string tipo;
	int pontuacao;
	char idCarro;
public:
	Piloto(std::string n);
	~Piloto();

	//funcionalidades

	//pontuacao
	void adicionaPontuacao(int pontos);
	void resetPontuacao();

	//ordens
	bool stop(Carro * c);

	//Carro
	char obtemIdCarro() const;
	bool verificaCarro() const;
	bool adicionaCarro(char id);
	bool removeCarro();

	virtual bool tomaDecisao(Carro * c,Pista * p) = 0;

	//toString
	std::string obtemNome() const;
	std::string obtemTipo() const;

	std::string pilotoToString() const;


};