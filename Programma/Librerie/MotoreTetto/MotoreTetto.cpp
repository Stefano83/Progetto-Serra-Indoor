#include "MotoreTetto.h"
#include <Arduino.h>



	
	
MotoreTetto::MotoreTetto(int pinDir, int stepperPin)	
{
pinMode(pinDir,OUTPUT); // imposta il pinDir di direzione come OUTPUT in particolare il pin digitale 7
pinMode(stepperPin,OUTPUT); // imposta lo stepperPin di avvio come OUTPUT in particolare il pin digitale 8
_pinDir=pinDir;
_stepperPin=stepperPin;
passi=10000;
}	

// Avvia il movimento del tetto
void MotoreTetto::avvioMotore(bool dir)
	
{
	digitalWrite(_pinDir,dir);  //direzione di rotazione del motore
	delay(50);
  // esegue un passo alla volta fino al numero di passi predefiniti
  for(int i=0;i<passi;i++)
  {
    digitalWrite(_stepperPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_stepperPin, LOW);
    delayMicroseconds(10);
  }
}
