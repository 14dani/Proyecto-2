// Proyecto2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "Monitoreo.h"
using namespace std;

int main()
{
	Monitoreo m;
	m.Menu();
	string frase;
	cout << "escriba una frase cifrada" << endl;
	cin.ignore();
	getline(cin, frase);
	int n = 1;
	for (int tamano = 0; tamano < frase.size(); tamano++)
	{
		char letra = frase[tamano] - n;
		cout << letra;
		n++;
		if (n > 10)
		{
			n = 1;
		}
	}
}

