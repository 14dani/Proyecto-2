// Proyecto2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "Monitoreo.h"
#include "Sistema_alarma.h"
using namespace std;

int main()
{
	Monitoreo m;
	m.Menu();
	Sistema_alarma ss;
	ss.Menu();
}

