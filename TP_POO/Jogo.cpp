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
			criaPiloto(tipo, nome);
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
	int capI, capM;

	size_t pos;

	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			//marca = "", modelo = "";//reset
			marca.erase(), modelo.erase();//reset
			capI = -1, capM = -1, pos = 0;

			cout << "Linha:" << line << endl;

			//Capacidade Inicial
			pos = line.find_first_of(" ");
			capI = stoi(line.substr(0, pos));
			line.erase(0, pos + 1);
		

			//Capacidade Maxima
			pos = line.find_first_of(" ");
			capM = stoi(line.substr(0, pos));
			line.erase(0, pos + 1);

			//Marca
			pos = line.find_first_of(" ");
			marca = line.substr(0, pos);
			line.erase(0, pos + 1);

			if (pos != -1) {
				modelo = line;	
			}
			
			//cout << "\tCarro:" << marca << "," << modelo << "(" << capI << "/" << capM << ")\n" << endl;
			criaCarro(capI, capM,marca,modelo);
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

			//Numero máximo de carros
			pos = line.find_first_of(" ");
			n = stoi(line.substr(0, pos));
			line.erase(0, pos + 1);

			pos = line.find_first_of(" ");
			comprimento = stoi(line.substr(0, pos));
			line.erase(0, pos + 1);
			
			nome = line;

			cout << "\tAutodromo[" << n << "]:" << nome << "(" << comprimento << " metros)\n" << endl;
			criaAutodromo(n, comprimento, nome);
		}
		myfile.close();
		return true;
	}
	else cout << "Erro na leitura do fichero:'" << fileName << "'" << endl;

	return false;
}

bool Jogo::criaCarro(int capMaxima, int capInicial, std::string marca, std::string modelo)
{
	return dvg.criaCarro(capMaxima, capInicial, marca, modelo);
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

		//incia o campeonato com o vecto de todos os autdromos neste campeonato
		vector<Autodromo*> autodromosCampeonato;
		for (int i = 0; i < nomesAutodromoIn.size(); i++) {
			autodromosCampeonato.push_back(obtemAutodromo(nomesAutodromoIn.at(i)));
		}

		if (autodromosCampeonato.size() == nomesAutodromoIn.size())
			cout << "Tenho o vetor de ponteiros com os " << autodromosCampeonato.size() << " autodromos" << endl;

		cout << "Devia ter os pilotos/carros associados a este ponto?(acho que sim)" << endl;

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
	return dvg.obtemTodosCarros();
}

bool Jogo::carregaTudo()
{
	return dvg.carregaTodosCarros();
}

bool Jogo::corrida()
{
	Autodromo * autoCompeticao;
	//insere os carros e pilotos no autodromo onde vai decorrer a proxima corrida
	camp->proximoAutodromo();

	autoCompeticao = camp->obtemAutodromoCompeticao();

	autoCompeticao->carregaCarros(dvg.obtemVectorCarros());
	autoCompeticao->carregaPilotos(dvg.obtemVectorPilotos());

	if (!autoCompeticao->inserePilotosPista()) {
		cout << "Nao existem pilotos/carros disponiveis para correr, logo vou acabar o campeonato" << endl;
		delete camp;
		camp = nullptr;
		return false;
	}

	autoCompeticao->iniciaPista();
	
	return true;
}

bool Jogo::passatempo(int segundos)
{
	return camp->passaTempo(segundos);
}
