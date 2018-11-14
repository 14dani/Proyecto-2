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

bool caracteres(string user) //verifica que la identificacion sea de 10 o más caracteres
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

void Monitoreo::Monitorear()
{

}

void Monitoreo::Establecer_Usuarios(string pusuario)
{
	Usuario us;
	string nom, propiedad, dir, correo1;
	int t1, t2;

	if (caracteres(pusuario))
	{
		if (users.size() == 0)
		{
			us.identificacion = pusuario;
			cout << "Nombre y apellidos: ";
			getline(cin, nom);
			us.nombre = nom;

			cout << "Tipo de propiedad donde desea instalar el sistema de alarma: ";
			getline(cin, propiedad);
			us.tipo_propiedad = propiedad;

			cout << "Direccion de propiedad: ";
			getline(cin, dir);
			us.direccion = dir;

			cout << "Telefono 1: ";
			cin >> t1;
			us.tel_1 = t1;

			cout << "Telefono 2: ";
			cin >> t2;
			us.tel_2 = t2;

			cout << "Correo electronico: ";
			getline(cin, correo1);
			us.correo = correo1;

			users.push_back(us);

		}
		else
		{
			if (RecorrenUsuarios(pusuario))
			{
				cout << "Usuario ya registrado" << endl;
			}
			else
			{

			}
		}
	}
	else
		cout << "Identificación debe tener 10 o más caracteres" << endl;

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
