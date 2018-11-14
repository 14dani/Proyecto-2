#include "pch.h"
#include "Arbol.h"
#include "Nodo.h"
#include <string>
using namespace std;


Arbol::Arbol() // constructor
{
	raiz = nullptr;
}

void Arbol::insertar(string valor) // llega el puntero del nodo a insertar 
{
	Nodo* ptr = new Nodo(valor);
	raiz = insertar_nodo(raiz, ptr); // envia punteros de la raiz y del nodo a insertar 
}

Nodo* Arbol::insertar_nodo(Nodo *ptr_raiz, Nodo *ptr)
{
	if (ptr_raiz == nullptr)
		ptr_raiz = ptr;
	else
		if (ptr->dato <= ptr_raiz->dato) // nodos <= raiz van a su izquierda 
			ptr_raiz->superior = insertar_nodo(ptr_raiz->superior, ptr);
		else // nodos > raiz van a su derecha 
			ptr_raiz->inferior = insertar_nodo(ptr_raiz->inferior, ptr);
	return ptr_raiz;
}

void Arbol::recorrer()  // inicia el recorrido por la raiz del arbol 
{
	en_orden(raiz);
	system("pause");
}
void Arbol::en_orden(Nodo *ptr) // recorrido I-R-D
{
	if (ptr != nullptr)
	{
		en_orden(ptr->superior);
		cout << ptr->dato << endl;
		en_orden(ptr->inferior);
	}
}

Nodo* Arbol::buscar(string valor)
{
	return buscar_nodo(raiz, valor);
}

Nodo* Arbol::buscar_nodo(Nodo* ptr_raiz, string valor)
{
	if (ptr_raiz == nullptr) // caso base 1: algoritmo termina si arbol vacio o no esta el valor
		return nullptr;
	if (valor == ptr_raiz->dato)  // caso base 2: dato encontrado 
		return ptr_raiz;
	if (valor <= ptr_raiz->dato)  // la funcion mueve punteros segun el valor sea <= o > raiz
		return buscar_nodo(ptr_raiz->superior, valor); // se mueve por el hijo izquierdo <= 
	else
		return buscar_nodo(ptr_raiz->inferior, valor); // se mueve por el hijo derecho > 
}

Nodo* Arbol::buscar_nodo_iterativo(string valor)
{
	Nodo* ptr_raiz = raiz;
	while (ptr_raiz != nullptr)
	{
		if (valor == ptr_raiz->dato)
			break;
		if (valor <= ptr_raiz->dato)
			ptr_raiz = ptr_raiz->superior;
		else ptr_raiz = ptr_raiz->inferior;
	}
	return ptr_raiz;
}