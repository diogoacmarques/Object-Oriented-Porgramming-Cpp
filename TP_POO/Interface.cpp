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
	Consola::setTextSize(15, 15);
	Consola::setScreenSize(Consola::ScreeSizeY, Consola::ScreeSizeX);  // linhas colunas. valores grandes pode nao dar
	Consola::setBackgroundColor(Consola::CINZENTO);  // favor consultar o .h para ver as constantes
	Consola::setTextColor(Consola::CYAN_CLARO);
	Consola::clrscr();
	Consola::gotoxy(0, 0);

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
			else if (comando == "teste") {
				func();
				continue;
			}
				

			if (modo == 1) {//modo 1
				//meta 1: Execução de todos os comandos exceto savedgv, loaddgv e deldgv.
				if (comando == "carregaP")
					jogo.lerFicheiroPiloto(linha);
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
					saveDgv(linha);//meta 2
				else if (comando == "loaddgv")
					loadDgv(linha);//meta 2
				else if (comando == "deldgv")
					deleteDgv(linha);//meta 2
				else if (comando == "campeonato") {
					if (campeonato(linha))
						modo = 2;
				}
				else
					cout << "Este comando nao se encontra na lista do modo 1!" << endl;
			}
			else {//modo 2
				if (comando == "listacarros") {
					log.push_back("listaCarros");
					cout << jogo.listaCarros();
					}
				else if (comando == "preparaAutodromo") {
					log.push_back("preparaAutodromo");
					if (!jogo.insereCarrosAutodromo())
						modo = 1;
				}
				else if (comando == "carregabat")
					carregaBat(linha);
				else if (comando == "carregatudo") {
					log.push_back("carregaTudo");
					jogo.carregaTudo();
				}
				else if (comando == "corrida") {
					log.push_back("corrida");
					if (jogo.corrida())
						modo = 2;
					else
						modo = 1;
				}
				else if (comando == "acidente")
					acidente(linha);
				else if (comando == "stop")
					stop(linha);
				else if (comando == "destroi")
					destroi(linha);
				else if (comando == "passatempo")
					passaTempo(linha);
				else if (comando == "log") {
					for (auto l : log)
						cout << l << endl;
				}
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
			cout << "Pametros para a criacao de carro = (velocidadeMaxima capacidadeInicial capacidadeMaxima marca modelo):";
		else if (tipo == "p")
			cout << "Pametros para a criacao de piloto = tipo nome):";
		if (tipo == "a")
			cout << "Pametros para a criacao de autodromo = (N comprimento nome):";

		getline(cin, parametros);
	}

	cout << "\tTipo='" << tipo << "'\n\tParametros=" << parametros << endl;

	if (tipo == "c") {
		//carro
		string capInicial = "", capMaxima = "", marca = "", modelo = "", velMax = "";

		velMax = splitLine(parametros);
		parametros.erase(0, velMax.size() + 1);

		capInicial = splitLine(parametros);
		parametros.erase(0, capInicial.size() + 1);

		capMaxima = splitLine(parametros);
		parametros.erase(0, capMaxima.size() + 1);

		marca = splitLine(parametros);
		parametros.erase(0, marca.size() + 1);

		//verificar se tem todos os elementos necessarios
		if (capInicial == "" || capMaxima == "" || marca == "" || velMax == "") {
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

		cout << "\tCarro:" << marca << "," << modelo << "(" << capInicial << "/" << capMaxima << ") e velocidae" << velMax << "\n" << endl;
		jogo.criaCarro(stoi(velMax),stoi(capInicial), stoi(capMaxima), marca, modelo);

		//log.push_back("cria c " + velMax + " " + capInicial + " " + capMaxima + " " + marca + " " + modelo);
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
		if (jogo.criaPiloto(tipoPiloto, nome)) {
			return true;
			//log.push_back("cria p " + tipoPiloto + " " + nome);
		}
		else {
			cout << "Este tipo de piloto nao existe: " << tipoPiloto << endl;
			return false;
		}
			
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
		//log.push_back("cria a " + to_string(n) + " " + to_string(comprimento) +" " + nome);

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

bool Interface::saveDgv(std::string parametros)
{
	if (parametros.empty()) {//sem parametros
		cout << "Nome da DGV:";
		getline(cin, parametros);
		parametros = splitLine(parametros);
	}

	if (parametros.empty()){
		cout << "Nome nao inserido, a cancelar." << endl;
		return false;
	}

	return jogo.saveDGV(parametros);
}

bool Interface::loadDgv(std::string parametros)
{
	if (parametros.empty()) {//sem parametros
		cout << "Nome da DGV:";
		getline(cin, parametros);
		parametros = splitLine(parametros);
	}

	if (parametros.empty()) {
		cout << "Nome nao inserido, a cancelar." << endl;
		return false;
	}

	return jogo.loadDGV(parametros);
}

bool Interface::deleteDgv(std::string parametros)
{
	if (parametros.empty()) {//sem parametros
		cout << "Nome da DGV:";
		getline(cin, parametros);
		parametros = splitLine(parametros);
	}

	if (parametros.empty()) {
		cout << "Nome nao inserido, a cancelar." << endl;
		return false;
	}

	return jogo.delDGV(parametros);
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
		log.push_back("campeonato " + parametros);
		return jogo.campeonato(autodromosCampeonato);//A1 A2 A3 A4
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

	if (parametros.empty() || segundos < 0){
		cout << "Parametros de tempo invalido" << endl;
		return false;
	}
	

	//cout << "Corrida avanca em " << segundos << " segundos." << endl;

	jogo.passatempo(segundos);
	log.push_back("passatempo " + to_string(segundos));

	return true;
}

bool Interface::carregaBat(std::string parametros)
{
	int quantidade;
	char idCarro;
	if (parametros.empty()) {
		cout << "Insira os seguintes parametros:(<letraCarro> <Q>):";
		getline(cin, parametros);
	}
	
	if (parametros.empty()) {
		cout << "parametros nao insereridos" << endl;
		return false;
	}
	
	string tmp = splitLine(parametros);
	parametros.erase(0, tmp.size() + 1);

	idCarro = tmp[0];

	if (parametros.empty()) {
		cout << "Quantidade nao insererida" << endl;
		return false;
	}

	quantidade = stoi(parametros);

	log.push_back("carregabat " + to_string(idCarro) + " " + to_string(quantidade));


	if (!jogo.carregaBat(idCarro, quantidade)) {
		cout << "Parametros <letraCarro> ou <Q> invalidos" << endl;
		return false;
	}

	return true;
}

bool Interface::acidente(std::string parametros)
{
	
	if (parametros.empty()) {//sem parametros
		cout << "Indique o id do carro:";
		getline(cin, parametros);
	}

	string idCarro = splitLine(parametros);

	
	if (!idCarro.empty()){
		char id = idCarro[0];
		log.push_back("acidente " + id);
		if (jogo.acidente(id))
			cout << "O carro com o id '" << id << "' teve um acidente" << endl;
		else
			cout << "O carro com o id '" << id << "' nao teve um acidente" << endl;
		return true;
	}
	else {
		cout << "O id do carro inserido e invalido." << endl;
		return false;
	}
	return false;
}

bool Interface::stop(std::string parametros)
{
	if (parametros.empty()) {//sem parametros
		cout << "Indique o nome do piloto:";
		getline(cin, parametros);
	}

	string nomePiloto = splitLine(parametros);

	if (!nomePiloto.empty()) {
		log.push_back("stop " + nomePiloto);

		if (jogo.stopPiloto(nomePiloto))
			cout << "O piloto '" << nomePiloto << "' ativou o sinalDeEmergencia" << endl;
		else
			cout << "O piloto '" << nomePiloto << "' nao ativou o sinalDeEmergencia" << endl;

		return true;
	}
	else {
		cout << "O nome do piloto inserido e invalido." << endl;
		return false;
	}
	return false;
}

bool Interface::destroi(std::string parametros)
{
	if (parametros.empty()) {//sem parametros
		cout << "Indique o id do Carro";
		getline(cin, parametros);
	}

	string idCarro = splitLine(parametros);

	if (!idCarro.empty()) {
		char id = idCarro[0];
		log.push_back("acidente " + id);

		if (jogo.destroi(id))
			cout << "O carro com o id '" << id << "' foi destruido" << endl;
		else
			cout << "O carro com o id '" << id << "' nao foi destruido" << endl;
		return true;
	}
	else {
		cout << "O ID do carro inserido e invalido." << endl;
		return false;
	}
	return false;
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
	int comprimento = 40;//parametros teste
	int nMax = 16;//parametros teste
	//Precisa de ter 3 espaços de estrada para cada carro, para se ver bem
	//Mais NumeroDePistas-1, para dar para o '|', ou seja, tem que se calcular o numero de pistas x 4
	int tam = comprimento;
	while (tam > Consola::ScreeSizeY) {//reduz o tamanho da pista para caber no ecra
		tam = tam / 2;
	}

	Consola::gotoxy(15, 0);
	cout << "Tamanho da pista:" << comprimento
		<< " | Tam=" << tam << ",nMax=" << nMax;


	for (int i = 0; i < tam; i++) {

		for (int j = 0; j < nMax; j++) {
			Consola::setBackgroundColor(Consola::PRETO);
			Consola::gotoxy((Consola::ScreeSizeX / 2) + 20 + j + 1, i + 1);
			cout << " ";
			if (i == tam - 1) {
				Consola::setBackgroundColor(Consola::BRANCO_CLARO);
				Consola::gotoxy((Consola::ScreeSizeX / 2) + 20 + j + 1, i + 1);
				cout << " ";
			}
		}
		for (int j = 0; j <= nMax; j+=4) {
				Consola::setTextColor(Consola::BRANCO_CLARO);
				Consola::gotoxy((Consola::ScreeSizeX / 2) + 20 + j + 1, i + 1);
				cout << "|";
		}

		

	}

	Consola::setBackgroundColor(Consola::CINZENTO);
	cout << endl;

	return false;
}
