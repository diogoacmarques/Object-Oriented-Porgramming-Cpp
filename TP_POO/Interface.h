#pragma once
#include <string>
class Interface
{
	std::string nome;
	int modo;
public:
	Interface(std::string n = "default");
	~Interface();

	//funcionalidades
	bool start();
	bool getCommand();
	std::string splitLine(std::string str);

	bool readFile(std::string fileName);
	bool func();
};

