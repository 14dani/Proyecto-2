#pragma once
class Nodo
{
private:
	int dato;// informacion del nodo
	Nodo *p_izq;// puntero hijo izquierdo
	Nodo *p_der;// puntero hijo derecho
public:
	Nodo(int);
	friend class Arbol;
};
