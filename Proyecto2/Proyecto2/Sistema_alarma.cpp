#include "pch.h"
#include "Sistema_alarma.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono> 
#include"Arduino.h"
using namespace std;

Arduino arduino;

string dispositivo_1_;
string dispositivo_2_;
string variable_para_gestion = "NO ACTIVADO";
string variable_monitoreo = "NO ACTIVADO";
string variable_alarma = "NO ACTIVADO";
vector<string*> dispos = { &dispositivo_1_,&dispositivo_2_ };////Estas tres lineas se cambian con dispositivos

string linea_a_guardar;
fstream linea12;
string linead;

string lineadzx;
string linea_a_guardarzx;


struct alertas
{
	string dispositivo;
	string estado;
};

//fstream dispositivos1;
int numero_dispositivo;
string estadoi;
alertas alertadx;

Sistema_alarma::Sistema_alarma()
{
}


int esperar1_1()
{
	if (!linea12.is_open())
	{
		esperar1_1();
	}
	return NULL;
}
/*int esperar3_1()
{
	if (!dispositivos1.is_open())
	{
		esperar3_1();
	}
	return NULL;
}*/
int esperar1()//////Funcion de esperar para funcion consultar estado y modificar estado.
{
	if (linea12.is_open())
	{
		esperar1();
	}
	return NULL;
}
/*int esperar3()//////Funcion de esperar para estado de alerta.
{
	if (dispositivos1.is_open())
	{
		esperar3();		
	}
	return NULL;
}*/

/*void Ejecutar()
{
		esperar3();
		dispositivos1.open("Arduino.txt", ios::out);
		esperar3_1();
		dispositivos1 << dispositivo_1_ << endl;
		esperar3_1();
		dispositivos1 << dispositivo_2_ << endl;
		dispositivos1.close();
	
}*/
/*string consultar_estado(int tipo)
{
	if (!linea12.is_open()) {
		linea12.open("estados.txt", ios::in);
		for (int i = 1; i <= 2; i++)
		{
			getline(linea12, linead);
			if (tipo == 1 && i == 1)linea_a_guardar = linead;
			else if (tipo == 2 && i == 2)linea_a_guardar = linead;
		}
		linea12.close();
		return linea_a_guardar;
	}
	else return consultar_estado(tipo);

}*/


/*void modificar_estado(int tipo, string estado_cambiado)
{
	if (!linea12.is_open()) {
		linea12.open("estados.txt", ios::in);
		if (tipo == 1)
		{
			for (int i = 1; i <= 2; i++)
			{
				getline(linea12, lineadzx);
				if (i == 2)linea_a_guardarzx = lineadzx;
			}
			linea12.close();
			linea12.open("estados.txt", ios::out);
			linea12 << estado_cambiado << endl;
			linea12 << linea_a_guardarzx << endl;
			if (estado_cambiado == "NO ACTIVADO")variable_para_gestion = "NO ACTIVADO";
			else if (estado_cambiado == "ACTIVADO")variable_para_gestion = "ACTIVADO";
			linea12.close();
		}
		else if (tipo == 2)
		{
			for (int i = 1; i <= 2; i++)
			{
				getline(linea12, lineadzx);
				if (i == 1)linea_a_guardarzx = lineadzx;
			}
			linea12.close();
			linea12.open("estados.txt", ios::out);
			linea12 << linea_a_guardarzx << endl;
			linea12 << estado_cambiado << endl;
			linea12.close();
		}
		else linea12.close();
	}
	else modificar_estado(tipo, estado_cambiado);
}*/


