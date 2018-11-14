#include "pch.h"
#include "Monitoreo.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;
vector<string> lineas; /*guarda las lineas del archivo de monitoreo para que se pueda cerrar el archivo de registros inmediatamente
					   , asi el sistema de alarma puede seguir enviando alertas mientras el sistema de monitoreo esta encendido*/

void lineasf()//Funcion para guardar las lineas en el vector.
{
	fstream monitoreo;
	string linea;
	monitoreo.open("monitoreo.txt", ios::in);/////Recordar cambiar a nombre del archivo real.
	cin.ignore();
	while (!monitoreo.eof())
	{
		getline(monitoreo, linea);

		lineas.push_back(linea);

	}
	monitoreo.close();
}

vector<string> dividir_string(string string1)//Divide string separado  por espacios
{
	vector<string> space;


	istringstream iss(string1);

	string token;

	while (getline(iss, token, ' '))
	{

		space.push_back(token);

	}
	return space;
}

void imprimir_lineas(int tanda)//Funcion para imprimir lineas(de 15 en 15), el switch es para indicar la tanda de lineas que se esta buscando imprimir.
{
	int indice_min = (tanda-1) * 15;
	int indice_max = indice_min + 14;
	int tope;
	string descripcion = "";
	string accion = "";
	int sw = 0;
	int sw2 = 0;
	vector<string> elementos;
	int contador = 1;

	if (indice_max > lineas.size() - 1)tope = lineas.size() - 1;
	else tope = indice_max;

	for (int i = indice_min; i <= tope; i++)
	{
			elementos = dividir_string(lineas[i]);
			for (int j = 0; j < elementos.size(); j++) {
				if (elementos[i] == "." || sw == 1)
				{
					sw = 1;
					if (elementos[i] == "..") {
						sw = 0; sw2 = 1;
					}
					if (elementos[i] != "." && sw==1)
					{
						descripcion += elementos[i];
					}

				}
				if (sw2 == 1)
				{
					if (elementos[1] == "...")sw2 = 0;
					if (elementos[i]!=".." && sw2 == 1)accion += elementos[i];
				}
			}
			if (elementos[elementos.size() - 1] == "1")
			{
				cout << contador << "-" << setw(1) << elementos[1] << setw(3) << elementos[2] << setw(3) << elementos[3] << setw(3) << elementos[4] << setw(3);
				cout << elementos[5] << setw(3) << descripcion << setw(3) << accion << endl;
			}

	}
}


Monitoreo::Monitoreo()
{
}

struct Usuario   //estructura para establecer el usuario
{
	string identificacion;
	string nombre;
	string tipo_propiedad;
	string direccion;
	int tel_1;
	int tel_2;
	string correo;

};

vector<Usuario>users;//vector para guardar los usuarios establecidos

bool RecorrenUsuarios(string usuario)
{
	bool f = false;
	{
		for (int i = 0; i < users.size(); i++)
		{
			if (users.at(i).identificacion == usuario)
			{
				f = true;
			}
		}
	}
	return f;
}

bool caracteres(string user) //verifica que la identificacion sea de 10 o m�s caracteres
{
	bool f = false;
	{
		for (int i = 0; i < user.length(); i++)
		{
			if (i >= 10)
			{
				f = true;
			}
		}
	}
	return f;
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

void Monitorear()
{

}

void Monitoreo::Establecer_Usuarios(string pusuario)
{
	if (caracteres(pusuario))
	{
		cout << "Yes" << endl;
	}
	else
		cout << "Identificaci�n debe tener 10 o m�s caracteres" << endl;

}



void Monitoreo::Menu()
{
	int opcion;
	do {
		cout << "MENU" << endl;
		cout << "1. Monitorear" << endl;//Salida del comando que se desee ingresar
		cout << "2. Establecer usuarios" << endl;
		cout << "3. Ayuda" << endl;
		cout << "4. Acerca de" << endl;
		cout << "0. Fin" << endl;
		cout << "Opcion :";
		cin >> opcion;
		cout << endl;
		string U;
		
		switch (opcion)
		{
		case 1:
			lineasf();
			break;
		case 2:
			cout << "Ingrese usuario: ";
			cin.ignore();
			getline(cin, U);
			Establecer_Usuarios(U);
			cout << endl;
			break;
		case 3:
		
			break;
		case 4:
			break;
		
		
		//case 0:
			//break;
		}
	} while (opcion > 4&&opcion >0);

	
}
