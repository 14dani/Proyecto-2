#include "pch.h"
#include "Sistema_alarma.h"
#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <thread> 
#include"Arduino.h"
#include <time.h>
#include <ctime>
#include <stdlib.h>
#pragma warning(disable : 4996)
#include <winsock2.h>
#include <stdexcept> //Clave
#include <windows.h>//Clave
using namespace std;

Arduino arduino;

string dispositivo_1_;
string dispositivo_2_;
string variable_monitoreo;
string variable_alarma;
string variable_alarma_desactivada;
vector<string> dispos;////Estas tres lineas se cambian con dispositivos
Arduino comunicacion;

struct alertas
{
	string dispositivo;
	string estado;
};

struct Linea_bitacora
{
	string fyh;
	string id;
	string balerta;
	string z_c;
	string bdescripcion;
	string baccion;
	int el;
};

struct Linea_bitacora1
{
	string f1;
	string h1;
	string id1;
	string balertas1;
	string z_c1;
	string bdescripcion1;
	string baccion1;
	int el;
};

vector<Linea_bitacora>lb;


int numero_dispositivo;
string estadoi;
alertas alertadx;

Sistema_alarma::Sistema_alarma()
{
}

alertas estado_alerta()
{
	dispos={dispositivo_1_, dispositivo_2_ };
	for (int i = 1; i <= 2; i++)////Aqui se harian cambios en los dispositivos.
	{
		estadoi = dispos[i - 1];
		numero_dispositivo = i;
		if (estadoi == "ACTIVADO")
		{
			break;
		}

	}
	alertadx.dispositivo = numero_dispositivo;
	alertadx.estado = estadoi;
	return alertadx;
}

void alerta()
{
	while (variable_alarma == "ACTIVADO" && variable_monitoreo == "ACTIVADO" && variable_alarma_desactivada=="NO ACTIVADO") {

				cout << endl << "ALERTA" << endl;
				this_thread::sleep_for(chrono::milliseconds(2000));
	}
}
void gestionar_arduino()///Aqui se cambiarian
{
			comunicacion.proveer();
			dispositivo_1_ = comunicacion.dispositivo_1;
			dispositivo_2_ = comunicacion.dispositivo_2;
}
int monitorear()
{
	
	alertas alertad;
	while (true)
	{
		if (variable_monitoreo == "ACTIVADO")
		{
			gestionar_arduino();
			alertad = estado_alerta();
				if (alertad.estado == "ACTIVADO")////Primero apaga la alerta para que no siga apareciendo
				{
					dispositivo_1_ == "NO ACTIVADO";
					dispositivo_2_ == "NO ACTIVADO";////aqui se cambiarian los dispositivos
					
					/////MANDAR CORREO
					variable_alarma = "ACTIVADO";
						thread alertar(alerta);
						alertar.detach();
				}

		}
		else return NULL;
	}

}

struct U_Principal
{
	int codigoP;
	string cod_accesoP;

};

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
	string disponible;
};

struct S_A
{
	string identificacion;
	U_Principal UsuarioP;
	vector<U_secundario>UsuariosS;
	vector<zona>zonas;
	string disponible;
};


vector<S_A>usuarios; //Vector donde se guaradaran los usuarios
vector<string>Ucontraseña;

string hora()
{
	string h, m, s, r;
	time_t now;
	struct tm nowLocal;
	now = time(NULL);
	nowLocal = *localtime(&now);
	h = to_string(nowLocal.tm_hour);
	m = to_string(nowLocal.tm_min);
	s = to_string(nowLocal.tm_sec);
	r = h + ":" + m + ":" + s;
	return r;
}

string fecha()
{
	string d,m,a,r;
	time_t now;
	struct tm nowLocal;
	now = time(NULL);
	nowLocal = *localtime(&now);
	d = to_string(nowLocal.tm_mday);
	m = to_string(nowLocal.tm_mon + 1);
	a = to_string(nowLocal.tm_year + 1900);
	r = d + "." + m + "." + a;
	return r;
}

vector<string> Scmd(string string1) //Separa el string cuando se ingresan los comandos cuando encuentra espacios
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

vector<string>registro1;
vector<string>NOidentificaciones;
vector<string>identificaciones;
vector<string>identificaciones1;//Se guardan identificaciones


void ExtraerInfo(string str1) //Extrae cada identificacion
{
	S_A s;
	string m;
	identificaciones = Scmd(str1);
	identificaciones1.push_back(identificaciones[0]);
	s.identificacion = identificaciones[0];
	s.disponible = identificaciones[7];
	usuarios.push_back(s);
}

void readFile()//Lee usuarios establecidos del monitoreo.cpp
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





//Validaciones

