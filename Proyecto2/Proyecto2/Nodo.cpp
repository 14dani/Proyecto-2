#include "pch.h"
#include "Nodo.h"
#include <string>
#include "Sistema_alarma.h"
using namespace std;


Nodo::Nodo(Sistema_alarma d) // constructor recibiendo datos
{
	Sistema_alarma dato = d;
	superior = nullptr;
	inferior_izquierdo = nullptr;
	inferior_derecho = nullptr;
}