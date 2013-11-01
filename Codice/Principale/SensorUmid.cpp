
#include "SensorUmid.h"
#include <Arduino.h>
#include <SoftwareSerial.h>
	
	
SensorUmid::SensorUmid(int pinUT)
{
//Serial.begin(9600); // configuro la seriale
pinMode(pinUT,INPUT);
_pinUT=pinUT;
}	

void SensorUmid::letturaUT(int & umid)
	
{
	umid = analogRead(_pinUT);
	Serial.print("Umidità Terreno: "); // stampo sulla seriale valore di umidità del terreno appena letto
	Serial.println(umid);
	delay(100);
}
