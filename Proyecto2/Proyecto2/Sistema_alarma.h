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


public:
	Sistema_alarma();
	Sistema_alarma(string, Usuario, vector<Usuario>, vector<Zona>, string);
	Sistema_alarma(string,string);
	
	void ExtraerInfo(string);
	bool RecorrerIden(string);
	void Archivo_usuario_SA();
	void ExtraerInfoSecciones(string);
	void armar_sistema();
	void desarmar_sistema();
	void desactivar_sistema();
	void programar_zonas();
	void lista_zonas();
	void bitacora();
	void borrar_bitacora();
	void establecer_CAP();
	void establecer_CAS();


	int Menu();
};

