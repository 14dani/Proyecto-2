#pragma once
#include <string>
#include "Sistema_alarma.h"
using namespace std;
class Nodo // componentes del nodo
{
private:
	string dato;// datos del nodo, en este caso es solo un string por la identificacion
	Nodo * superior;// puntero al nodo izq
	Nodo * inferior_izquierdo;// puntero al nodo der
	Nodo * inferior_derecho;
public:
	Nodo(Sistema_alarma);// constructor recibiendo datos
	friend class Arbol;
	friend int indicar_nivel(Nodo*);
};