bool RecorrerIden(string usuario) //Verifica que la identidad o usuario que se ingrese este entre los usuarios establecidos
{
	bool f = false;
	{
		for (int i = 0; i < usuarios.size(); i++)
		{
			if ((usuario == usuarios.at(i).identificacion) && (usuarios.at(i).disponible == "1"))
			{
				f = true;
			}
		}
	}
	return f;
}


//Validacion del telefono de usuario secundarios

bool telefono1(string numero) //verifica que la identificacion sea de 8 digitos exactos
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

int ToInt1(string s) //Funcion que convierte lo de telefono en int
{
	stringstream ss(s);
	int x = 0;
	ss >> x;
	return x;
}

//Validaciones de la contraseña

bool verificar_cantidad(string x) //verifica que la contraseña tenga 8 o mas caracteres
{
	if (8 > int(x.length()))
	{
		return false;
	}
	else { return true; }
}

bool verificar_repetido(string x)// verifica que la letras no se repita 3 0 mas veces
{
	int contador = 0;
	for (int i = 0; i < int(x.length()); i++)
	{
		contador = 0;
		for (int j = 0; j <int(x.length()); j++)
		{
			if (x[i] == x[j]) { contador++; }
		}
		if (contador > 2) { return false; }
	} { return true; }
}

bool verificar_mayuscula(string  x) //verifica que al menos haya una mayuscula
{
	for (int i = 0; i < int(x.length()); i++)
	{
		if (!isdigit(x[i])) {
			if (isupper(x[i]))
				return true;
		}
	}
	return false;
}

bool verificar_minuscula(string x) //verifica que haya al menos una minuscula
{
	for (int i = 0; i < int(x.length()); i++)
	{
		if (!isdigit(x[i])) {
			if (!isupper(x[i]))
				return  true;
		}
	}return false;
}

bool verificar_digito(string x) //verifica que hayaal menos un digito
{
	for (int i = 0; i < int(x.length()); i++)
	{
		if (isdigit(x[i])) { return true; }
	} { return false; }
}

bool verificar_todo(string x) //verifica que hay al menos un simbolo que no sea ni letra o digito
{
	for (int i = 0; i < int(x.length()); i++)
	{
		if (!isalnum(x[i]))return true;
	}return false;
}

bool validar_palabra_clave(string x) //Verifica todo el string para que se cumplan la validaciones anteriores
{
	if (verificar_cantidad(x) && verificar_digito(x) && verificar_mayuscula(x) && verificar_minuscula(x) && verificar_repetido(x) && verificar_todo(x))
		return true;
	else return false;
}
/*
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
*/
string getpassword(const string& prompt = "Enter password> ") //Hace que no se vean la clave cuando se ingresa
{
	string result;

	// Set the console mode to no-echo, not-line-buffered input
	DWORD mode, count;
	HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleMode(ih, &mode))
		throw runtime_error(
			"getpassword: You must be connected to a console to use this program.\n"
		);
	SetConsoleMode(ih, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

	// Get the password string
	WriteConsoleA(oh, prompt.c_str(), prompt.length(), &count, NULL);
	char c;
	while (ReadConsoleA(ih, &c, 1, &count, NULL) && (c != '\r') && (c != '\n'))
	{
		if (c == '\b')
		{
			if (result.length())
			{
				WriteConsoleA(oh, "\b \b", 3, &count, NULL);
				result.erase(result.end() - 1);
			}
		}
		else
		{
			WriteConsoleA(oh, "*", 1, &count, NULL);
			result.push_back(c);
		}
	}
	// Restore the console mode
	SetConsoleMode(ih, mode);
	return result;
}
//////ARCHIVOS///////////////////////////////////////////////////////////

void Archivo_usuario_SA()
{
	fstream file;

	file.open("UsuariosSistemaAlarma.txt", ios::out);

	if (!file.is_open())
		cout << "Error al abrir archivo" << endl;
	else
	{
		for (unsigned int u = 0; u < usuarios.size(); u++)
		{
			file << usuarios.at(u).identificacion << "-"
				<< usuarios.at(u).UsuarioP.codigoP << "-"
				<< usuarios.at(u).UsuarioP.cod_accesoP << ".";
			for (int i = 0; i < usuarios.at(u).UsuariosS.size(); i++)
			{
				file << usuarios.at(u).UsuariosS.at(i).codigo << "-"
					<< usuarios.at(u).UsuariosS.at(i).cod_acceso << "-"
					<< usuarios.at(u).UsuariosS.at(i).nombre_persona << "-"
					<< usuarios.at(u).UsuariosS.at(i).telefono << "|";
			}
			file << ".";
			for (int f = 0; f < usuarios.at(u).zonas.size(); f++)
			{
				file << usuarios.at(u).zonas.at(f).z << "-"
					<< usuarios.at(u).zonas.at(f).descrpcion << "-"
					<< usuarios.at(u).zonas.at(f).dispositivo << "-"
					<< usuarios.at(u).zonas.at(f).disponible << "|";
			}
			file << ".";
			file << usuarios.at(u).disponible << endl;
		}
		file.close();
	}

}

