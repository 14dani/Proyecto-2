// Proyecto2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "Monitoreo.h"
#include "Sistema_alarma.h"
#include <thread>
#include <chrono>
#include <fstream>
using namespace std;


int main()
{
	Monitoreo m;
	Sistema_alarma ss;
	string comando;
	while (true) {
		cout << "Presione m si desea consultar el sistema de monitoreo, ss si desea consultar la alarma.";
		getline(cin, comando);
		if (comando == "m")
			m.Menu();
		else
			ss.Menu();
	}
}


