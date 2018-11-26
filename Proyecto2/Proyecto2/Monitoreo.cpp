#include "pch.h"
#include "Monitoreo.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Usuario.h"

using namespace std;



Usuario::Usuario(string id, string nom, string des, string dir, int t1, int t2, string co, int e)
{
	identificacion = id;
	nombre = nom;
	tipo_de_propiedad = des;
	direccion = dir;
	telefono1 = t1;
	telefono2 = t2;
	correo = co;
	el = e;

}
Usuario usu;
vector<Usuario>user1;

Usuario Object(string iden, string nomb,string tp,string dir,int tel1,int tel2,string cor,int eli) //Funcion que crea objetos 

{
	Usuario usuario(iden,nomb,tp,dir,tel1,tel2,cor,eli);
	return usuario;
}


vector<string> lineas; /*guarda las lineas del archivo de monitoreo para que se pueda cerrar el archivo de registros inmediatamente
					   , asi el sistema de alarma puede seguir enviando alertas mientras el sistema de monitoreo esta encendido*/
struct datos_de_linea
{
	vector<string> elementos;
	string accion;
	string descripcion;
};
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

void guardar()
{
	fstream monitoreo;
	monitoreo.open("monitoreo.txt", ios::out);
	for (int i=0; i<int(lineas.size()-1);i++)
	{
		monitoreo << lineas[i] << endl;
	}
	monitoreo << lineas[int(lineas.size() - 1)]; //guardar el ultimo
	monitoreo.close();
}/*Esta funcion borra el archivo y guarda las lineas que se encuentran en el vector de lineas, cuidado porque el vector de lineas
 tiene que estar lleno*/

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

datos_de_linea separar_linea(string linea)
{
	string descripcion = "";
	string accion = "";
	int sw = 0;
	int sw2 = 0;
	vector<string> elementos = dividir_string(linea);
	datos_de_linea lineac;

	for (int j = 0; j < int(elementos.size()); j++) {
		if (elementos[j] == "." || sw == 1)
		{
			sw = 1;
			if (elementos[j] == "..") {
				sw = 0; sw2 = 1;
			}
			if (elementos[j] != "." && sw == 1)
			{
				if (elementos[j] == "&") { descripcion = "none"; }
				else { descripcion += (" " + elementos[j]); }
			}

		}
		if (sw2 == 1)
		{
			if (elementos[j] == "...")sw2 = 0;
			if (elementos[j] != ".." && sw2 == 1) {
				if (elementos[j] == "&") { accion = "none"; }
				else { accion += (" " + elementos[j]); }
			}
		}
		lineac.accion = accion;
		lineac.descripcion = descripcion;
		lineac.elementos = elementos;
	}return lineac;
}

vector<int> imprimir_lineas(int indice_min, int contador, int indice_max)//Funcion para imprimir lineas(de 15 en 15), el switch es para indicar la tanda de lineas que se esta buscando imprimir.
{
	int tope;
	vector<string> elementos;
	datos_de_linea datos;
	vector<int> respuesta;

	if (indice_max > int(lineas.size()) - 1)tope = int(lineas.size()) - 1;
	else tope = indice_max;

	for (int i = indice_min; i <= tope; i++)
	{
			datos = separar_linea(lineas[i]);
			elementos = datos.elementos;

			if (elementos[elementos.size() - 1] == "1")
			{
				cout << contador << "-" << elementos[1] << setw(10) << elementos[2] << setw(13) << elementos[3] <<"    " << elementos[4];
				cout <<setw(10)<< elementos[5] << setw(10) << datos.descripcion << setw(10) << datos.accion << endl;
				contador++;
			}
			else { if (tope<int(lineas.size()) - 1)tope++; }
	}
	respuesta.push_back(contador);
	respuesta.push_back(tope + 1); 
	return respuesta;
}