vector<string> ScmdS(string string1) //Separa el string cuando se ingresan los comandos cuando encuentra espacios
{
	vector<string> space;


	istringstream iss(string1);

	string token;

	while (getline(iss, token, '.'))
	{

		space.push_back(token);

	}
	return space;
}

vector<string> ScmdUZ(string string1) //Separa el string cuando se ingresan los comandos cuando encuentra espacios
{
	vector<string> space;


	istringstream iss(string1);

	string token;

	while (getline(iss, token, '|'))
	{

		space.push_back(token);

	}
	return space;
}

vector<string>seccion;
vector<string>seccion1;
vector<string>secciones;
vector<string>UCC;
vector<string>USALL;
vector<string>ZALL;
vector<string>US1;
vector<string>Z1;

void ExtraerInfoSecciones(string str1) //Guarda los usuarios en users
{
	S_A user1;
	U_secundario us2;
	zona z2;
	vector<U_secundario>usuarios2;
	vector<zona>Zonas2;
	secciones = ScmdS(str1);
	UCC = Scmd(secciones[0]);
	USALL = ScmdUZ(secciones[1]);
	ZALL = ScmdUZ(secciones[2]);

	user1.UsuarioP.codigoP = ToInt1(UCC[1]);
	/*user1.UsuarioP.cod_accesoP = UCC[2];
	for (int i = 0; i < USALL.size()-1; i++)
	{
		US1.clear();
		US1 = Scmd(USALL[i]);
		for (int j = 0; j < US1.size()-1; j++)
		{
			us2.codigo = ToInt1(US1[0]);
			us2.cod_acceso = US1[1];
			us2.nombre_persona = US1[2];
			us2.telefono = ToInt1(US1[3]);
			usuarios2.push_back(us2);
			
		}
	}
	user1.UsuariosS = usuarios2;
	for (int i = 0; i < ZALL.size()-1; i++)
	{
		Z1.clear();
		Z1 = Scmd(ZALL[i]);
		for (int j = 0; j < Z1.size()-1; j++)
		{
			z2.z = ToInt1(US1[0]);
			z2.descrpcion = US1[1];
			z2.dispositivo = US1[2];
			z2.disponible = US1[3];
			Zonas2.push_back(z2);

		}
	}
	user1.zonas = Zonas2;*/
	usuarios.push_back(user1);
	
}

void LeerArchivoSA()
{
	ifstream my_file;
	string registro;
	my_file.open("UsuariosSistemaAlarma.txt", ios::in);

	if (my_file.fail())
	{
		cout << endl << "Archivo no existente" << endl << endl;
	}
	else
	{
		while (!my_file.eof())
		{
			seccion.clear();
			getline(my_file, registro);
			seccion.push_back(registro);

			for (int i = 0; i < seccion.size(); i++)
			{
				
				seccion1.push_back(seccion[i]);

			}
		}
		if (my_file.eof())
		{
			cout << endl;
		}
	}
}

void IU()//Funcion que extrae los atributos de la estructura Usuario para que no se borren
{
	for (int i = 0; i < seccion1.size(); i++)
	{

		ExtraerInfoSecciones(seccion1[i]);
	}

}


void prueba()
{
	cout << seccion.size() << endl;

	/*for (int i = 0; i < secciones.size(); i++)
	{
		cout << secciones[i] << endl;
		//ExtraerInfoSecciones(seccion1[i]);
	}*/
	/*for (int i = 0; i < usuarios.size(); i++)
	{
		cout << i + 1 << ":" << usuarios.at(i).identificacion << endl;
		cout << i + 1 << ":" << usuarios.at(i).UsuarioP.codigoP << endl;
		cout << i + 1 << ":" << usuarios.at(i).UsuarioP.cod_accesoP << endl;
		cout << i + 1 << ":" << usuarios.at(i).disponible << endl;
	}*/
}

void Archivo_Bitacora()
{

}

void Archivo_monitoreo()
{

}



void armar_sistema()
{
	string id, con,con1;
	string est = "Armar";

	Linea_bitacora linea;
	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		/*
		cout << "Ingrese la clave: ";
		con = getpassword(con1);
		getline(cin, con1);
		for(int i=0;i<usuarios.size();i++)
		{
			if ((id == usuarios.at(i).identificacion)&&(con == usuarios.at(i).UsuarioP.cod_accesoP))
			{
				usuarios.at(i).UsuarioP.codigoP = 0;

				//linea.fyh = ctime(&H);
				linea.id = id;
				linea.balerta = est;
				linea.z_c = usuarios.at(i).UsuarioP.codigoP;
				linea.bdescripcion = "&";
				linea.baccion = "&";
				linea.el = 1;
				lb.push_back(linea);

			}
			else
			{
				for (int n = 0; n < usuarios.size(); n++)
				{
					for (int m = 0; m < usuarios.at(n).UsuariosS.size(); m++)
					{
						if (con == usuarios.at(n).UsuariosS.at(m).cod_acceso)
						{
							//linea.fyh = ctime(&H);
							linea.id = id;
							linea.balerta = est;
							linea.z_c = usuarios.at(n).UsuariosS.at(m).codigo;
							linea.bdescripcion = "&";
							linea.baccion = "&";
							linea.el = 1;
							lb.push_back(linea);

						}

					}
				}
			}

		}*/
		variable_monitoreo = "ACTIVADO";
		variable_alarma_desactivada = "NO ACTIVADO";
		thread a_monitorear(monitorear);
		a_monitorear.detach();
		cout << endl << "LISTO" << endl << endl;

	}
	else cout << "Usuario no registrado" << endl;
}

