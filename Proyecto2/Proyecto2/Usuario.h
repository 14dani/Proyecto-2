#pragma once
#include <string>
using namespace std;
class Usuario
{
	string identificacion;
	int codigo;
	string cod_acceso;
	string nombre;
	string tipo_de_propiedad;
	string direccion;
	int telefono1;
	int telefono2;
	string correo;
	int el;

public:
	Usuario();
	Usuario(string, string, string, string, int, int, string, int);
	Usuario(int, string);
	Usuario(int, string, string, int);
	~Usuario();
	bool RecorrenUsuarios(string);
	void Establecer_Usuarios(string);
	void ExtraerInfoM(string);
	void CrearUsuario(string);
	void eliminar_Usuario();
	void SaveFile();

	friend class Sistema_alarma;
	friend class Monitoreo;
};

