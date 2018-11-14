#include "pch.h"
#include "Monitoreo.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;
vector<string> lineas; /*guarda las lineas del archivo de monitoreo para que se pueda cerrar el archivo de registros inmediatamente
					   , asi el sistema de alarma puede seguir enviando alertas mientras el sistema de monitoreo esta encendido*/


/*Supuestamente la pagina se tiene que actualizar al apretar cierto comando,
lo que se me ocurre es que siempre que se ingrese al comando de monitoreo el programa cargue automaticamente la lista.
Le colocamos un switch al puro inicio, si el swicth esta encendido quiere decir que el programa se reinicio para refrescar la lista.
Si el interruptor switch esta apagado quiere decir que el programa de monitoreo se esta iniciando normalmente*/

Monitoreo::Monitoreo()
{
}

string Encript(string frase)//Algoritmo de encriptado
{
	string resultado = "";
	int n = 1;
	for (int tamano = 0; tamano < frase.size(); tamano++)
	{
		char letra = frase[tamano] - n;
		resultado += letra;
		n++;
		if (n > 10)
		{
			n = 1;
		}
	}
	return resultado;
}

string Desencript(string frase)//Algortimo para desencriptar
{
	string resultado = "";
	int n = 1;
	for (int tamano = 0; tamano < frase.size(); tamano++)
	{
		char letra = frase[tamano] - n;
		resultado += letra;
		n++;
		if (n > 10)
		{
			n = 1;
		}
	}return resultado;
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