void desarmar_sistema()
{
	string id, con,con1;
	string est = "Desarmar";
	//time_t H = time(nullptr);
	//tm * timeinfo = localtime(&H); ////linea.fyh = ctime(&H);
	Linea_bitacora linea;
	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		/*
		cout << "Ingrese la clave: ";
		con=getpassword(con1);
		getline(cin, con1);
		for (int i = 0; i < usuarios.size(); i++)
		{
			if ((id == usuarios.at(i).identificacion) && (con == usuarios.at(i).UsuarioP.cod_accesoP))
			{
				usuarios.at(i).UsuarioP.codigoP = 0;

				//linea.fyh = ctime(&H);
				linea.id = id;
				linea.balerta = est;
				linea.z_c = usuarios.at(i).UsuarioP.codigoP;
				linea.bdescripcion = "&";
				linea.baccion = "&";
				linea.el = 1;
				lb.push_back(linea);

			}
			else
			{
				for (int n = 0; n < usuarios.size(); n++)
				{
					for (int m = 0; m < usuarios.at(n).UsuariosS.size(); m++)
					{
						if (con == usuarios.at(n).UsuariosS.at(m).cod_acceso)
						{
							//linea.fyh = ctime(&H);
							linea.id = id;
							linea.balerta = est;
							linea.z_c = usuarios.at(n).UsuariosS.at(m).codigo;
							linea.bdescripcion = "&";
							linea.baccion = "&";
							linea.el = 1;
							lb.push_back(linea);

						}

					}
				}
			}

		}*/

		variable_monitoreo = "NO ACTIVADO";
		variable_alarma = "NO ACTIVADO";
	}
	else { variable_alarma_desactivada = "NO ACTIVADO"; alerta(); cout << "Usuario no registrado" << endl; }
}

void desactivar_sistema()
{
	string id, con, con1;
	string est = "DESACTIVACION";
	//time_t H = time(nullptr);
	//tm * timeinfo = localtime(&H); ////linea.fyh = ctime(&H);
	Linea_bitacora linea;
	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		cout << "Ingrese la clave: ";
		con = getpassword(con1);
		getline(cin, con1);
		variable_alarma = "NO ACTIVADO";
	}
	else { variable_alarma_desactivada=="NO ACTIVADO"; alerta(); cout << "Usuario no registrado" << endl; }
}

