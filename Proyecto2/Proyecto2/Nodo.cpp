#include "pch.h"
#include "Nodo.h"


Nodo::Nodo(int d) // constructor recibiendo datos
{
	dato = d;
	superior = nullptr;
	inferior = nullptr;
}
