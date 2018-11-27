#pragma once
#include <string>
#include "Sistema_alarma.h"
using namespace std;
class Nodo
{
private:
	Sistema_alarma objeto;// informacion del nodo
	int dato;
	Nodo *p_izq;// puntero hijo izquierdo
	Nodo *p_der;// puntero hijo derecho
public:
	Nodo(Sistema_alarma);
	friend class Arbol_binario;
};


