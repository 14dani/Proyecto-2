#include "pch.h"

#include "Nodo.h"
#include "Arbol.h"

Arbol::Arbol() // constructor
{
	raiz = nullptr;
}

void Arbol::insertar(int valor) // llega el puntero del nodo a insertar
{
	Nodo* ptr = new Nodo(valor);
	raiz = insertar_nodo(raiz, ptr); // envia punteros de la raiz y del nodo a insertar
}
Nodo* Arbol::insertar_nodo(Nodo *ptr_raiz, Nodo *ptr)
{
	if (ptr_raiz == nullptr)
		ptr_raiz = ptr;
	else
		if (ptr->dato <= ptr_raiz->dato)
			// nodos <= raiz van a su izquierda
			ptr_raiz->p_izq = insertar_nodo(ptr_raiz->p_izq, ptr);
		else
			// nodos > raiz van a su derecha
			ptr_raiz->p_der = insertar_nodo(ptr_raiz->p_der, ptr);
	return ptr_raiz;
}