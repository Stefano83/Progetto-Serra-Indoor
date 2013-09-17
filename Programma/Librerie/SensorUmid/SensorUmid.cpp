#include <wprogram.h>
#include "SensorUmid.h"
#include <SoftwareSerial.h>
#include <Arduino.h>
	
	
SensorUmid::SensorUmid(int pinUT)
{
Serial.begin(9600); // configuro la seriale
pinMode(pinUT,INPUT);
_pinUT=pinUT;
}	

void SensorUmid::letturaUT(int & umid)
	
{
	umid = analogRead(_pinUT);
	Serial.print("Umidità Terreno: "); // stampo sulla seriale valore di umidità del terreno appena letto
	Serial.println(umidTerr);
	delay(100);
}