void programar_zonas() //Me falta terminar esta
{
	S_A sa;
	zona zo;
	vector<zona>zv;
	string id, des, dis, op, op2, des2, dis2, con, con1;
	int num, num2,num3;

	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		cout << "Ingrese codigo de acceso principal: ";
		con = getpassword(con1);
		getline(cin, con1);

		for (int i = 0; i < usuarios.size(); i++)
		{
			
			if (id == usuarios.at(i).identificacion&&usuarios.at(i).UsuarioP.cod_accesoP==con)
			{
				cout << "Numero de zona: ";
				cin >> num;
				if (usuarios.at(i).zonas.size() == 0)
				{
					cout << "Numero de zona no registrado" << endl;
					cout << "Ingrese numero de zona: ";
					cin >> num;
					if (num >= 1)
					{
						zo.z = num;
						cout << "Ingrese descripcion: ";
						cin.ignore();
						getline(cin, des);
						zo.descrpcion = des;
						cout << "Dispositivo que se va a instalar: ";

						getline(cin, dis);
						zo.dispositivo = dis;
						zo.disponible = "1";
						zv.push_back(zo);
						usuarios.at(i).zonas = zv;
						Archivo_usuario_SA();
						cout << endl;
					}
					else
						cout << "Numero de zona debe ser mayor o igual a 1" << endl << endl;
				}
				else
				{
					for (int m = 0; m < usuarios.at(i).zonas.size(); m++)
					{

						if (num == usuarios.at(i).zonas.at(m).z)
						{
							cout << "Numero de zona: " << usuarios[i].zonas[m].z << endl;
							cout << "Descripcion: " << usuarios[i].zonas[m].descrpcion << endl;
							cout << "Dispositivo instalado en la zona: " << usuarios[i].zonas[m].dispositivo << endl;
							cout << endl;
							cout << "Para cambiar algun dato presione la tecla <c>" << endl;
							cout << "Para borrar alguna zona presione la tecla <b>" << endl;
							cout << "Para agregar zona presione la tecla <a>" << endl;
							cin.ignore();
							getline(cin, op);
							if (op == "c" || op == "C")
							{
								while (true)
								{
									cout << endl;
									cout << "1. Numero de zona" << endl;
									cout << "2. Descripcion" << endl;
									cout << "3. Dispositivo" << endl;
									cout << "S. Salir" << endl;
									cout << "Cambiar: "; getline(cin, op2);
									if (op2 == "1")
									{
										cout << "Numero nuevo: "; cin >> num2;
										if (num2 >= 1)
										{
											for (int h = 0; h < usuarios[i].zonas.size(); h++)
											{
												if (num2 != usuarios[i].zonas[h].z)
												{
													usuarios[i].zonas[m].z = num2;
												}
											}
										}
										else
											cout << "Numero debe ser mayor o igual a 1" << endl << endl;
									}
									if (op2 == "2") { cout << "Nueva descripcion: "; getline(cin, des2); usuarios[i].zonas[m].descrpcion = des2; }
									if (op2 == "3") { cout << "Nuevo dispositivo: "; getline(cin, dis2); usuarios[i].zonas[m].dispositivo = dis2; }
									if (op2 == "S" || op2 == "s")break;
									Archivo_usuario_SA();
								}
							}
							if (op == "b" || op == "B")
							{
								usuarios[i].zonas[m].disponible = "0";
								Archivo_usuario_SA();
							}
							if (op == "a" || op == "A")
							{
								cout << "Ingrese numero de zona: ";
								cin >> num3;
								if (num3 >= 1)
								{
									zo.z = num3;
									cout << "Ingrese descripcion: ";
									cin.ignore();
									getline(cin, des);
									zo.descrpcion = des;
									cout << "Dispositivo que se va a instalar: ";
									getline(cin, dis);
									zo.dispositivo = dis;
									zo.disponible = "1";

									zv = usuarios.at(i).zonas;
									zv.push_back(zo);
									usuarios.at(i).zonas = zv;
									Archivo_usuario_SA();
									cout << endl;
									break;
								}
								else
									cout << "Numero debe ser mayor o igual a 1" << endl << endl;
							}

						}
						else
						{
							cout << "Numero de zona no registrado" << endl;
							cout << "Ingrese numero de zona: ";
							cin >> num3;
							if (num3 >= 1)
							{
								zo.z = num3;
								cout << "Ingrese descripcion: ";
								cin.ignore();
								getline(cin, des);
								zo.descrpcion = des;
								cout << "Dispositivo que se va a instalar: ";
								getline(cin, dis);
								zo.dispositivo = dis;
								zo.disponible = "1";
								zv = usuarios.at(i).zonas;
								zv.push_back(zo);
								usuarios.at(i).zonas = zv;
								Archivo_usuario_SA();
								cout << endl;
								break;
							}
							else
								cout << "Numero debe ser mayor o igual a 1" << endl << endl;
						}
					}
				}
			}
			
		}
	}
	else cout << "Usuario no registrado" << endl;
}

void SaveFileZ(vector<zona>zz1)//Archivo pdf para imprimir lista
{
	fstream my_file;
	string m = "Lista.pdf";

	my_file.open(m, ios::out|ios::binary);

	if (!my_file.is_open())
		cout << "Error al abrir archivo" << endl;
	else
	{
		for (int i = 0; i < zz1.size(); i++)
		{

			my_file << setw(19) << zz1.at(i).z << setw(11) << setw(10) << zz1.at(i).descrpcion << setw(30) << zz1.at(i).dispositivo << endl;

		}
		my_file.close();
	}

}

void ArchivoImprimir(string id)
{
	string m = id + ".pdf";
	
	ShellExecute(NULL, TEXT("open"), TEXT("C:\\Users\\User\\Desktop\\Prueba12\\Proyecto2\\Proyecto2\\Lista.pdf"), NULL, NULL, SW_SHOWNORMAL);
}

