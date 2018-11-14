#include "pch.h"
#include "Nodo.h"
#include <string>
using namespace std;


Nodo::Nodo(string d) // constructor recibiendo datos
{
	dato = d;
	superior = nullptr;
	inferior = nullptr;
}