#include "Interface.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Interface::Interface(string n):nome(n),modo(1)
{
}

Interface::~Interface()
{
}

bool Interface::inciar()
{
	cout << "Starting interface!" << endl;

	string linha;//getline
	string comando;//comando(primeira palavra da linha)
	do {
		cout << nome << "[" << modo << "]:";
		//cin.ignore();
		getline(cin, linha);

		if (linha != "") {
			comando = splitLine(linha);
			linha.erase(0, comando.size() + 1);
			//cout << "Comando:" << comando << endl;
			//cout << "Parametros:'" << linha << "'\n" << endl;

			if (comando == "fim")
				break;

			if (modo == 1) {//modo 1
				//meta 1: Execução de todos os comandos exceto savedgv, loaddgv e deldgv.
				if (comando == "carregaP")
					jogo.lerFicheiroPiloto(linha);
				//lerFicheiroPiloto(linha);
				else if (comando == "carregaC")
					jogo.lerFicheiroCarro(linha);
				else if (comando == "carregaA")
					jogo.lerFicheiroAutodromo(linha);
				else if (comando == "cria")
					cria(linha);
				else if (comando == "apaga")
					apaga(linha);
				else if (comando == "entranocarro")
					func();
				else if (comando == "saidocarro")
					func();
				else if (comando == "lista")
					cout << listaTudo();
				else if (comando == "savedgv")
					func();//meta 2
				else if (comando == "loaddgv")
					func();//meta 2
				else if (comando == "deldgv")
					func();//meta 2
				else if (comando == "campeonato") {
					func();
					modo = 2;
				}
				else
					cout << "Este comando nao se encontra na lista do modo 1!" << endl;
			}
			else {//modo 2
				//meta 1 : Comando “campeonato <A1>” (só há um autódromo).
				//meta 1 : Comando “passatempo <N>”
				if (comando == "listacarros")
					func();
				else if (comando == "carregabat")
					func();
				else if (comando == "carregatudo")
					func();
				else if (comando == "corrida")
					func();
				else if (comando == "acidente")
					func();
				else if (comando == "stop")
					func();
				else if (comando == "destroi")
					func();
				else if (comando == "passatempo")
					func();
				else if (comando == "log")
					func();
				else
					cout << "Este comando nao se encontra na lista do modo 2!" << endl;
			}
		}


	} while (linha != "fim");

	return true;
}

std::string Interface::splitLine(std::string str)
{
	string returnString = "";
	//cout << "[Input]:'" << str << "'" << endl;
	for (auto x : str)
	{
		if (x == ' ')
		{
			//cout << "[Output]:'" << returnString << "'" << endl;
			return returnString;
		}
		else
		{
			returnString = returnString + x;
		}
	}

	return str;
}

