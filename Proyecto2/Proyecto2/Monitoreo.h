#pragma once
#include <string>
using namespace std;
class Monitoreo
{
public:
	Monitoreo();
	void Monitorear();
	void Establecer_Usuarios(string);
	void Menu();
	friend class Sistema_alarma;

};

