#pragma once
#include <string>
using namespace std;
class Nodo // componentes del nodo
{
private:
	string dato;// datos del nodo, en este caso es solo un entero
	Nodo * superior;// puntero al nodo izq
	Nodo * inferior;// puntero al nodo der
public:
	Nodo(string);// constructor recibiendo datos
	friend class Arbol;
};

