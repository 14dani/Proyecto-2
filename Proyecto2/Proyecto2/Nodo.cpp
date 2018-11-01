#include "pch.h"
#include "Nodo.h"


Nodo::Nodo(int d) // constructor recibiendo datos
{
	dato = d;
	ptr_izq = nullptr;
	ptr_der = nullptr;
}
