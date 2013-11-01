#include "SensorGPS.h"
#include "GestioneSD.h"
#include "SensorUmid.h"
#include "GestioneUmid.h"
#include "GestioneSMS.h"
#include "MotoreTetto.h"
#include <Arduino.h>
#include <SoftwareSerial.h>

	
	
GestioneUmid::GestioneUmid()
{
//Serial.begin(9600); // configuro la seriale
UMIDTERR_MAX=700;
UMIDTERR_MIN=200;
}	


void GestioneUmid::ControlloUmid(int pinUT, int stepperPin, int pinDir, int pinSD, int vel, int & umid, char * lon, char * lat, bool & dir, bool & tetto, bool & inviato, bool & risposto, char * time)
{
	SensorUmid sensorUmid(pinUT);
	sensorUmid.letturaUT(umid);  // lettura del valore di umidità del terreno
	SensorGPS sensorGPS;
	sensorGPS.letturaTempo(time);  // lettura del valore di tempo
		
	GestioneSD gestioneSD(pinSD);
	gestioneSD.umtSD(umid, time);
  
  if(umid > UMIDTERR_MAX && !tetto)  // controllo se l'umidità rilevata è sotto un certo valore altrimenti passo il comando alla funzione di chiusura del tetto
  {
     MotoreTetto motoreTetto(stepperPin, pinDir, vel);
     motoreTetto.avvioMotore(dir); // chiudo il tetto
	 dir = false; // imposto la direzzione contraria di rotazione
	 tetto = true; // imposto la variabile di stato del tetto a true cioè il tetto è chiuso
  }
  
  else if(umid < UMIDTERR_MIN && !inviato) // controllo se l'umidità rilevata è sopra un certo valore altrimenti invio messaggio di approvazione irrigazione
  {
   GestioneSMS gestioneSMS;
   inviato = gestioneSMS.invioSMS(inviato, risposto, lon, lat);  // invio messaggio di approvazione irrigazione
  }
}

