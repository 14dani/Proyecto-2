#include "pch.h"
#include "Nodo.h"
#include <string>
#include "Sistema_alarma.h"
using namespace std;

Nodo::Nodo(int d) // constructor
{
	dato = d;
	p_izq = nullptr;
	p_der = nullptr;
}

