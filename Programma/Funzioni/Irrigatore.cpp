#include <wprogram.h>
#include "Irrigatore.h"
#include <Arduino.h>

	
	
Irrigatore::Irrigatore(int pinIrrig)
{
pinMode(pinIrrig, OUTPUT); // imposto il pinIrrig come OUTPUT in particolare il pin digitale 9
_pinIrrig=pinIrrig;
}	


void Irrigatore::avvioIrrigatore()
{
	digitalWrite(_pinIrrig,HIGH ); // Avvio l'irrigatore
}


void Irrigatore::spegniIrrigatore()
{
	digitalWrite(_pinIrrig, LOW); // Spengo l'irrigatore
}	
