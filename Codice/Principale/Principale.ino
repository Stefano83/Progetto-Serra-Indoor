/*
 *Progetto Serra Indoor
 *
 *Francioso Vincenzo, Salamanna Stefano, Pisanò Luca
 *
 */

// Inclusione librerie predefinite

#include <SoftwareSerial.h>

#include <call.h>
#include <gps.h>
#include <GSM.h>
#include <inetGSM.h>
#include <LOG.h>
#include <SIM900.h>
#include <sms.h>
#include <Streaming.h>
#include <WideTextFinder.h>

#include <ArduinoStream.h>
#include <bufstream.h>
#include <ios.h>
#include <iostream.h>
#include <istream.h>
#include <MinimumSerial.h>
#include <ostream.h>
#include <Sd2Card.h>
#include <SdBaseFile.h>
#include <SdFat.h>
#include <SdFatConfig.h>
#include <SdFatmainpage.h>
#include <SdFatStructs.h>
#include <SdFatUtil.h>
#include <SdFile.h>
#include <SdInfo.h>
#include <SdStream.h>
#include <SdVolume.h>

#include <DHT11.h>

#include <Arduino.h>
#include <SoftwareSerial.h>


//Inclusione delle librerie create per il programma

#include "SensorUmid.h"
#include "SensorTemp.h"
#include "SensorGPS.h"
#include "Irrigatore.h"
#include "MotoreTetto.h"
#include "GestioneIrrig.h"
#include "GestioneSMS.h"
#include "GestioneTemp.h"
#include "GestioneUmid.h"
#include "GestioneSD.h"


//Definizione dei pin di input
int pinUT = A0; // pin collegato al sensore di umidità del terreno
int pinTA = 6; // pin collegato al sensore di temperatura


//Definizione dei pin di output

int pinDir = 7; // pin collegato al motore e che ne stabilisce la direzione di rotazione
int stepperPin = 8; // pin collegato al motore
int pinIrrig = 9; // pin collegato all'irrigatore
int pinSD = 10; // pin collegato con la SD

//Definizione variabili da utilizzare
int vel = 50; // velocità di rotazione del motore
float temp; // temperatura dell'aria
int umid;  // umidità del terreno
char lon[10];   // longitudine
char lat[10];   // latitudine
char time[15];  // tempo

//Definizione variabili di stato da utilizzare
bool irrig=false; // approvazione di irrigazione
bool irriv_av=false;  // irrigazione in corso
bool tetto=false;  // tetto aperto
bool inviato=false; // nessun messaggio è stato inviato senza risposta
bool risposto=false; // indica se è arrivata la risposta a un messagio
bool dir=true; // direzione di rotazione oraria del motore cioè nella direzione che serve a chiudere il tetto


//Costruttori 
//SensorUmid sensorUmid(pinUT);
SensorTemp sensorTemp(pinTA); 
//SensorGPS sensorGPS; 
//MotoreTetto motoreTetto (pinDir,stepperPin,vel);
//Irrigatore irrigatore (pinIrrig);
GestioneIrrig gestioneIrrig; 
GestioneSMS gestioneSMS;
GestioneTemp gestioneTemp;
GestioneUmid gestioneUmid; 
GestioneSD gestioneSD(pinSD);

void setup(){
  
  Serial.begin(9600);
  while (!Serial) {}
}

void loop(){
  
  sensorTemp.letturaTA (temp);
  gestioneUmid.ControlloUmid(pinUT, stepperPin, pinDir, pinSD, vel, umid, lon, lat, dir, tetto, inviato, risposto, time);
  gestioneTemp.ControlloTemp(pinTA, stepperPin, pinDir, pinSD, vel, umid, temp, tetto, dir, time);
  
  if (inviato && !risposto)
  {gestioneSMS.controlloSMS(irrig, inviato, risposto);}
  
  if (irrig)
  {gestioneIrrig.controlloIrrig(pinIrrig, pinUT, pinSD, umid, irrig, time);}
  
  gestioneSD.invioDati(time);
  
  delay(600000);
}