void lista_zonas()
{
	string id,con,imp,con1;
	vector<int>Nzonas;
	vector<zona>zz;
	int z;
	vector<zona>zz2;

	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	
	if (RecorrerIden(id))
	{
		
		cout << "Ingrese la clave: ";
		con = getpassword(con1);
		getline(cin, con1);

		for (int i = 0; i < usuarios.size(); i++)
		{

			if (id == usuarios.at(i).identificacion)
			{
				if (usuarios.at(i).UsuarioP.cod_accesoP == con)
				{
					for (int j = 0; j < usuarios.at(i).zonas.size(); j++)
					{
						Nzonas.push_back(usuarios.at(i).zonas.at(j).z);
						zz.push_back(usuarios.at(i).zonas.at(j));
					}
				}
				else
				{
					for (int n = 0; n < usuarios.size(); n++)
					{
						for (int m = 0; m < usuarios.at(n).UsuariosS.size(); m++)
						{
							if (con == usuarios.at(n).UsuariosS.at(m).cod_acceso)
							{
								for (int h = 0; h < usuarios.at(n).zonas.size(); h++)
								{
									Nzonas.push_back(usuarios.at(n).zonas.at(h).z);
									zz.push_back(usuarios.at(n).zonas.at(h));
								}
							}

						}
					}
				}

			}
		}


		for (int i = 1; i < Nzonas.size(); i++)//acomoda la lista en orden
		{
		
			for (int j = 0; j < Nzonas.size() - 1; j++)
			{
				if (Nzonas[j] > Nzonas[j + 1])
				{
					int temp;
					temp = Nzonas[j];
					Nzonas[j] = Nzonas[j + 1];
					Nzonas[j + 1] = temp;

				}

			}
		}

		for (int i = 0; i < zz.size(); i++)
		{
			z = zz[i].z;
			for (int s = 0; s < Nzonas.size(); s++)
			{
				if (Nzonas[s] == z)
				{
					//cout << zz.at(s).z << "  " << zz.at(s).descrpcion << "  " << zz.at(s).dispositivo << endl;//Push_back al tercer vector 
					zz2.push_back(zz.at(s));
				}
			}
		}

		for (int i = 0; i < usuarios.size(); i++)
		{

			if (id == usuarios.at(i).identificacion)
			{
				if (usuarios.at(i).UsuarioP.cod_accesoP == con)
				{
					for (int j = 0; j < usuarios.at(i).zonas.size(); j++)
					{
						
						cout << setw(20) << "Zona" << setw(20) << "Descripcion" << setw(40) << "Dispositivo" << endl;
						cout << setw(108) << "==============================================================================================" << endl;

						for (int s = 0; s < zz2.size(); s++)
						{

							cout << setw(19) << zz2.at(s).z << setw(11) << setw(10) << zz2.at(s).descrpcion << setw(30) << zz2.at(s).dispositivo << endl;

						}
						SaveFileZ(zz2);
						cout << "Para IMPRIMIR presione la tecla <I>" << endl;
						cout << "Para SALIR presione la tecla <S>" << endl << endl;
						getline(cin, imp);
						/*if (imp == "i" || imp == "I")
						{
							ArchivoImprimir(id);
						}*/

					}
				}
				else
				{
					for (int n = 0; n < usuarios.size(); n++)
					{
						for (int m = 0; m < usuarios.at(n).UsuariosS.size(); m++)
						{
							if (con == usuarios.at(n).UsuariosS.at(m).cod_acceso)
							{
								for (int h = 0; h < usuarios.at(n).zonas.size(); h++)
								{
									cout << setw(20) << "Zona" << setw(20) << "Descripcion" << setw(40) << "Dispositivo" << endl;
									cout << setw(108) << "==============================================================================================" << endl;

									for (int l = 0; l < zz2.size(); l++)
									{

										cout << setw(19) << zz2.at(l).z << setw(11) << setw(10) << zz2.at(l).descrpcion << setw(30) << zz2.at(l).dispositivo << endl;

									}
									SaveFileZ(zz2);
									cout << "Para IMPRIMIR presione la tecla <I>" << endl;
									cout << "Para SALIR presione la tecla <S>" << endl << endl;
									getline(cin, imp);
									/*if (imp == "i" || imp == "I")
									{
										ArchivoImprimir(id);
									}*/
								}
							}

						}
					}
				}

			}
		}

		

	}
	else cout << "Usuario no registrado" << endl;
}

