#pragma once
#include "nodo.h"
#include <iostream>
using namespace std;
class Arbol
{
private:
	Nodo * raiz; // mantiene la raiz de todo el arbol
public:
	Arbol();
	void insertar(int);
	Nodo* insertar_nodo(Nodo*, Nodo*);
};


