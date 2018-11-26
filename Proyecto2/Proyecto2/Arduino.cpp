#include "pch.h"
#include "Arduino.h"
#include <iostream>
#include<thread>
#include <string>
using namespace std;


Arduino::Arduino()
{
}
string dispositivo_1;
string dispositivo_2;

void Arduino::proveer()/////Aqui se envian los datos en terminos activos o desactivos.
{
	
	dispositivo_1 = "DESACTIVADO";
	dispositivo_2 = "DESACTIVADO";
	this->dispositivo_1 = dispositivo_1;
	this->dispositivo_2 = dispositivo_2;
}
