#pragma once
class Nodo // componentes del nodo
{
private:
	int dato;// datos del nodo, en este caso es solo un entero
	Nodo * ptr_izq;// puntero al nodo izq
	Nodo * ptr_der;// puntero al nodo der
public:
	Nodo(int);// constructor recibiendo datos
};