void modificar_accion(int indice_min, int contador, int indice_max)
{
	int linea_deseada;
	int indice_linea;
	int tope;
	string accion_monitoreo;
	vector<string> elementos;
	string linea_con_accion="";
	datos_de_linea datos;

	if (indice_max > int(lineas.size()) - 1)tope = int(lineas.size()) - 1;
	else tope = indice_max;

	cout << endl << "Ingrese la linea deseada:";
	cin >> linea_deseada;
	if (linea_deseada<contador || linea_deseada>contador+14 || linea_deseada>int(lineas.size()-1))
	{
		cout << endl << "linea fuera de monitor" << endl;
	}
	else {
		for (int i = indice_min; i <= tope; i++)
		{
			datos = separar_linea(lineas[i]);
			elementos = datos.elementos;
			if (elementos[elementos.size() - 1] == "1")
			{
				if (contador == linea_deseada)
				{
					if (elementos[4] == "ACTIVACION")
					{
						cout << endl << "Escriba la accion:";
						cin.ignore();
						getline(cin, accion_monitoreo);
						if (accion_monitoreo == "")accion_monitoreo = "none";
						datos.accion = accion_monitoreo;
						indice_linea = i;
						for (int y = 0; y <=5 ; y++)
						{
							linea_con_accion += elementos[y] + " ";
						}
						linea_con_accion +=". "+datos.descripcion+" .. "+datos.accion+" ... "+ elementos[elementos.size() - 1];
						lineas[indice_linea] = linea_con_accion;
						guardar();
						cout << endl << "Listo" << endl;
					}
					else {
						cout << endl << "No es una linea de activacion" << endl;
					}
				}

				contador++;
			}
		}
	}
}



bool Usuario::RecorrenUsuarios(string usuario) //Recorre los usuarios de users
{
	bool f = false;
	{
		for (int i = 0; i < user1.size(); i++)
		{
			if (user1.at(i).identificacion == usuario)
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

bool telefono(string numero) //Valida que el telefono tenga 8 digitos exactos
{
	bool f = false;
	{
		for (int i = 0; i < numero.size(); i++)
		{
			if (i == 7)
			{
				f = true;
			}
		}
	}
	return f;
}

int ToInt(string s) //Funcion que convierte lo telefono en int
{
	stringstream ss(s);
	int x = 0;
	ss >> x;
	return x;
}


int Monitorear()
{
	string comando = "enter";
	int contador=1;
	int indice_minimo=0;
	int sw = 0;
	int tanda = 0;
	vector<int>respuesta;
	
	
	lineasf();

	while (comando != "F")
	{
		if (comando == "enter") {
			if (indice_minimo==(int(lineas.size())))
			{
				cout << endl << "No hay mas datos." << endl<<endl;
				sw = 1;
			}
			else {
				respuesta= imprimir_lineas(indice_minimo, contador, indice_minimo+14);
				contador = respuesta[0];
				indice_minimo = respuesta[1];
				tanda++;
			}
		}
		else if (comando == "A")
		{
			return(Monitorear());
		}
		else if (comando == "#")
		{
			if (sw==1)
			{
				cout<<endl<<"No hay mas datos"<<endl;
			}
			else {
				modificar_accion(((tanda - 1) * 15), ((tanda-1)*15)+1, indice_minimo);
			}
			cin.ignore();
		}
		cout << ": ";
		getline(cin, comando);
	}cout << endl; return NULL;
}

void Usuario::SaveFile()//Archivo para guardar usuarios
{
	fstream my_file;

	my_file.open("Usuarios.txt", ios::out);

	if (!my_file.is_open())
		cout << "Error al abrir archivo" << endl;
	else
	{
		for (unsigned int i = 0; i < user1.size(); i++)
		{
			my_file << user1.at(i).identificacion << "-"
				<< user1.at(i).nombre << "-"
				<< user1.at(i).tipo_de_propiedad << "-"
				<< user1.at(i).direccion << "-"
				<< user1.at(i).telefono1 << "-"
				<< user1.at(i).telefono2 << "-"
				<< user1.at(i).correo << "-"
				<< user1.at(i).el << endl;

		}
		my_file.close();
	}

}


vector<string> ScmdM(string string1) //Separa el string cuando se ingresan los comandos cuando encuentra espacios
{
	vector<string> space;


	istringstream iss(string1);

	string token;

	while (getline(iss, token, '-'))
	{

		space.push_back(token);

	}
	return space;
}

vector<string>registro1m;
vector<string>NOidentificacionesm;
vector<string>identificacionesm;
vector<string>identificaciones1m;//Se guardan identificaciones


void Usuario::ExtraerInfoM(string str1) //Guarda los usuarios en users
{
	Usuario s;
	string m;
	identificacionesm = ScmdM(str1);
	identificaciones1m.push_back(identificacionesm[0]);

	s.identificacion = identificacionesm[0];
	s.nombre = identificacionesm[1];
	s.tipo_de_propiedad = identificacionesm[2];
	s.direccion = identificacionesm[3];
	s.telefono1 = ToInt(identificacionesm[4]);
	s.telefono2 = ToInt(identificacionesm[5]);
	s.correo = identificacionesm[6];
	s.el = ToInt(identificacionesm[7]);
	user1.push_back(s);
}

void readFileM()//Lee usuarios establecidos del monitoreo.cpp
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
			registro1m.clear();
			getline(my_file, registro);
			registro1m.push_back(registro);

			for (int i = 0; i < registro1m.size(); i++)
			{
				NOidentificacionesm.push_back(registro1m[i]);

			}
		}
		if (my_file.eof())
		{
			cout << endl;
		}
	}
}

