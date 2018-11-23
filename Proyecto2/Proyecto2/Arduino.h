#pragma once
#include <iostream>
#include <string>
using namespace std;
class Arduino
{
private:
	string dispositivo_1;
	string dispositivo_2;
	friend void Ejecutar();
	friend int monitorear();
public:
	Arduino();
	void proveer();
	
};

