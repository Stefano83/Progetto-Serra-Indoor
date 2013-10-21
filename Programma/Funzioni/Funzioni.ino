// Includo tutte le librerie create

#include "SensorUmid.h"
#include "SensorTemp.h"
#include "SensorGPS.h"
#include "Irrigatore.h"
#include "MotoreTetto.h"
#include "GestioneIrrig.h"
#include "GestioneSMS.h"
#include "GestioneTemp.h"
#include "GestioneUmid.h"

// Costruttori

SensorUmid sensorUmid(A0);
SensorTemp sensorTemp(6);
SensorGPS sensorGPS();
GestioneIrrig gestioneIrrig();
GestioneSMS gestioneSMS();
GestioneTemp gestioneTemp();
GestioneUmid gestioneUmid(); 
MotoreTetto motoreTetto (7,8,50);
Irrigatore irrigatore (9);

// Variabili

float temp; // temperatura dell'aria
int umid;  // umidità del terreno
char lon[10];   // longitudine
char lat[10];   // latitudine
char time[15];  // tempo

// Variabili di stato

boolean irrig=false; // approvazione di irrigazione
boolean irriv_av=false;  // irrigazione in corso
boolean tetto=false;  // tetto aperto
boolean inviato=false; // nessun messaggio è stato inviato senza risposta
boolean risposto=false;
boolean dir=true; // direzione di rotazione oraria del motore cioè nella direzione che serve a chiudere il tetto

void setup()
{}

void loop() {

  GestioneUmid.controlloUmid(umid, tetto, inviato, dir);
  GestioneTemp.controlloTemp(umid, temp, tetto, dir);
  
  if (inviato && !risposto)
  {GestioneSMS.controlloSMS(irrig);}
  
  if (irrig)
  {GestioneIrrig.controlloIrrig(umid, irrig, time);}
  
  delay(600000);
*/
irrigatore.avvioIrrigatore ();
delay (1000);
motoreTetto.avvioMotore (dir);
}

