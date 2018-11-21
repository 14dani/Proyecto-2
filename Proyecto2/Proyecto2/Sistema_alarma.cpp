#include "pch.h"
#include "Sistema_alarma.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono> 
using namespace std;

Sistema_alarma::Sistema_alarma()
{
}

void monitorear(int estado)
{

}

void modificar_estado(int tipo, string estado_cambiado)
{
	string segunda_lineas;
	if (tipo == 1)
	{

	}
}
void alerta(int estado)
{
	while (true) {
		cout << endl << "ALERTA" << endl;
		this_thread::sleep_for(chrono::seconds(2));
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


bool telefono1(string numero) //verifica que la identificacion sea de 10 o más caracteres
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

int ToInt1(string s) //Funcion que convierte lo telefono en int
{
	stringstream ss(s);
	int x = 0;
	ss >> x;
	return x;
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
	string id,con1,con2;
	vector<string>contraseñas;
	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		for (int i = 0; i < usuarios.size(); i++)
		{
			if (id == usuarios.at(i).identificacion)
			{
				cout << "Ingrese codigo de acceso principal: ";
				getline(cin, con1);
				contraseñas.push_back(con1);
				cout << "Confirme el codigo de acceso principal: ";
				getline(cin, con2);
				for (int m = 0; m < contraseñas.size(); m++)
				{
					if (contraseñas[m] == con2)
					{
						usuarios.at(i).UsuarioP.codigoP = 0;
						usuarios.at(i).UsuarioP.cod_accesoP = con1;

					}
					else
						cout << "Contraseñas no concuerdan" << endl;
				}


			}
		}
	}
	else cout << "Usuario no registrado" << endl;
}

void establecer_CAS()
{
	string id, conP, conS1, conS2,numTel;
	int numCod;
	string Cod, nombre;
	U_secundario ss;
	vector<U_secundario>us;
	vector<string>contraseñas;


	cout << "Ingrese usuario o la identificacion: ";
	getline(cin, id);
	if (RecorrerIden(id))
	{
		cout << "Ingrese codigo de acceso principal: ";
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
					getline(cin, conS1);
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
							cout << "Contraseñas no concuerdan" << endl;
					}
				
				}
				/*for (int g = 0; g < usuarios.at(i).UsuariosS.size(); g++)
				{
					
				}*/
			}
		}
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

int Sistema_alarma::Menu()/*Estado es un interruptor que indica si se esta llamando a la funcion para consultar el estado 
									 o para correr el menu, tipo es el dato de quien esta haciendo la consulta*/
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

			if (opcion == "0")return 0;
			else if (opcion == "1") {alerta(0);
			}
			else if (opcion == "2")desarmar_sistema;
			else if (opcion == "3")desactivar_sistema();
			else if (opcion == "4")programar_zonas();
			else if (opcion == "5") {
				lista_zonas();
			}
			else if (opcion == "6")bitacora();
			else if (opcion == "7")borrar_bitacora();
			else if (opcion == "8")establecer_CAP();
			else if (opcion == "9")establecer_CAS();
			//else if (opcion == "10")armar_sistema();
			//else if (opcion == "11")armar_sistema();


		}

}