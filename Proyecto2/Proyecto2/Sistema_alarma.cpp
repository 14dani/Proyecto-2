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



Sistema_alarma::~Sistema_alarma()
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

vector<S_A>usuarios; //Vector donde se guaradaran los usuarios


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
vector<string>identificaciones1;//Se guardan identificaciones

void ExtraerInfo(string str1) //Extrae cada identificacion
{
	S_A s;
	identificaciones = Scmd(str1);
	identificaciones1.push_back(identificaciones[0]);
	s.identificacion = identificaciones[0];
	usuarios.push_back(s);
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
		
		ExtraerInfo(NOidentificaciones[i]);
	}
}

bool RecorrerIden(string usuario)
{
	bool f = false;
	{
		for (int i = 0; i < identificaciones1.size(); i++)
		{
			if (identificaciones1[i] == usuario)
			{
				f = true;
			}
		}
	}
	return f;
}


void armar_sistema()
{
	string id;
	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		cout << "H" << endl;
	}
	else cout << "Usuario no registrado" << endl;
}

void desarmar_sistema()
{
	string id;
	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		cout << "H" << endl;
	}
	else cout << "Usuario no registrado" << endl;
}

void desactivar_sistema()
{
	string id;
	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		cout << "H" << endl;
	}
	else cout << "Usuario no registrado" << endl;
}

void programar_zonas() //Me falta terminar esta
{
	S_A sa;
	zona zo;
	vector<zona>zv;
	string id,des,dis;
	int num;

	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		for (int i = 0; i < usuarios.size(); i++)
		{
			if (id == usuarios.at(i).identificacion)
			{
				cout << "Numero de zona: ";
				cin >> num;
				for (int m = 0; m < usuarios[i].zonas.size(); m++)
				{
					if (num == usuarios[i].zonas[m].z)
					{
						cout << "Numero de zona: " << usuarios[i].zonas[m].z << endl;
						cout << "Descripcion: " << usuarios[i].zonas[m].descrpcion << endl;
						cout << "Dispositivo instalado en la zona: " << usuarios[i].zonas[m].dispositivo << endl;
					}
					else
					{
						cout << "Numero de zona no registrado" << endl;
						cout << "Ingrese numero de zona: ";
						cin >> num;
						zo.z = num;
						cout << "Ingrese descripcion: ";
						getline(cin, des);
						zo.descrpcion = des;
						cout << "Dispositivo que se va a instalar: ";
						getline(cin, dis);
						zo.dispositivo = dis;
						zv.push_back(zo);
						sa.zonas = zv;
					}
				}
			}
			else cout << "Usuario no registrado" << endl;
		}
		

	}
	else cout << "Usuario no registrado" << endl;
}

void lista_zonas()
{
	string id;
	S_A sa;
	zona zo;

	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		cout << setw(20) << "Zona" << setw(20) << "Descripcion" << setw(20) << "Dispositivo" << endl;
		cout << setw(62) << "================================================" << endl;
	}
	else cout << "Usuario no registrado" << endl;
}

void bitacora()
{
	string id;
	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		cout << "H" << endl;
	}
	else cout << "Usuario no registrado" << endl;
}

void borrar_bitacora()
{
	string id;
	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		cout << "H" << endl;
	}
	else cout << "Usuario no registrado" << endl;
}

void establecer_CAP()
{
	string id;
	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		cout << "H" << endl;
	}
	else cout << "Usuario no registrado" << endl;
}

void establecer_CAS()
{
	string id;
	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		cout << "H" << endl;
	}
	else cout << "Usuario no registrado" << endl;
}

void Fuego()
{

}

void ayuda()
{

}

void panico()
{

}
void Sistema_alarma::Menu()
{
	string opcion;
	readFile(); 
	Ids(); //se cargan las identidades del monitoreo.cpp
	
	
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
		cout << "10. Centro de ayuda" << endl;
		cout << "11. Acerca De" << endl;
		cout << "0. Fin" << endl;
		cout << setw(10) << "F.FUEGO" << setw(10) << "A.AYUDA" << setw(11) << "P.PANICO" << endl;
		cout << "Opcion: ";
		getline(cin, opcion);
		cout << endl;

		if (opcion == "0")break;
		else if (opcion == "1")armar_sistema();
		else if (opcion == "2")desarmar_sistema;
		else if (opcion == "3")desactivar_sistema();
		else if (opcion == "4")programar_zonas();
		else if (opcion == "5")lista_zonas();
		else if (opcion == "6")bitacora();
		else if (opcion == "7")borrar_bitacora();
		else if (opcion == "8")establecer_CAP();
		else if (opcion == "9")establecer_CAS();
		//else if (opcion == "10")armar_sistema();
		//else if (opcion == "11")armar_sistema();
		
		
	}
}