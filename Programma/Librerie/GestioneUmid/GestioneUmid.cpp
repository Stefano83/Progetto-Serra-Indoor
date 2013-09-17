#include <wprogram.h>
#include "SensorUmid.h"
#include "GestioneUmid.h"
#include "MotoreTetto.h"
#include <Arduino.h>
#include <SoftwareSerial.h>

	
	
GestioneUmid::GestioneUmid()
{
Serial.begin(9600); // configuro la seriale
UMIDTERR_MAX=700;
UMIDTERR_MIN=200;
}	


GestioneUmid::controlloUmid(int & umid, boolean & tetto, boolean & inviato, boolean & dir)
{
  SensorUmid.letturaUT(umid);  // lettura del valore di umidità del terreno
  if(umid > UMIDTERR_MAX && !tetto)  // controllo se l'umidità rilevata è sotto un certo valore altrimenti passo il comando alla funzione di chiusura del tetto
  {
     MotoreTetto.AvvioMotore(dir, passi); // chiudo il tetto
	 dir = false; // imposto la direzzione contraria di rotazione
	 tetto = true; // imposto la variabile di stato del tetto a true cioè il tetto è chiuso
  }
  
  else if(umid < UMIDTERR_MIN && !inviato) // controllo se l'umidità rilevata è sopra un certo valore altrimenti invio messaggio di approvazione irrigazione
  {
      inviato = gestioneSMS.invioSMS();  // invio messaggio di approvazione irrigazione
  }
}
}