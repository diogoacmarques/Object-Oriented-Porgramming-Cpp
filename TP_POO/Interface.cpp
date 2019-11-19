#include "Interface.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

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

			//geral
			if (comando == "fim")
				break;
			else if (comando == "clear") {
				system("cls");
				continue;
			}
				

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
					entraNoCarro(linha);
				else if (comando == "saidocarro")
					saiDoCarro(linha);
				else if (comando == "lista")
					cout << listaTudo();
				else if (comando == "savedgv")
					func();//meta 2
				else if (comando == "loaddgv")
					func();//meta 2
				else if (comando == "deldgv")
					func();//meta 2
				else if (comando == "campeonato") {
					campeonato(linha);
					modo = 2;
				}
				else
					cout << "Este comando nao se encontra na lista do modo 1!" << endl;
			}
			else {//modo 2
				//meta 1 : Comando “campeonato <A1>” (só há um autódromo).
				//meta 1 : Comando “passatempo <N>”
				if (comando == "listacarros")
					cout << jogo.listaCarros();
				else if (comando == "carregabat")
					func();
				else if (comando == "carregatudo")
					jogo.carregaTudo();
				else if (comando == "corrida")
					jogo.corrida();
				else if (comando == "acidente")
					func();
				else if (comando == "stop")
					func();
				else if (comando == "destroi")
					func();
				else if (comando == "passatempo")
					passaTempo(linha);
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

bool Interface::entraNoCarro(std::string parametros)
{
	string nomePiloto;
	string tmp;
	char idCarro;
	if (parametros.empty()) {
		cout << "Insira os seguintes parametros:(<letraCarro> <nomePiloto>):";
		getline(cin, parametros);
	}

	tmp = splitLine(parametros);
	if (!tmp.empty()) {
		idCarro = tmp[0];
	}
	else {
		cout << "Erro nos parametros(letraCarro)" << endl;
		return false;
	}
	parametros.erase(0,tmp.size() + 1);
			nomePiloto = splitLine(parametros);
	if (nomePiloto.empty()) {
		cout << "Erro nos parametros(nomePiloto)" << endl;
		return false;
	}
	
	cout << "Funcao Entra no carro parametros:" << endl;
	cout << "\tPiloto:'" << nomePiloto << "'" << endl;
	cout << "\tidCarro:'" << idCarro << "'" << endl;


	if (jogo.entraNoCarro(idCarro, nomePiloto)) {
		cout << "Sucesso!" << endl;
		return true;
	}
	
	cout << "Erro ao associar carro/piloto" << endl;
	return false;

}

bool Interface::saiDoCarro(std::string parametros)
{
	string tmp;
	char idCarro;
	if (parametros.empty()) {
		cout << "Insira os seguintes parametros:(<letraCarro>):";
		getline(cin, parametros);
	}

	tmp = splitLine(parametros);

	if (!tmp.empty()) {
		idCarro = tmp[0];
	}
	else {
		cout << "Erro nos parametros(letraCarro)" << endl;
		return false;
	}

	cout << "Funcao sai do carro parametros:" << endl;
	cout << "\tidCarro:'" << idCarro << "'" << endl;


	if (jogo.saiDoCarro(idCarro)) {
		cout << "Sucesso!" << endl;
		return true;
	}

	cout << "Erro a remover piloto do carro" << endl;
	return false;
}

std::string Interface::listaTudo()
{
	return jogo.lista();
}

bool Interface::campeonato(std::string parametros)
{
	vector<string> autodromosCampeonato;
	string nomeAutodromo;
	if (parametros.empty()) {
		cout << "Insira os seguintes parametros:(<A1> <A2> ... <An>):";
		getline(cin, parametros);
		if (parametros.empty()) {
			cout << "Parametros invalidos" << endl;
			return false;
		}
	}

	while (!parametros.empty()) {

		nomeAutodromo = splitLine(parametros);
		parametros.erase(0, nomeAutodromo.size() + 1);

		autodromosCampeonato.push_back(nomeAutodromo);	
	}
	
	if (!autodromosCampeonato.empty()) {
		jogo.campeonato(autodromosCampeonato);
	}
		
		return false;
}

bool Interface::passaTempo(std::string parametros)
{
	int segundos;
	if (parametros.empty()) {
		cout << "Insira os seguintes parametros:(<N>):";
		getline(cin, parametros);
	}

	segundos = stoi(parametros);

	if (parametros.empty() || segundos <= 0){
		cout << "Parametros de tempo invalido" << endl;
		return false;
	}
	

	//cout << "Corrida avanca em " << segundos << " segundos." << endl;

	jogo.passatempo(segundos);

	return true;
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
