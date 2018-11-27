#pragma once
#include <string>
#include <vector>
#include "Arbol.h"
#include "Zona.h"
#include "Usuario.h"
using namespace std;



class Sistema_alarma
{
private:
	string identificacion;
	Usuario UsuarioP;
	vector<Usuario>UsuariosS;
	vector<Zona>zonas;
	string disponible;
	string nombre;
	int numero;
	int carnet;
	vector<int> zonas;
	int codigo;
public:
	Sistema_alarma(string, Usuario, vector<Usuario>, vector<Zona>, string);
	void ExtraerInfo(string);
	bool RecorrerIden(string);
	void Archivo_usuario_SA();
	void ExtraerInfoSecciones(string);
	void armar_sistema();
	void desarmar_sistema();
	void desactivar_sistema();
	void programar_zonas();
	void lista_zonas();
	void establecer_CAP();
	void establecer_CAS();


	int Menu();
};