void IdsM()//Funcion que extrae los atributos de la estructura Usuario para que no se borren
{
	Usuario us2;
	for (int i = 0; i < NOidentificacionesm.size() - 1; i++)
	{
		
		us2.ExtraerInfoM(NOidentificacionesm[i]);
	}

}

void Usuario::CrearUsuario(string usu)
{
	Usuario us;
	string nom, propiedad, dir, correo1,t1,t2;
	
	us.identificacion = usu;
	cout << "Nombre y apellidos: ";
	getline(cin, nom);
	us.nombre = nom;

	cout << "Tipo de propiedad donde desea instalar el sistema de alarma: ";
	getline(cin, propiedad);
	us.tipo_de_propiedad = propiedad;

	cout << "Direccion de propiedad: ";
	getline(cin, dir);
	us.direccion = dir;

	do {
		cout << "Telefono 1: ";
		getline(cin, t1);
		if (telefono(t1))
		{

			us.telefono1 = ToInt(t1);
		}
		else
			cout << "Numero debe tener 8 numeros exactos" << endl;
	} while (telefono(t1) == false);
	
	do {
		cout << "Telefono 2: ";
		getline(cin, t2);
		if (telefono(t2))
		{

			us.telefono2 = ToInt(t2);
		}
		else
			cout << "Numero debe tener 8 numeros exactos" << endl;
	} while (telefono(t2) == false);
	

	cout << "Correo electronico: ";
	//cin.ignore();
	getline(cin, correo1);
	us.correo = correo1;
	us.el = 1;
	user1.push_back(us);
	SaveFile();
}


