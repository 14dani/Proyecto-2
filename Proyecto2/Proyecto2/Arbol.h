#pragma once
#include "Nodo.h"
#include <iostream>
#include <string>
using namespace std;

class Arbol
{
	Nodo * raiz; //
public:
	Arbol();
	void insertar(string);
	Nodo* insertar_nodo(Nodo*, Nodo*); 
	void recorrer(); 
	void en_orden(Nodo*); 
	Nodo* buscar(string);
	Nodo* buscar_nodo(Nodo*, string);
	Nodo* buscar_nodo_iterativo(string);
	friend class Sistema_alarma;
};


