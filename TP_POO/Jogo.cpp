#include "Jogo.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

Autodromo * Jogo::obtemAutodromo(std::string nomeA) const
{
	vector<Autodromo*>::const_iterator it = todosAutodromos.begin();
	while (it != todosAutodromos.end()) {
		if (nomeA == (*it)->obtemNome()) {
			return (*it);
		}
		it++;
	}
	return nullptr;
}

bool Jogo::verificaDigitos(std::string parametros)
{
	for (int i = 0; i < parametros.size(); i++)
		if (!isdigit(parametros[i]))
			return false;
	return true;
}

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
	cout << "Destrutor_Jogo" << endl;
	//delete [] todosAutodromos;
	for (int i = 0; i < todosAutodromos.size(); i++)
		delete todosAutodromos.at(i);
	todosAutodromos.clear();
}

bool Jogo::lerFicheiroPiloto(std::string fileName)
{
	//cout << "A abrir o ficheio:'" << fileName << "'" << endl;
	string line, tipo, nome;

	size_t pos;

	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			tipo = "", nome = "",pos = 0;//reset
			cout << "Linha:" << line << endl;

			//tipo
			pos = line.find_first_of(" ");
			tipo = line.substr(0, pos);
			line.erase(0, tipo.size() + 1);
			
			//nome
			nome = line;

			//cout << "\tPiloto:(" << tipo << "," << nome << ")\n" << endl;
			if (!nome.empty() && !tipo.empty()) {
				criaPiloto(tipo, nome);
			}
			else
				cout << "Valores de ficheiro invalidos" << endl;

		}
		myfile.close();
		return true;
	}
	else cout << "Erro na leitura do fichero:'" << fileName << "'" << endl;

	return false;
}

bool Jogo::lerFicheiroCarro(std::string fileName)
{
	string line, marca, modelo;
	int capI, capM, velMax;

	size_t pos;

	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			//marca = "", modelo = "";//reset
			marca.erase(), modelo.erase();//reset
			capI = -1, capM = -1, pos = 0, velMax = -1;

			cout << "Linha:" << line << endl;

			//Velocidade Maxima
			pos = line.find_first_of(" ");
			if (!verificaDigitos(line.substr(0, pos))) {
				cout << "Linha com parametros invalidos (ignorada)" << endl;
				continue;
			}
			velMax = stoi(line.substr(0, pos));
			line.erase(0, pos + 1);
			
			
			//Capacidade Inicial
			pos = line.find_first_of(" ");
			if (!verificaDigitos(line.substr(0, pos))) {
				cout << "Linha com parametros invalidos (ignorada)" << endl;
				continue;
			}
			capI = stoi(line.substr(0, pos));
			line.erase(0, pos + 1);
		

			//Capacidade Maxima
			pos = line.find_first_of(" ");
			if (!verificaDigitos(line.substr(0, pos))) {
				cout << "Linha com parametros invalidos (ignorada)" << endl;
				continue;
			}
			capM = stoi(line.substr(0, pos));
			line.erase(0, pos + 1);

			//Marca
			pos = line.find_first_of(" ");
			marca = line.substr(0, pos);
			line.erase(0, pos + 1);

			if (pos != -1) {
				modelo = line;	
			}
			
			if (velMax != -1 && capI != -1 && capM != -1 && !marca.empty()) {
				//cout << "\tCarro:" << marca << "," << modelo << "(" << capI << "/" << capM << ")\n" << endl;
				criaCarro(velMax, capI, capM, marca, modelo);
			}
			
		}
		myfile.close();
		return true;
	}
	else cout << "Erro na leitura do fichero:'" << fileName << "'" << endl;

	return false;
}

bool Jogo::lerFicheiroAutodromo(std::string fileName)
{
	string line, nome, tmp;

	int n, comprimento;

	size_t pos;

	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			nome = "", tmp = "";
			n = 0, comprimento = 0;//reset

			cout << "Linha:" << line << endl;

			//Numero máximo de carrosc
			pos = line.find_first_of(" ");
			if (!verificaDigitos(line.substr(0, pos))) {
				cout << "Linha com parametros invalidos (ignorada)" << endl;
				continue;
			}
			n = stoi(line.substr(0, pos));
			line.erase(0, pos + 1);

			pos = line.find_first_of(" ");
			if (!verificaDigitos(line.substr(0, pos))) {
				cout << "Linha com parametros invalidos (ignorada)" << endl;
				continue;
			}
			comprimento = stoi(line.substr(0, pos));
			line.erase(0, pos + 1);
			
			nome = line;

			if (n != -1 && comprimento != -1 && !nome.empty()) {
				//cout << "\tAutodromo[" << n << "]:" << nome << "(" << comprimento << " metros)\n" << endl;
				criaAutodromo(n, comprimento, nome);		
			}
				
			
		}
		myfile.close();
		return true;
	}
	else cout << "Erro na leitura do fichero:'" << fileName << "'" << endl;

	return false;
}

bool Jogo::criaCarro(int velMax, int capMaxima, int capInicial, std::string marca, std::string modelo)
{
	return dvg.criaCarro(velMax,capMaxima, capInicial, marca, modelo);
}

bool Jogo::criaPiloto(std::string tipo, std::string nome)
{
	return dvg.criaPiloto(tipo, nome);
}

