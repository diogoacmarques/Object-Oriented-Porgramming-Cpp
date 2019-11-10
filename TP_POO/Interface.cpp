#include "Interface.h"
#include <iostream>
using namespace std;

Interface::Interface(string n):nome(n),modo(1)
{
}

Interface::~Interface()
{
}

bool Interface::start()
{
	cout << "Starting Game!" << endl;
	getCommand();
	return true;
}

bool Interface::getCommand()
{
	string linha;//getline
	string comando;//comando(primeira palavra da linha)
	do {
		cout << nome << "[" << modo << "]:";
		//cin.ignore();
		getline(cin, linha);

		if (linha != "") {
			comando = splitLine(linha);
			linha.erase(0, comando.size() + 1);
			cout << "Comando:" << comando << endl;
			cout << "Parametros:'" << linha << "'\n" << endl;


			if (modo == 1) {//modo 1
				if (comando == "carregaP")
					readFile(linha);
				else if (comando == "carregaC")
					func();
				else if (comando == "carregaA")
					func();
				else if (comando == "cria")
					func();
				else if (comando == "apaga")
					func();
				else if (comando == "entranocarro")
					func();
				else if (comando == "saidocarro")
					func();
				else if (comando == "lista")
					func();
				else if (comando == "savedgv")
					func();
				else if (comando == "loaddgv")
					func();
				else if (comando == "deldgv")
					func();
				else if (comando == "campeonato") {
					func();
					modo = 2;
				}
				else
					cout << "Este comando nao se encontra na lista do modo 1!" << endl;
			}
			else {//modo 2
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

bool Interface::readFile(std::string fileName)
{
	cout << "Will read file:'" << fileName << "'!" << endl;
	return false;
}

bool Interface::func()
{
	cout << "Funcao temporaria para os comandos que ainda nao tem funcao construida!" << endl;
	return false;
}
