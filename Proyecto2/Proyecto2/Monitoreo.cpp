#include "pch.h"
#include "Monitoreo.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;



Monitoreo::Monitoreo()
{
}


Monitoreo::~Monitoreo()
{
}


struct CS
{
	int codigo;
	string codigoAcceso;
	string NombreUsuario;
	int telefono;
};

struct Alarma
{
	string CP;
	vector<CS>codigosSecundarios;
	int zonas;
};

void Monitoreo::Monitorear()
{

}

void Monitoreo::Establecer_Usuarios()
{

}


void Monitoreo::Menu()
{
	string opcion;
	while (true)
	{
		cout << "1. Monitorear" << endl;//Salida del comando que se desee ingresar
		cout << "2. Establecer usuarios" << endl;
		cout << "3. Eliminar usuarios" << endl;
		cout << "4. Ayuda" << endl;
		cout << "5. Acerca de" << endl;
		cout << "0. Fin" << endl;
		
		getline(cin, opcion);

	}
}
