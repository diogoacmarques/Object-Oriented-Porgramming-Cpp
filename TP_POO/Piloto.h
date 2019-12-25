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
	std::string obtemNome() const;
	std::string obtemTipo() const;

	//pontuacao
	void adicionaPontuacao(int pontos);
	void resetPontuacao();

	//Carro
	bool verificaCarro() const;
	bool adicionaCarro(char id);
	bool removeCarro();

	virtual bool tomaDecisao(Carro * c,Pista * p) = 0;

	//toString
	std::string pilotoToString() const;
};