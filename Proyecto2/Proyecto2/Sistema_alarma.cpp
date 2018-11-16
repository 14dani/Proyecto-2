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

Sistema_alarma::Sistema_alarma(string iden,string c_p, vector<U_secundario>U2,vector<zona>z)
{
	identificacion = iden;
	codigo_principal = c_p;
	UsuariosS = U2;
	zonas = z;
}

Sistema_alarma::~Sistema_alarma()
{
}





vector<Sistema_alarma>usuarios;




Sistema_alarma Sistema(string id, string cod_prin, vector<U_secundario>US, vector<zona>zonas)
{
	Sistema_alarma sa(id, cod_prin, US, zonas);
	return sa;
}



vector<string> Scmd(string string1) //Separa el string cuando se ingresan los comandos cuando encuentra espacios o comas
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

vector<string>registro1;
vector<string>NOidentificaciones;
vector<string>identificaciones;
vector<string>identificaciones1;

void ExtrarID(string str1) //Extrae cada identificacion
{
	identificaciones = Scmd(str1);
	identificaciones1.push_back(identificaciones[0]);
}

void readFile()//Lee usuarios establecidos, todavia me hace falta volver a cargarlo
{
	ifstream my_file;
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
			registro1.clear();
			getline(my_file, registro);
			registro1.push_back(registro);
			
			for (int i = 0; i < registro1.size(); i++)
			{
				NOidentificaciones.push_back(registro1[i]);
				
			}

					
		}

		if (my_file.eof())
		{
			cout << endl;
		}
	}

	
}

void Ids()//Funcion que extrae las identificaciones del archivo
{
	
	for (int i = 0; i < NOidentificaciones.size()-1; i++)
	{
		
		ExtrarID(NOidentificaciones[i]);
	}
	
}




void Sistema_alarma::Menu()
{
	string opcion;
	readFile();
	Ids();
	/*
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





	}*/
}