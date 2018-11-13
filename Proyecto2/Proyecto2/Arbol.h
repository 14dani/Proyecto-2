#pragma once
#include "Nodo.h"
#include <iostream>
using namespace std;
class Arbol
{
	Nodo * raiz; //
public:
	Arbol();
	void insertar(int); 
	Nodo* insertar_nodo(Nodo*, Nodo*); 
	void recorrer(); 
	void en_orden(Nodo*); 
	Nodo* buscar(int); 
	Nodo* buscar_nodo(Nodo*, int); 
	Nodo* buscar_nodo_iterativo(int);
	friend class Sistema_alarma;
};


