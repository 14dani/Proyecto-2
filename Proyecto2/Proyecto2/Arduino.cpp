#include "pch.h"
#include "Arduino.h"
#include <iostream>
#include <fstream>
#include<thread>
using namespace std;

string estado_dispositivo_1 = "0";////Estos se convertirian en los valores que provea arduino
string estado_dispositivo_2 = "0";////Aqui se harian cambios en los dispositivos
fstream arduino;

Arduino::Arduino()
{
}

int esperar3ss()//////Funcion de esperar para estado de alerta.
{
	if (arduino.is_open())
	{
		this_thread::sleep_for(chrono::seconds(1));
		esperar3ss();
	}
	else return NULL;
}
void Arduino::Ejecutar()/////Aqui se hacen las comunicaciones con el arduino.
{
	esperar3ss();
	arduino.open("Arduino.txt", ios::out);
	arduino << "ACTIVADO"<<endl;
	arduino << "NO ACTIVADO" << endl;
	arduino.close();
}
