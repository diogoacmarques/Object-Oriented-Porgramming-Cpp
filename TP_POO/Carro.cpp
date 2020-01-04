#include "Carro.h"
#include "Pista.h"
#include <iostream>
#include <sstream>

using namespace std;

char Carro::idStatic = 'a';//inicializar o 'cont'

Carro::Carro(int velMax,int capInicial, int capMax, string marca, string modelo):velcidadeMaxima(velMax),mAh(capInicial), capcidadeMaxima(capMax),marca(marca),modelo(modelo),
id(idStatic++), piloto(nullptr),emCompeticao(false), pontuacao(0),linhaPista(0)
{
	if (idStatic < 'a' || idStatic > 'z')
		idStatic = '?';
	cout << "\tConstrutor_Carro:" << marca << "," << modelo << "(" << mAh << "/" << capcidadeMaxima << ")\n" << endl;
}

Carro::~Carro()
{
	cout << "Destrutor_Carro(" << marca << "/" << modelo << ")" << endl;
	if (verificaPiloto()) {//tem piloto
		piloto->removeCarro();
	}
}

bool Carro::verificaDano() const
{
	if (danoIrreparavel) {
		//cout << "O carro esta danificado!" << endl;
		return true;
	}
	return false;
}

bool Carro::verificaEmergencia() const
{
	return sinalEmergencia;
}

int Carro::obtemBateriaMax() const
{
	return capcidadeMaxima;
}

int Carro::carregaBateria(int n)
{
	if (verificaDano())
		return false;

	if (n > 0 && metroSegundo == 0) {// e positivo e esta parado
		if (mAh + n <= capcidadeMaxima) {//nivel da bateria + n < capacidade maxima
			mAh += n;
		}
		else {
			mAh = capcidadeMaxima;
			cout << "O carro " << id << " foi carregado completamente " << mAh << "mAh/" << capcidadeMaxima << endl;
		}	
	}
	else {
		cout << "O carro esta em movimento ou o valor nao e valido" << endl;
	}

	return 0;
}

bool Carro::carregamentoTotal()
{
	if (verificaDano())
		return false;

	mAh = capcidadeMaxima;
	return true;
}

char Carro::obtemId() const
{
	return id;
}

int Carro::obtemVelMax() const
{
	return velcidadeMaxima;
}

void Carro::ativaSinalEmergencia()
{
	sinalEmergencia = true;
	return;
}

void Carro::danificaCarro()
{
	danoIrreparavel = true;
	return;
}

std::string Carro::infoCompeticao() const
{
	ostringstream os;
	os << "Carro[" << id << "]:" << marca << "," << modelo << "(" << mAh << "/" << capcidadeMaxima << ")->" << metroSegundo << "m/s (" 
		<< piloto->obtemNome() << "/" << piloto->obtemTipo() << ")" ;
	if (verificaDano())
		os << "(danificado)";
	if (sinalEmergencia)
		os << "(Sinal Emergencia)";
	if(mAh == 0)
		os << "(sem bateria)";
	return os.str();
}

bool Carro::adicionaPontuacao(int pontos)
{
	pontuacao += pontos;
	return true;
}

int Carro::obtemPontuacao() const
{
	return pontuacao;
}

bool Carro::resetPontuacao()
{
	pontuacao = 0;
	return true;
}

bool Carro::verificaPiloto() const
{
	if (piloto == nullptr)
		return false;
	else
		return true;
}

bool Carro::adicionaPiloto(Piloto * p)
{
	if (!verificaDano()){
		piloto = p;
		return true;
	}
	else
		return false;
	
	
}

bool Carro::removePiloto()
{
	if (verificaDano())
		return false;

	piloto = nullptr;
	return true;
}

bool Carro::decisaoPiloto(Pista * p)
{
	if (verificaDano())
		return false;

	piloto->tomaDecisao(this, p);
	return passaSegundo();

}

std::string Carro::obtemNomePiloto() const
{
	return piloto->obtemNome();
}

bool Carro::verificaAptidao() const
{
	if (danoIrreparavel || emCompeticao || sinalEmergencia)
		return false;
	else
		return true;
}

bool Carro::verificaCompeticao() const
{
	return emCompeticao;
}

bool Carro::iniciaCompeticao(int linha)
{
	if (verificaDano())
		return false;

	sinalEmergencia = false;
	linhaPista = linha;
	emCompeticao = true;
	return true;
}

bool Carro::fimCompeticao()
{
	emCompeticao = false;
	sinalEmergencia = false;
	return true;
}

int Carro::obtemLinhaPista() const
{
	return linhaPista;
}

bool Carro::entraNaGaragem()
{
	fimCompeticao();
	mPercorrido = 0;
	metroSegundo = 0;
	linhaPista = 0;
	return true;
}

int Carro::obtemVelocidade() const
{
	return metroSegundo;
}

bool Carro::acelera()
{
	if (verificaDano() || sinalEmergencia)
		return false;

	metroSegundo++;
	return true;
}

bool Carro::trava()
{
	if (verificaDano())
		return false;

	if (metroSegundo > 0)
		metroSegundo--;
	else
		metroSegundo = 0;
	
	return true;
}

int Carro::obtemDistanciaPercorrida() const
{
	return mPercorrido;
}

bool Carro::passaSegundo()
{
	if (verificaDano())
		return false;

	if (sinalEmergencia) {
		trava();
		trava();
		trava();
	}

	if (metroSegundo > 0) {//se esta a andar
		if (mAh >= metroSegundo) {//se tem energia para fazer a distancia
			mAh -= metroSegundo;
			//cout << marca << " perdeu " << metroSegundo << " de energia e tem agora " << mAh << endl;
		}
		else {//nao tem energia
			//cout << marca << " nao tem energia" << endl;
			mAh = 0;
			metroSegundo = 0;
			return false;
		}	
		mPercorrido += metroSegundo;
	}

	return true;
}

bool Carro::resetDistancia()
{
	mPercorrido = 0;
	return true;
}

std::string Carro::carroToString() const
{
	ostringstream os;
	os << "carro[" << id << "]:" << marca << "(" << modelo << ") com bateria " << mAh << "/" << capcidadeMaxima << " e velocidade maxima de " << velcidadeMaxima;
	if (verificaPiloto())
		os << " tem piloto " << piloto->obtemNome();

	/*if (movimento)
		os << " a andar " << metrosegundo << " mts/seg (" << mpercorrido << "metros total)";
*/
	return os.str();
}

int Carro::obtemBateriaAtual() const
{
	return mAh;
}

