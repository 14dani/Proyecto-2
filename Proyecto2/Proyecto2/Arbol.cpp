#include "pch.h"
#include "Arbol.h"
#include "Nodo.h"
#include <string>
#include "Sistema_alarma.h"
using namespace std;


Arbol::Arbol() // constructor
{
	raiz = nullptr;
}

int indicar_nivel(Nodo* actual)
{
	int contador = 1;
	while (actual->inferior_izquierdo!=nullptr && actual->inferior_derecho!=nullptr )
}

void Arbol::insertar(Sistema_alarma valor) // llega el puntero del nodo a insertar 
{
	Nodo* actual;
	Nodo* actual2;
	Nodo* siguiente_izquierdo;
	Nodo* siguiente_derecho;
	Nodo* a_conectar;
	Nodo* salarma = new Nodo(valor);
	int sw1 = 0;
	int sw2=0;
	if (raiz == nullptr)raiz = salarma;
	else {
		actual = raiz;
		actual2 = raiz;

		while (sw1==0 && sw2==0)
		{
			if (actual->inferior_izquierdo == nullptr || actual->inferior_derecho == nullptr)
			{
				sw1 = 1;
			}
			else if (actual2->inferior_izquierdo == nullptr || actual2->inferior_derecho == nullptr)
			{
				sw2 = 1;
			}

		}

	}
	
}