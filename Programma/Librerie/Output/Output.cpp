#include <DHT11.h>	
#include <wprogram.h>
#include "Output.h"
#include <Arduino.h>
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "gps.h "
#include "sms.h"


	
	
Output::Output(int pinDir, int stepperPin, int pinIrrig)
	
{
	
pinMode(pinDir,OUTPUT);
pinMode(stepperPin,OUTPUT);
pinMode(pinIrrig, OUTPUT);
_pinDir=pinDir;
_stepperPin=stepperPin;
_pinIrrig=pinIrrig;
}	

void Output::avvioMotore(bool dir, int passi)
	
{
	digitalWrite(_pinDir,dir);  //direzione di rotazione del motore
	delay(50);
  for(int i=0;i<passi;i++)
  {
    digitalWrite(_stepperPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_stepperPin, LOW);
    delayMicroseconds(10);
  }
}


void Output::avvioIrrigatore()
{
	digitalWrite(_pinIrrig,HIGH );
}


void Output::spegniIrrigatore()
{
	digitalWrite(_pinIrrig, LOW);
}	


bool Output::invioSMS(char * numero, char * messaggio)
{
	SMSGSM sms; // Creiamo un oggetto sms della classe SMSGSM
	if(sms.SendSMS(numero, messaggio))
	return true;
	else return false;
}



void Output::cancellazioneSMS(int pos)
{
	SMSGSM sms; // Creiamo un oggetto sms della classe SMSGSM
	sms.DeleteSMS(pos);
}