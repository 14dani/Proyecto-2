#pragma once
#include <string>
#include <vector>
#include "Arbol.h"
using namespace std;

struct U_secundario
{
	int codigo;
	string cod_acceso;
	string nombre_persona;
	int telefono;
};
struct zona
{
	int z;
	string descrpcion;
	string dispositivo;
};

class Sistema_alarma
{
	string identificacion;
	string codigo_principal;
	vector<U_secundario>UsuariosS;
	vector<zona>zonas;

public:
	Sistema_alarma();
	Sistema_alarma(string, string, vector<U_secundario>, vector<zona>);
	~Sistema_alarma();
	void Menu();
};