void bitacora()
{
	string id,c_a;
	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		cout << "Ingrese codigo de acceso: ";
		getline(cin, c_a);
		for (int i = 0; i < usuarios.size(); i++)
		{
			if ((id == usuarios.at(i).identificacion)&&(c_a == usuarios.at(i).UsuarioP.cod_accesoP))
			{
				//crear_archivo_Bitacora(id);
				//leer_AB(id);
			}

		}
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

void establecer_CAP()//Establece el codigo principal
{
	string id, con1,con11, con2,con22, cambio, clave,clave1;
	vector<string>contraseñas;
	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		for (int i = 0; i < usuarios.size(); i++)
		{
			if (id == usuarios.at(i).identificacion)
			{
				if (Ucontraseña.size() == 0)
				{

					cout << "Ingrese codigo de acceso principal: ";
					con1 = getpassword(con11);
					getline(cin, con11);
					if (validar_palabra_clave(con1))
					{
						contraseñas.push_back(con1);
						cout << "Confirme el codigo de acceso principal: ";
						con2 = getpassword(con22);
						getline(cin, con22);
						for (int m = 0; m < contraseñas.size(); m++)
						{
							if (contraseñas[m] == con2)
							{
								usuarios.at(i).UsuarioP.codigoP = 0;
								usuarios.at(i).UsuarioP.cod_accesoP = con1;
								Ucontraseña.push_back(id);
								Archivo_usuario_SA();

							}
							else
								cout << "Contraseñas no concuerdan" << endl;
						}
					}
					else
						cout << "Clave debe tener 8 o mas caracteres y al menos 1 mayuscula, 1 minuscula, 1 digito, 1 simbolo y que los caracteres no se repitan 3 o mas veces" << endl << endl;
				}
				else
				{
					for (int e = 0; e < Ucontraseña.size(); e++)
					{
						if (id == Ucontraseña[e])
						{

							cout << "La clave ha sido establecida anteriormente" << endl << endl;
							cout << "Para cambiarla presione la tecla <c>" << endl;
							cout << "Para salir presione <s>" << endl << endl;
							getline(cin, cambio);
							if (cambio == "c" || cambio == "C")
							{
								cout << "Ingrese clave anterior: ";
								clave = getpassword(clave1);
								getline(cin, clave1);
								cout << clave << endl;
								for (int f = 0; f < usuarios.size(); f++)
								{
									if ((id == usuarios.at(f).identificacion) && (clave == usuarios.at(f).UsuarioP.cod_accesoP))
									{
										cout << "Ingrese codigo de acceso principal: ";
										con1 = getpassword(con11);
										getline(cin, con11);
										if (validar_palabra_clave(con1))
										{
											contraseñas.push_back(con1);
											cout << "Confirme el codigo de acceso principal: ";
											con2 = getpassword(con22);
											getline(cin, con22);
											for (int q = 0; q < contraseñas.size(); q++)
											{
												if (contraseñas[q] == con2)
												{
													usuarios.at(f).UsuarioP.codigoP = 0;
													usuarios.at(f).UsuarioP.cod_accesoP = con1;
													Archivo_usuario_SA();

												}
												else
													cout << "Contraseñas no concuerdan" << endl;
											}
										}
										else
											cout << "Clave debe tener 8 o mas caracteres y al menos 1 mayuscula, 1 minuscula, 1 digito, 1 simbolo y que los caracteres no se repitan 3 o mas veces" << endl << endl;
										break;
									}
									else
										cout << "Clave incorrecta" << endl;
									break;
								}
							}

						}
						else
						{
							for (int x = 0; x < usuarios.size(); x++)
							{
								if (id == usuarios.at(x).identificacion)
								{

									cout << "Ingrese codigo de acceso principal: ";
									con1 = getpassword(con11);
									getline(cin, con11);
									if (validar_palabra_clave(con1))
									{
										contraseñas.push_back(con1);
										cout << "Confirme el codigo de acceso principal: ";
										con2 = getpassword(con22);
										getline(cin, con22);
										for (int m = 0; m < contraseñas.size(); m++)
										{
											if (contraseñas[m] == con2)
											{
												usuarios.at(x).UsuarioP.codigoP = 0;
												usuarios.at(x).UsuarioP.cod_accesoP = con1;
												Ucontraseña.push_back(id);
												Archivo_usuario_SA();

											}
											else
												cout << "Contraseñas no concuerdan" << endl;
										}
									}
									else

										cout << "Clave debe tener 8 o mas caracteres y al menos 1 mayuscula, 1 minuscula, 1 digito, 1 simbolo y que los caracteres no se repitan 3 o mas veces" << endl << endl;

								}
							}
						}
						break;
					}
				}

			}
		}
		
	}
	else cout << "Usuario no registrado" << endl;
	cout << endl;
}

