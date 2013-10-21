#include "GestioneSD.h"
#include <Arduino.h>
#include <SD.h>
#include <SoftwareSerial.h>

	
GestioneSD::GestioneSD(int pinSD)	
{
pinMode(pinSD,OUTPUT); // imposta il pinSD come OUTPUT in particolare il pin digitale 10
_pinSD=pinSD;
}	

// Scrive valori di temperatura e umidità del terreno in un file di testo nella SD
void GestioneSD::valoriSD(int & temp, int & umt)
	
{
//creo un oggetto dalla classe File
	File FileSD;
//inizializza la classe e specifica
//il pin SD Card
	if (SD.begin(_pinSD) == true)
    //inizializzazione ok
{
	
//Apro un file di testo in modalità scrittura che nomino con 
    FileSD = SD.open("Valori.txt", FILE_WRITE);
//se non ci sono problemi nell'apertura dei file scrivo
//al suo interno
	if (FileSD != false)
	{
		FileSD.println("Temp:" + temp);
		FileSD.println("Umid:" + umt);
//chiudo il file
		FileSD.close();
			}
	
	
	else
    //problemi nell'apertura del file
	Serial.println("\n ERRORE APERTURA");
	
  }
  else
  //problemi nell'inizializzazione
	Serial.println("\n ERRORE INIZIALIZZAZIONE");
}


// Salva messaggi di risposta in un file di testo nella SD
void GestioneSD::msgSD(char* msg)
	
{
//creo un oggetto dalla classe File
	File FileSD;
//inizializza la classe e specifica
//il pin SD Card
	if (SD.begin(_pinSD) == true)
    //inizializzazione ok
{
	
//Apro un file di testo in modalità scrittura che nomino con 
    FileSD = SD.open("Messaggi.txt", FILE_WRITE);
//se non ci sono problemi nell'apertura dei file scrivo
//al suo interno
	if (FileSD != false)
	{
		FileSD.println("Messaggio:" + (String)msg);
//chiudo il file
		FileSD.close();
			}
	
	
	else
    //problemi nell'apertura del file
	Serial.println("\n ERRORE APERTURA");
	
  }
  else
  //problemi nell'inizializzazione
	Serial.println("\n ERRORE INIZIALIZZAZIONE");
}
