#include "pch.h"
#include "Monitoreo.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

/*Supuestamente la pagina se tiene que actualizar al apretar cierto comando,
lo que se me ocurre es que siempre que se ingrese al comando de monitoreo el programa cargue automaticamente la lista.
Le colocamos un switch al puro inicio, si el swicth esta encendido quiere decir que el programa se reinicio para refrescar la lista.
Si el interruptor switch esta apagado quiere decir que el programa de monitoreo se esta iniciando normalmente*/

Monitoreo::Monitoreo()
{
}


Monitoreo::~Monitoreo()
{
}

void Monitoreo::Menu()
{
	string opcion;
	while (true)
	{
		cout << "1. Monitorear" << endl;//Salida del comando que se desee ingresar
		cout << "2. Establecer usuarios" << endl;
		cout << "3. Ayuda" << endl;
		cout << "4. Acerca de" << endl;
		cout << "0. Fin" << endl;
		cout << setw(10) << "F.FUEGO" << setw(10) << "A.AYUDA" << setw(11) << "P.PANICO" << endl;
		getline(cin, opcion);

	}
}