void establecer_CAS()//Establece codigos secundarios
{
	string id, conP, conP1, conS1,conS11,conS22, conS2, numTel;
	int numCod, numCod2;
	string Cod, nombre;
	U_secundario ss;
	vector<U_secundario>us;
	vector<string>contraseñas;


	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		cout << "Ingrese codigo de acceso: ";
		conP = getpassword(conP1);
		getline(cin, conP1);
		for (int i = 0; i < usuarios.size(); i++)
		{
			if ((id == usuarios.at(i).identificacion)&&(conP==usuarios.at(i).UsuarioP.cod_accesoP))
			{
				if (usuarios.at(i).UsuariosS.size() == 0)
				{
					cout << "Ingrese numero de codigo: ";
					cin >> numCod;
					ss.codigo = numCod;
					cout << "Codigo de acceso secundario: ";
					cin.ignore();
					conS1 = getpassword(conS11);
					getline(cin, conS11);
					if (validar_palabra_clave(conS1))
					{
						contraseñas.push_back(conS1);
						cout << "Confirmacion de codigo de acceso secundario: ";
						conS2 = getpassword(conS22);
						getline(cin, conS22);
						for (auto c : contraseñas)
						{
							if (c == conS2)
							{
								ss.cod_acceso = conS1;
								cout << "Ingrese nombre de usuario: ";
								getline(cin, nombre);
								ss.nombre_persona = nombre;
								cout << "Ingrese numero de telefono: ";
								getline(cin, numTel);
								if (telefono1(numTel))
								{
									ss.telefono = ToInt1(numTel);
									us.push_back(ss);
									usuarios.at(i).UsuariosS = us;
									Archivo_usuario_SA();
									break;
								}
								else
								{
									cout << "Numero de telefono debe tener 8 numeors exactos" << endl;
									break;
								}
							}
							else
							{
								cout << "Claves no concuerdan" << endl;
								break;
							}
						}

					}
					else
					{
						cout << "Clave debe tener al menos 1 mayuscula, 1 minuscula, 1 digito, 1 simbolo y que los caracteres no se repitan 3 o mas veces" << endl << endl;
						break;
					}
				}
				else
				{
					cout << "Ingrese numero de codigo: ";
					cin >> numCod2;
					for (int g = 0; g < usuarios.at(i).UsuariosS.size(); g++)
					{
						if (numCod2 != usuarios.at(i).UsuariosS.at(g).codigo)
						{
							ss.codigo = numCod2;
							cout << "Codigo de acceso secundario: ";
							cin.ignore();
							conS1 = getpassword(conS11);
							getline(cin, conS11);
							if (validar_palabra_clave(conS1))
							{
								contraseñas.push_back(conS1);
								cout << "Confirmacion de codigo de acceso secundario: ";
								conS2 = getpassword(conS22);
								getline(cin, conS22);
								for (auto c : contraseñas)
								{
									if (c == conS2)
									{
										ss.cod_acceso = conS1;
										cout << "Ingrese nombre de usuario: ";
										getline(cin, nombre);
										ss.nombre_persona = nombre;
										cout << "Ingrese numero de telefono: ";
										getline(cin, numTel);
										if (telefono1(numTel))
										{
											ss.telefono = ToInt1(numTel);
											us = usuarios.at(i).UsuariosS;
											us.push_back(ss);
											usuarios.at(i).UsuariosS = us;
											Archivo_usuario_SA();
											break;
										}
										else
										{
											cout << "Numero de telefono debe tener 8 numeors exactos" << endl;
											break;
										}
									}
									else
									{
										cout << "Claves no concuerdan" << endl;
										break;
									}
									
								}
							}
							else
							{
								cout << "Clave debe tener al menos 1 mayuscula, 1 minuscula, 1 digito, 1 simbolo y que los caracteres no se repitan 3 o mas veces" << endl << endl;
								break;
							}
						}
						else
						{
							cout << "Numero de codigo repetido" << endl;
							break;
						}
						break;
					}
				}
				
			}
		}
	}
	else cout << "Usuario no registrado" << endl;
}

void imp()
{
	string id;
	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);

	for (int i = 0; i < usuarios.size(); i++)
	{
		if (id == usuarios.at(i).identificacion)
		{
			for (int j = 0; j < usuarios.at(i).UsuariosS.size(); j++)
			{
				cout << usuarios.at(i).UsuariosS.at(j).codigo << endl;
				cout << usuarios.at(i).UsuariosS.at(j).cod_acceso << endl;
				cout << usuarios.at(i).UsuariosS.at(j).nombre_persona << endl;
				cout << usuarios.at(i).UsuariosS.at(j).telefono << endl;

			}

		}
	}

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

int Sistema_alarma::Menu()/*Estado es un interruptor que indica si se esta llamando a la funcion para consultar el estado 
									 o para correr el menu, tipo es el dato de quien esta haciendo la consulta*/
{
		string opcion;
		
		readFile();
		Ids(); //se cargan las identidades del monitoreo.cpp
	   LeerArchivoSA();
		//IU();
		
		//prueba();
		
		cin.ignore();
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

			if (opcion == "0")return 0;
			else if (opcion == "1") {  armar_sistema(); }
			else if (opcion == "2") { variable_alarma_desactivada = "ACTIVADO"; desarmar_sistema(); }
			else if (opcion == "3") { variable_alarma_desactivada = "ACTIVADO"; desactivar_sistema(); }
			else if (opcion == "4")programar_zonas();
			else if (opcion == "5") {
				lista_zonas();
			}
			else if (opcion == "6")bitacora();
			else if (opcion == "7")borrar_bitacora();
			else if (opcion == "8")establecer_CAP();
			else if (opcion == "9") { establecer_CAS(); imp(); }
			//else if (opcion == "10")armar_sistema();
			//else if (opcion == "11")armar_sistema();


		}
		
}

////El estado tipo 1 indica si la alarma esta o no esta armada.
////El estado tipo 2 indica si la sirena esta sonando.