void Usuario::Establecer_Usuarios(string pusuario)
{
	Usuario us;
	string op,id,nom2,prop2,dir2,correo2,t11,t22;
	

	if (caracteres(pusuario))
	{
		if (user1.size() == 0)
		{
			
			CrearUsuario(pusuario);
		}
		else
		{
			if (RecorrenUsuarios(pusuario))
			{
				for (int i = 0; i < user1.size(); i++)
				{
					if (pusuario == user1.at(i).identificacion) //Desplega informacion cuando ya hay un usuario registrado y da la opcion para realizar cambios
					{
						cout << "Identificacion: " << user1.at(i).identificacion << endl;
						cout << "Nombre completo: " << user1.at(i).nombre << endl;
						cout << "Tipo de propiedad: " << user1.at(i).tipo_de_propiedad << endl;
						cout << "Direccion: " << user1.at(i).direccion << endl;
						cout << "Telefono 1: " << user1.at(i).telefono1 << endl;
						cout << "Telefono 2: " << user1.at(i).telefono2 << endl;
						cout << "Correo: " << user1.at(i).correo << endl;
						cout << "Para cambiar algun dato presione la tecla <C>" << endl;
						cout << "Para salir presione la tecla <S>" << endl;
						string c;
						getline(cin, c);
						if (c == "C" || c == "c")
						{
							while (true)
							{
								cout << "1. Identificacion" << endl;
								cout << "2. Nombre" << endl;
								cout << "3. Tipo de propiedad" << endl;
								cout << "4. Direccion" << endl;
								cout << "5. Telefono 1" << endl;
								cout << "6. Telefono 2" << endl;
								cout << "7. Correo" << endl;
								cout << "S. Salir" << endl;
								cout << "Cambiar: "; getline(cin, op);
								if (op == "1")
								{
									cout << "Identificacion nueva: ";
									getline(cin, id);
									if (caracteres(id))
									{
										user1.at(i).identificacion = id;
									}
									else
										cout << "Identificacion debe tener 10 o mas caracteres" << endl;

								}
								if (op == "2")
								{
									cout << "Nombre nuevo: "; 
									getline(cin, nom2);
									user1.at(i).nombre = nom2;
								}
								if (op == "3")
								{
									cout << "Tipo de propiedad nueva: "; 
									getline(cin, prop2); 
									user1.at(i).tipo_de_propiedad = prop2;
								}
								if (op == "4")
								{
									cout << "Direccion nueva: "; 
									getline(cin, dir2);
									user1.at(i).direccion = dir2;
								}
								if (op == "5") {
									do {
										cout << "Telefono 1 nuevo: "; getline(cin, t11); if (telefono(t11))
										{
											user1.at(i).telefono1 = ToInt(t11);
										}
										else
											cout << "Numero debe tener 8 numeros exactos" << endl;
									} while (telefono(t11) == false);
								}
								if (op == "6")
								{
									do {
										cout << "Telefono 2 nuevo: ";
										getline(cin, t22);
										if (telefono(t22))
										{

											user1.at(i).telefono2= ToInt(t22);
										}
										else
											cout << "Numero debe tener 8 numeros exactos" << endl;
									} while (telefono(t22) == false);
								}
								if (op == "7") { cout << "Correo nuevo: "; getline(cin, correo2); user1.at(i).correo = correo2; }
								if (op == "S" || op == "s")break;
								SaveFile();
							}
						}
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
		cout << "Identificacion debe tener 10 o mas caracteres" << endl;

}

void Usuario::eliminar_Usuario()
{
	Usuario us;
	string eliminar;
	cout << "Eliminar usuario: ";
	cin.ignore();
	getline(cin, eliminar);
	for (int i = 0; i < user1.size(); i++)
	{
		if (eliminar == user1.at(i).identificacion)
		{
			user1.at(i).el = 0;
			SaveFile();
		}
	}

}

/*
void pruebam()
{
	for (int i = 0; i < users.size(); i++)
	{
		cout << i + 1 << ": " << users.at(i).identificacion << endl;
		cout << i + 1 << ": " << users.at(i).nombre << endl;
		cout << i + 1 << ": " << users.at(i).tipo_propiedad << endl;
		cout << i + 1 << ": " << users.at(i).direccion << endl;
		cout << i + 1 << ": " << users.at(i).tel_1 << endl;
		cout << i + 1 << ": " << users.at(i).tel_2 << endl;
		cout << i + 1 << ": " << users.at(i).correo << endl;
		cout << i + 1 << ": " << users.at(i).el<< endl;
	}
}*/

void Monitoreo::Menu()
{
	Usuario us;
	readFileM();
	IdsM();
	//pruebam();

	int opcion;
	while(true)
	{
		cout << "MENU" << endl;
		cout << "1. Monitorear" << endl;//Salida del comando que se desee ingresar
		cout << "2. Establecer usuarios" << endl;
		cout << "3. Eliminar usuario" << endl;
		cout << "4. Centro de ayuda" << endl;
		cout << "5. Acerca de" << endl;
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
			cin.ignore();
			getline(cin, U);
			cout << endl;
			us.Establecer_Usuarios(U);
			cout << endl;
		}
		if (opcion == 3)
		{
			us.eliminar_Usuario();
		}
		if (opcion == 0)
			break;
		
	} 

	
}
