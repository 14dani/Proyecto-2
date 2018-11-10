#pragma once
class Nodo // componentes del nodo
{
private:
	int dato;// datos del nodo, en este caso es solo un entero
	Nodo * superior;// puntero al nodo izq
	Nodo * inferior;// puntero al nodo der
public:
	Nodo(int);// constructor recibiendo datos
	friend class Arbol;
};

