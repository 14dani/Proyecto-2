#include "pch.h"
#include "Sistema_alarma.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

Sistema_alarma::Sistema_alarma()
{
}

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

struct S_A
{
	string identificacion;
	string codigo_principal;
	vector<U_secundario>UsuariosS;
	vector<zona>zonas;

};
vector<S_A>usuarios;

void readFile()//Lee usuarios establecidos, todavia me hace falta volver a cargarlo
{
	fstream my_file;

	string registro;

	my_file.open("Usuarios.txt", ios::in);

	if (my_file.fail())
	{

		cout << endl << "Archivo no existente" << endl << endl;

	}
	else
	{
		while (!my_file.eof())
		{

			getline(my_file, registro);
			cout << registro << endl;

		}

		if (my_file.eof())
			cout << endl;
	}
}



void Sistema_alarma::Menu()
{
	string opcion;
	while (true)
	{
		cout << "1. Armar sistema" << endl;//Salida del comando que se desee ingresar
		cout << "2. Desarmar sistema" << endl;
		cout << "3. Desactivar sistema" << endl;
		cout << "4. Programa zonas" << endl;
		cout << "5. Lista de zonas" << endl;
		cout << "6. Bitacora" << endl;
		cout << "7. Borrar bitacora" << endl;
		cout << "8. Establecer codigo de acceso principal" << endl;
		cout << "9. Establecer codigos de acceso secundarios" << endl;
		cout << "0. Fin" << endl;
		cout << setw(10) << "F.FUEGO" << setw(10) << "A.AYUDA" << setw(11) << "P.PANICO" << endl;
		getline(cin, opcion);





	}
}