bool Interface::cria(std::string parametros)
{
	string tipo;
	tipo = splitLine(parametros);

	if (tipo == "") {//sem parametros
		cout << "Tipo de criacao(c,p,a):";
		getline(cin, tipo);
		tipo = splitLine(tipo);
	}
	else {
		parametros.erase(0, tipo.size() + 1);//remove o tipo dos parametros
	}

	if (parametros == "") {
		if (tipo == "c")
			cout << "Pametros para a criacao de carro = (capacidadeInicial capacidadeMaxima marca modelo):";
		else if (tipo == "p")
			cout << "Pametros para a criacao de piloto = tipo nome):";
		if (tipo == "a")
			cout << "Pametros para a criacao de autodromo = (N comprimento nome):";

		getline(cin, parametros);
	}

	cout << "\tTipo='" << tipo << "'\n\tParametros=" << parametros << endl;

	if (tipo == "c") {
		//carro
		string capInicial = "", capMaxima = "", marca = "", modelo = "";

		capInicial = splitLine(parametros);
		parametros.erase(0, capInicial.size() + 1);

		capMaxima = splitLine(parametros);
		parametros.erase(0, capMaxima.size() + 1);

		marca = splitLine(parametros);
		parametros.erase(0, marca.size() + 1);

		//verificar se tem todos os elementos necessarios
		if (capInicial == "" || capMaxima == "" || marca == "") {
			cout << "Nao e possivel criar carro com estes parametros!" << endl;
			return false;
		}

		if (parametros != "") {
			modelo = splitLine(parametros);
			cout << "Irei construir carro COM modelo!" << endl;
			//Carro(capacidadeInicial,capacidadeMaxima,marca,modelo)
		}
		else {
			cout << "Irei construir carro SEM modelo!" << endl;
			//Carro(capacidadeInicial,capacidadeMaxima,marca)
		}

		//cout << "\tCarro:" << marca << "," << modelo << "(" << capInicial << "/" << capMaxima << ")\n" << endl;
		jogo.criaCarro(stoi(capInicial), stoi(capMaxima), marca, modelo);
		return true;
		
	}	
	else if (tipo == "p") {
		//piloto
		string tipoPiloto = "", nome = "";

		tipoPiloto = splitLine(parametros);
		parametros.erase(0, tipoPiloto.size() + 1);

		nome = splitLine(parametros);
	
		//verificar se tem todos os elementos necessarios
		if (tipoPiloto == "" || nome == "") {
			cout << "Nao e possivel criar piloto com estes parametros!" << endl;
			return false;
		}

		//cout << "\tPiloto:(" << tipoPiloto << "," << nome << ")\n" << endl;
		jogo.criaPiloto(tipo, nome);
		return true;
	}
	else if (tipo == "a") {
		//autodromo
		string nome = "", tmp = "";
		int n = 0, comprimento = 0;

		tmp = splitLine(parametros);
		parametros.erase(0, tmp.size() + 1);
		n = stoi(tmp);

		tmp = splitLine(parametros);
		parametros.erase(0, tmp.size() + 1);
		comprimento = stoi(tmp);

		nome = splitLine(parametros);

		if (nome == "") {
			cout << "Nao e possivel criar autodromo com estes parametros!" << endl;
			return false;
		}

		//cout << "\tAutodromo[" << n << "]:" << nome << "(" << comprimento << " metros)\n" << endl;
		jogo.criaAutodromo(n, comprimento, nome);
		return true;
	}
	else {
		cout << "Nao existe nenhum objeto do tipo '" << tipo << "'" << endl;
	}
	return false;
}

bool Interface::apaga(std::string parametros)
{
	string tipo;
	tipo = splitLine(parametros);

	if (tipo == "") {//sem parametros
		cout << "Tipo de objeto para apgar(c,p,a):";
		getline(cin, tipo);
		tipo = splitLine(tipo);
	}
	else {
		parametros.erase(0, tipo.size() + 1);//remove o tipo dos parametros
	}

	if (parametros == "") {
		if (tipo == "c")
			cout << "Identificador do carro(letra):";
		else if (tipo == "p")
			cout << "Identificador do piloto(nome):";
		if (tipo == "a")
			cout << "Identificador do autodromo(nome):";
		getline(cin, parametros);
	}

	parametros = splitLine(parametros);

	cout << "\tTipo='" << tipo << "'\n\tParametros=" << parametros << endl;
	if (tipo == "c") {
		return jogo.apagaCarro(parametros[0]);
	}
	else if (tipo == "p") {
		return jogo.apagaPiloto(parametros);
	}
	if (tipo == "a") {
		return jogo.apagaAutodromo(parametros);
	}
	return false;
}

std::string Interface::listaTudo()
{
	return jogo.lista();
}

std::string Interface::precisaNomeFicheiro()
{
	string returnString;
	cout << "Nome ficheiro + extensao:";
	getline(cin, returnString);
	returnString = splitLine(returnString);
	//cout << "Final:'" << returnString << "'!" << endl;
	return returnString;
}

bool Interface::func()
{
	cout << "Funcao temporaria para os comandos que ainda nao tem funcao construida!" << endl;
	return false;
}