alertas estado_alerta()
{
	for (int i = 1; i <= 2; i++)////Aqui se harian cambios en los dispositivos.
	{
		estadoi = *(dispos[i - 1]);
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
	while (true) {
			if (variable_alarma=="ACTIVADO") {
				this_thread::sleep_for(chrono::seconds(10));
				cout << endl << "ALERTA" << endl;
			}
			else { cout << "HE CERRADO"; break; }


	}
}
void gestionar_arduino()
{
	while (true) {
		if (variable_para_gestion == "ACTIVADO") {
			dispositivo_1_ = "ACTIVADO";
			dispositivo_2_ = "DESACTIVADO";
		}
		else break;
	}
}
int monitorear()
{
	alertas alertad;
	while (true)
	{
		if (variable_monitoreo == "ACTIVADO")
		{
			alertad = estado_alerta();
			if (alertad.estado == "ACTIVADO")////Primero apaga la alerta para que no siga apareciendo
			{
				for (int i = 1; i <= 2; i++)////aqui se cambiarian los dispositivos
				{
					*dispos[i - 1] = "NO ACTIVADO";
				}
				/////MANDAR CORREO
				variable_alarma="ACTIVADO";
				thread alertar(alerta);
				alertar.detach();
			}

			//thread gestion(gestionar_arduino);
			//gestion.join();
			
		}
		else return NULL;
		this_thread::sleep_for(chrono::seconds(1));
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
};

struct S_A
{
	string identificacion;
	U_Principal UsuarioP;
	vector<U_secundario>UsuariosS;
	vector<zona>zonas;
};

struct Linea_Bitacora
{
	string fecha;
	string hora;
	string id;
	string balerta;
	string z_c;
	string bdescripcion;
	string accion;
	int el;

};

vector<S_A>usuarios; //Vector donde se guaradaran los usuarios
vector<string>Ucontraseña;
vector<Linea_Bitacora>lines;


vector<string> Scmd(string string1) //Separa el string cuando se ingresan los comandos cuando encuentra espacios
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
			if (usuario == usuarios.at(i).identificacion)
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

void armar_sistema()
{
	string id;
	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		variable_monitoreo = "ACTIVADO"; 
		variable_para_gestion = "ACTIVADO"; 
		thread gestion(gestionar_arduino); 
		gestion.detach();
		thread a_monitorear(monitorear);
		a_monitorear.detach();
		cout << endl << "LISTO" << endl<<endl;
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
		variable_monitoreo = "NO ACTIVADO";
	}
	else cout << "Usuario no registrado" << endl;
}

void desactivar_sistema()
{
	variable_alarma = "NO ACTIVADO";
	string id;
	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		variable_alarma = "NO ACTIVADO";
	}
	else cout << "Usuario no registrado" << endl;
}

void programar_zonas() //Me falta terminar esta
{
	S_A sa;
	zona zo;
	vector<zona>zv;
	string id, des, dis, op, op2, des2, dis2;
	int num, num2,num3;

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

						zv.push_back(zo);
						usuarios.at(i).zonas = zv;
						cout << endl;
					}
					else
						cout << "Numero de zona debe ser mayor o igual a 1" << endl << endl;
				}
				else
				{
					for (int m = 0; m < usuarios.at(i).zonas.size(); m++)
					{

						if (num == usuarios[i].zonas[m].z)
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
											cout << "Numero debe ser mayor o igual a 1" << endl << endl;;
									}
									if (op2 == "2") { cout << "Nueva descripcion: "; getline(cin, des2); usuarios[i].zonas[m].descrpcion = des2; }
									if (op2 == "3") { cout << "Nuevo dispositivo: "; getline(cin, dis2); usuarios[i].zonas[m].dispositivo = dis2; }
									if (op2 == "S" || op2 == "s")break;
								}
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

								zv = usuarios.at(i).zonas;
								zv.push_back(zo);
								usuarios.at(i).zonas = zv;
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

