#pragma once
#include <string>
#include <vector>
#include "Arbol.h"
#include "Zona.h"
#include "Usuario.h"
using namespace std;



class Sistema_alarma
{private:
	int codigo;
	string cod_acceso;
	string nombre_persona;
	int telefono;
	int z;
	Zona la_zona;
	string identificacion;
	Usuario UsuarioP;
	vector<Usuario>UsuariosS;
	vector<Zona>zonas;
	string disponible;


public:
	Sistema_alarma();
	int Menu();
};