bool Jogo::criaAutodromo(int nMax, int comprimento, std::string nome)
{
	Autodromo * tmp;

	tmp = new Autodromo(nMax, comprimento, nome);
	todosAutodromos.push_back(tmp);

	return true;
}

std::string Jogo::autodromoToString()
{
	ostringstream os;
	vector<Autodromo*>::iterator it = todosAutodromos.begin();

	while (it != todosAutodromos.end()) {
		os << "\t" << (*it)->autodromoToString() << endl;
		it++;
	}
	return os.str();
}

bool Jogo::apagaCarro(char id)
{
	return dvg.apagaCarro(id);
}

bool Jogo::apagaPiloto(std::string nome)
{
	return dvg.apagaPiloto(nome);
}

bool Jogo::apagaAutodromo(std::string nome)
{
	vector<Autodromo*>::iterator it = todosAutodromos.begin();
	while (it != todosAutodromos.end()) {
		if ((*it)->obtemNome() == nome) {
			delete (*it);
			return true;
		}
		it++;
	}
	return false;
}

bool Jogo::entraNoCarro(char idCarro, std::string nomePiloto)
{
	return dvg.associaCarroPiloto(idCarro,nomePiloto);
}

bool Jogo::saiDoCarro(char idCarro)
{
	return dvg.removePilotoCarro(idCarro);
}

std::string Jogo::lista()
{
	ostringstream os;
	os << "Carros:" << endl;
	os << dvg.obtemTodosCarros() << endl;
	os << "Pilotos:" << endl;
	os << dvg.obtemTodosPilotos() << endl;
	os << "Equipas:" << endl;
	os << dvg.obtemTodasEquipas() << endl;
	os << "Autodromos:" << endl;
	os << autodromoToString() << endl;

	return os.str();
}

bool Jogo::verificaAutodromo(std::string nomeA) const
{
	Autodromo * tmp = obtemAutodromo(nomeA);
	if (tmp != nullptr)
		return true;
	else
		return false;
}

bool Jogo::campeonato(vector<string> nomesAutodromoIn)
{
	if (camp == nullptr) {
		cout << "A criar um campeonato!" << endl;
		for (int i = 0; i < nomesAutodromoIn.size(); i++) {
			//cout << "A verificar o nome:" << nomesAutodromoIn.at(i) << endl;
			if (!verificaAutodromo(nomesAutodromoIn.at(i))) {
				nomesAutodromoIn.erase(nomesAutodromoIn.begin() + i);
				i--;
				continue;
			}
		}

		if (nomesAutodromoIn.empty()) {
			cout << "Nao tenho nenhum autodromo legitimo para criar um campeonato!" << endl;
			return false;
		}
			
		//final:
		cout << "\n\nFinal:" << endl;
		for (int i = 0; i < nomesAutodromoIn.size(); i++)
			cout << "\tNome:" << nomesAutodromoIn.at(i) << endl;

		//incia o campeonato com o vector de todos os autdromos validos neste campeonato
		vector<Autodromo*> autodromosCampeonato;
		for (int i = 0; i < nomesAutodromoIn.size(); i++) {
			autodromosCampeonato.push_back(obtemAutodromo(nomesAutodromoIn.at(i)));
		}

		//if (autodromosCampeonato.size() == nomesAutodromoIn.size())
			//cout << "Tenho o vetor de ponteiros com os " << autodromosCampeonato.size() << " autodromos" << endl;

		camp = new Campeonato("local");
		camp->carregaAutodromos(autodromosCampeonato);

		return true;
	}
	else {
		cout << "Ja existe um campeonato a decorrer!" << endl;
		return false;
	}
	
}

std::string Jogo::listaCarros() const
{
	Autodromo * autodromoEmCompeticao = camp->obtemAutodromoCompeticao();
	return autodromoEmCompeticao->listaCarrosGaragem();
}

bool Jogo::carregaTudo()
{
	//carrega as baterias todas
	Autodromo * autodromoEmCompeticao = camp->obtemAutodromoCompeticao();
	return autodromoEmCompeticao->carregaBaterias();
}

bool Jogo::insereEquipaAutodromo()
{
	Autodromo * autodromoEmCompeticao = camp->obtemAutodromoCompeticao();
	//insere os carros e pilotos no autodromo onde vai decorrer a proxima corrida
	//cout << "A inserir as equipa na garagem" << endl;
	if (!autodromoEmCompeticao->carregaEquipasGaragem(dvg.carregaEquipas())) {//carro e piloto:
		cout << "Nao existem equipas disponiveis para criar um campeonato, a eliminar" << endl;
		delete camp;
		camp = nullptr;
		return false;
	}
	carregaTudo();//carrega as baterias todas
	
	return true;
}

bool Jogo::corrida()
{
	Autodromo * autoCompeticao;

	autoCompeticao = camp->obtemAutodromoCompeticao();

	if (!autoCompeticao->insereEquipaPista()) {
		cout << "Nao existem pilotos/carros disponiveis para correr, experimente (preparaAutodromo)" << endl;
		return true;
	}

	autoCompeticao->iniciaPista();
	
	return true;
}

bool Jogo::passatempo(int segundos)
{
	if (!camp->passaTempo(segundos))//se a corrida acabar
		camp->proximoAutodromo();
	return true;
}