void SaveFile(vector<zona>zz1)//Archivo pdf para imprimir lista
{
	fstream my_file;

	my_file.open("Lista.pdf", ios::out);

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


void lista_zonas()
{
	string id;
	vector<int>Nzonas;
	vector<zona>zz;
	int z;
	vector<zona>zz2;

	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		cout << setw(20) << "Zona" << setw(20) << "Descripcion" << setw(40) << "Dispositivo" << endl;
		cout << setw(108) << "==============================================================================================" << endl;

		for (int i = 0; i < usuarios.size(); i++)
		{

			if (id == usuarios.at(i).identificacion)
			{
				for (int j = 0; j < usuarios.at(i).zonas.size(); j++)
				{
					Nzonas.push_back(usuarios.at(i).zonas.at(j).z);
					zz.push_back(usuarios.at(i).zonas.at(j));
				}
			}
		}  


		for (int i = 1; i < Nzonas.size(); i++)//for n-1 passes
		{
			//In pass i,compare the first n-i elements
			//with their next elements
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

		for (int i = 0; i < zz2.size(); i++)
		{

			cout << setw(19) << zz2.at(i).z<< setw(11) << setw(10) << zz2.at(i).descrpcion << setw(30) << zz2.at(i).dispositivo << endl;

		}
		SaveFile(zz2);
	}
	else cout << "Usuario no registrado" << endl;
}

void crear_archivo_Bitacora(string bitacora)
{
	fstream Bit;
	string arch = bitacora + ".txt";
	
	Bit.open(arch, ios::out);

	if (!Bit.is_open())
		cout << "Error al abrir archivo" << endl;
	else
	{
		Bit << endl;
		
		Bit << "25.10.2018" << " " << "10:46:45" << " " << "AB12345678" << " " << "ACTIVACION" << " " << "2" << "       " << "Sala" << endl;
		/*for (int i = 0; i < lines.size(); i++)
		{
			Bit << i + 1 << "-" << lines.at(i).fecha << " " << lines.at(i).hora << " " << lines.at(i).id << " " << lines.at(i).balerta << " " << lines.at(i).z_c << " " << lines.at(i).bdescripcion << " " << lines.at(i).accion << " " << lines.at(i).el << endl;
		}*/
	}


}

void leer_AB(string bitacora)
{
	fstream Bit;
	string registro;
	string arch = bitacora + ".txt";

	Bit.open(arch, ios::in);

	if (Bit.fail())
	{

		cout << endl << "Archivo no existente" << endl << endl;

	}
	else
	{
		while (!Bit.eof())
		{

			getline(Bit, registro);
			cout << registro << endl;

		}

		if (Bit.eof())
			cout << endl;
	}

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
				crear_archivo_Bitacora(id);
				leer_AB(id);
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
	string id, con1, con2, cambio, clave;
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
					getline(cin, con1);
					if (validar_palabra_clave(con1))
					{
						contraseñas.push_back(con1);
						cout << "Confirme el codigo de acceso principal: ";
						getline(cin, con2);
						for (int m = 0; m < contraseñas.size(); m++)
						{
							if (contraseñas[m] == con2)
							{
								usuarios.at(i).UsuarioP.codigoP = 0;
								usuarios.at(i).UsuarioP.cod_accesoP = con1;
								Ucontraseña.push_back(id);

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
								getline(cin, clave);
								for (int f = 0; f < usuarios.size(); f++)
								{
									if ((id == usuarios.at(f).identificacion) && (clave == usuarios.at(f).UsuarioP.cod_accesoP))
									{
										cout << "Ingrese codigo de acceso principal: ";
										getline(cin, con1);
										if (validar_palabra_clave(con1))
										{
											contraseñas.push_back(con1);
											cout << "Confirme el codigo de acceso principal: ";
											getline(cin, con2);
											for (int q = 0; q < contraseñas.size(); q++)
											{
												if (contraseñas[q] == con2)
												{
													usuarios.at(f).UsuarioP.codigoP = 0;
													usuarios.at(f).UsuarioP.cod_accesoP = con1;

												}
												else
													cout << "Contraseñas no concuerdan" << endl;
											}
										}
										else
											cout << "Clave debe tener 8 o mas caracteres y al menos 1 mayuscula, 1 minuscula, 1 digito, 1 simbolo y que los caracteres no se repitan 3 o mas veces" << endl << endl;

									}
									else
										cout << "Clave incorrecta" << endl;
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
									getline(cin, con1);
									if (validar_palabra_clave(con1))
									{
										contraseñas.push_back(con1);
										cout << "Confirme el codigo de acceso principal: ";
										getline(cin, con2);
										for (int m = 0; m < contraseñas.size(); m++)
										{
											if (contraseñas[m] == con2)
											{
												usuarios.at(x).UsuarioP.codigoP = 0;
												usuarios.at(x).UsuarioP.cod_accesoP = con1;
												Ucontraseña.push_back(id);

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
}

void establecer_CAS()//Establece codigos secundarios
{
	string id, conP, conS1, conS2,numTel;
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
		getline(cin, conP);
		for (int i = 0; i < usuarios.size(); i++)
		{
			if ((id == usuarios.at(i).identificacion)&&(conP==usuarios.at(i).UsuarioP.cod_accesoP))
			{
				if (usuarios.at(i).UsuariosS.size() == 0)
				{
					cout << "Ingrese número de código: ";
					cin >> numCod;
					ss.codigo = numCod;
					cout << "Codigo de acceso secundario: ";
					cin.ignore();
					getline(cin, conS1);
					if (validar_palabra_clave(conS1))
					{
						contraseñas.push_back(conS1);
						cout << "Confirmacion de codigo de acceso secundario: ";
						getline(cin, conS2);
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
								}
								else
								{
									cout << "Numero de telefono debe tener 8 numeors exactos" << endl;
								}
							}
							else
								cout << "Claves no concuerdan" << endl;
						}

					}
					else
						cout << "Clave debe tener al menos 1 mayuscula, 1 minuscula, 1 digito, 1 simbolo y que los caracteres no se repitan 3 o mas veces" << endl << endl;
				
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
							getline(cin, conS1);
							if (validar_palabra_clave(conS1))
							{
								contraseñas.push_back(conS1);
								cout << "Confirmacion de codigo de acceso secundario: ";
								getline(cin, conS2);
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
										}
										else
										{
											cout << "Numero de telefono debe tener 8 numeors exactos" << endl;
										}
									}
									else
										cout << "Claves no concuerdan" << endl;
								}
							}
							else
								cout << "Clave debe tener al menos 1 mayuscula, 1 minuscula, 1 digito, 1 simbolo y que los caracteres no se repitan 3 o mas veces" << endl << endl;

						}
						else
							cout << "Numero de codigo repetido" << endl;
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
			else if (opcion == "2") { desarmar_sistema(); }
			else if (opcion == "3") { desactivar_sistema(); }
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