#include "pch.h"
#include "Arduino.h"
#include <iostream>
#include <fstream>
using namespace std;


Arduino::Arduino()
{
}


void Arduino::Ejecutar()/////Aqui se hacen las comunicaciones con el arduino.
{
	int estado_dispositivo_1=0;////Estos se convertirian en los valores que provea arduino
	int estado_dispositivo_2=0;////Aqui se harian cambios en los dispositivos
	fstream arduino;
	arduino.open("Arduino.txt", ios::out);
	arduino << estado_dispositivo_1<<endl;
	arduino << estado_dispositivo_2 << endl;
	arduino.close();
}
