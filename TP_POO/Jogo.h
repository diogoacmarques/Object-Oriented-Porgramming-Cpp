#pragma once
#include "DVG.h"
#include "Autodromo.h"
#include <vector>
class Jogo
{
	DVG d;
	std::vector <Autodromo*> todosAutodromos;
public:
	Jogo();
	~Jogo();
};

