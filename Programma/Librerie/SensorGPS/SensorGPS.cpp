#include <wprogram.h>
#include "SensorGPS.h"
#include <Arduino.h>
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "gps.h "

	
	
SensorGPS::SensorGPS()
{	
	Serial.begin(9600); // configuro la seriale
	// Configura il GSM
	if (gsm.begin(2400)){
    Serial.println("\n PRONTO");
    gsm.forceON();              
    started=true; 
  }
  else Serial.println("\n INATTIVO");
}	


// Metodo che legge i valori di longitudine e latitudine
void SensorGPS::letturaGPS(char* lon, char* lat)

{
	GSMGPS gps// istanzio l'oggetto GPS della classe GSMGPS all'interno del metodo
						//in modo che abbia visibilità solo all'interno del metodo e una volta concluso venga distrutto
						
	char tem[15]; // array usato in maniera fittizia per la lettura congiunta di tutti i valori attraverso il metodo getPar
	char alt[10]; // array usato in maniera fittizia per la lettura congiunta di tutti i valori attraverso il metodo getPar
	char vel[10]; // array usato in maniera fittizia per la lettura congiunta di tutti i valori attraverso il metodo getPar
	
	// attivo il GPS
  if(started){
    if (gps.attachGPS())
      Serial.println("GPS ATTIVO");
    else Serial.println("ERRORE");
 
    delay(2000);
	
	// Metodo che restituisce i valori di longitudine, latitudine, altitudine, velocità e tempo
	// Input: 5 array di caratteri
	// Output: aggiorna il contenuto degli array realtitti alle diverse grandezze
	gps.getPar(lon,lat,alt,time,vel);  
	
	Serial.println((String) lon);
	Serial.println((String) lat);
	Serial.println((String) alt);
	Serial.println((String) time);
	Serial.println((String) vel);
	delay(100);
}


// Metodo che legge ill valore del tempo
void SensorGPS::letturaTempo(char* time)

{
	GSMGPS gps// istanzio l'oggetto GPS della classe GSMGPS all'interno del metodo
						//in modo che abbia visibilità solo all'interno del metodo e una volta concluso venga distrutto
						
	char lo[10]; // array usato in maniera fittizia per la lettura congiunta di tutti i valori attraverso il metodo getPar					
	char la[10]; // array usato in maniera fittizia per la lettura congiunta di tutti i valori attraverso il metodo getPar
	char alt[10]; // array usato in maniera fittizia per la lettura congiunta di tutti i valori attraverso il metodo getPar
	char vel[10]; // array usato in maniera fittizia per la lettura congiunta di tutti i valori attraverso il metodo getPar
	
	// attivo il GPS
  if(started){
    if (gps.attachGPS())
      Serial.println("GPS ATTIVO");
    else Serial.println("ERRORE");
 
    delay(2000);
	
	// Metodo che restituisce i valori di longitudine, latitudine, altitudine, velocità e tempo
	// Input: 5 array di caratteri
	// Output: aggiorna il contenuto degli array realtitti alle diverse grandezze
	gps.getPar(lon,lat,alt,time,vel);  
	
	Serial.println((String) lon);
	Serial.println((String) lat);
	Serial.println((String) alt);
	Serial.println((String) time);
	Serial.println((String) vel);
	delay(100);
}

//Metodo che esegue una trsformazione in un numero reale di un array di catteri corrispondente al tempo
// Input: array di caratteri del tempo letto tramite getPar
// Output: un valore t che è ottenuto tramite conversione di ogni singolo carattere di interesse in un nuemro reale
// con parte intera corrispondente alle ore e parte decimale ai minuti
float trasformazioneTempo (char * time)

{
	float t;
	// Trasformazione di ogni singolo carattere in float e poi modificato in base alla posizione da occupare nell'orario
	t= ((float)(time[8] - '0')*10) + ((float)(time[9] - '0')) + ((float)(time[10] - '0')/10) + ((float)(time[11] - '0')/100);
	Serial.println((String) t);
	return t;
}