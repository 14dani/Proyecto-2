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

void imprimir_vector(vector<string> x)
{
	for (int i = 0; i<int(x.size()); i++)
		cout << endl << " x " << x[i];
}

void lineasf()//Funcion para guardar las lineas en el vector.
{
	fstream monitoreo;
	string linea;
	monitoreo.open("monitoreo.txt", ios::in);/////Recordar cambiar a nombre del archivo real.
	cin.ignore();
	lineas.clear();
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

int imprimir_lineas(int tanda, int contador)//Funcion para imprimir lineas(de 15 en 15), el switch es para indicar la tanda de lineas que se esta buscando imprimir.
{
	int indice_min = (tanda - 1) * 15;
	int indice_max = indice_min + 14;
	int tope;
	string descripcion;
	string accion;
	int sw = 0;
	int sw2 = 0;
	vector<string> elementos;

	if (indice_max > int(lineas.size()) - 1)tope = int(lineas.size()) - 1;
	else tope = indice_max;

	for (int i = indice_min; i <= tope; i++)
	{
		descripcion = "";
		accion = "";
			elementos = dividir_string(lineas[i]);
			for (int j = 0; j < int(elementos.size()); j++) {
				if (elementos[j] == "." || sw == 1)
				{
					sw = 1;
					if (elementos[j] == "..") {
						sw = 0; sw2 = 1;
					}
					if (elementos[j] != "." && sw==1)
					{
						if (elementos[j] == "&") { descripcion = "none"; }
						else { descripcion +=(" "+ elementos[j]); }
					}

				}
				if (sw2 == 1)
				{
					if (elementos[j] == "...")sw2 = 0;
					if (elementos[j] != ".." && sw2 == 1) {
						if (elementos[j] == "&") { accion = "none"; }
						else { accion +=(" "+ elementos[j]); }
					}
				}
			}
			if (elementos[elementos.size() - 1] == "1")
			{
				cout << contador << "-" << elementos[1] << setw(10) << elementos[2] << setw(13) << elementos[3] <<"    " << elementos[4];
				cout <<setw(10)<< elementos[5] << setw(10) << descripcion << setw(10) << accion << endl;
				contador++;
			}

	}return contador;
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
			if (i >= 9)
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

int Monitorear()
{
	string comando = "enter";
	int contador = 1;
	int contador2=1;
	lineasf();
	int variable;

	while (comando != "f")
	{
		if (comando == "enter") {
			variable = contador * 15 - int(lineas.size());
			if (15 <= variable)
			{
				cout << endl << "No hay mas datos." << endl<<endl;
			}
			else {
				contador2=imprimir_lineas(contador, contador2);
				contador++;
			}
		}
		else if (comando == "A")
		{
			return(Monitorear());
		}
		cout << ": ";
		getline(cin, comando);
	}cout << endl; return NULL;
}


void SaveFile()//Archivo para guardar usuarios
{
	fstream my_file;

	my_file.open("Usuarios.txt", ios::out);

	if (!my_file.is_open())
		cout << "Error al abrir archivo" << endl;
	else
	{
		for (unsigned int mats = 0; mats < users.size(); mats++)
		{
			my_file << endl;

			my_file << users.at(mats).identificacion << endl;
			my_file << users.at(mats).nombre << endl;
			my_file << users.at(mats).tipo_propiedad << endl;
			my_file << users.at(mats).direccion << endl;
			my_file << users.at(mats).tel_1 << endl;
			my_file << users.at(mats).tel_2 << endl;
			my_file << users.at(mats).correo << endl;

		}
		my_file.close();
	}

}

void CrearUsuario(string usu)
{
	Usuario us;
	string nom, propiedad, dir, correo1;
	int t1, t2;
	us.identificacion = usu;
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
	cin.ignore();
	getline(cin, correo1);
	us.correo = correo1;

	users.push_back(us);
	SaveFile();
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
			
			CrearUsuario(pusuario);
		}
		else
		{
			if (RecorrenUsuarios(pusuario))
			{
				for (int i = 0; i < users.size(); i++)
				{
					if (pusuario == users.at(i).identificacion)
					{
						cout << "Nombre: " << users.at(i).nombre << endl;
						cout << "Tipo de propiedad: " << users.at(i).tipo_propiedad << endl;
						cout << "Direccion: " << users.at(i).direccion << endl;
						cout << "Telefono 1: " << users.at(i).tel_1 << endl;
						cout << "Telefono 2: " << users.at(i).tel_2 << endl;
						cout << "Correo: " << users.at(i).correo << endl;
					}
				}
			}
			else
			{
				CrearUsuario(pusuario);
			}
		}
	}
	else
		cout << "Identificación debe tener 10 o mas caracteres" << endl;

}





void Monitoreo::Menu()
{
	int opcion;
	while(true)
	{
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
		
		if (opcion == 1)
		{
			Monitorear();
		}
		if(opcion == 2)
		{
			cout << "Ingrese usuario: ";
			getline(cin, U);
			cout << endl;
			Establecer_Usuarios(U);
			cout << endl;
		}
		
	} 

	
}
