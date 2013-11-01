#include <call.h>
#include <gps.h>
#include <GSM.h>
#include <inetGSM.h>
#include <LOG.h>
#include <SIM900.h>
#include <sms.h>
#include <Streaming.h>
#include <WideTextFinder.h>


#include "SensorGPS.h"
#include <Arduino.h>
#include <SoftwareSerial.h>

	
	
SensorGPS::SensorGPS()
{	
  //Serial.begin(9600); // configuro la seriale
}	


// Metodo che legge i valori di longitudine e latitudine
void SensorGPS::letturaGPS(char* lon, char* lat)

{
	GPSGSM gps;// istanzio l'oggetto GPS della classe GSMGPS all'interno del metodo
						//in modo che abbia visibilità solo all'interno del metodo e una volta concluso venga distrutto

        // Configura il GSM
    if (gsm.begin(2400)){
    Serial.println("\n PRONTO");
    gsm.forceON();              
    started=true; 
  }
  else Serial.println("\n INATTIVO");	
						
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
	gps.getPar(lon,lat,alt,tem,vel);
	
	Serial.println((String) lon);
	Serial.println((String) lat);
	Serial.println((String) alt);
	Serial.println((String) tem);
	Serial.println((String) vel);
	delay(100);
}
}


// Metodo che legge ill valore del tempo
void SensorGPS::letturaTempo(char* time)

{
	GPSGSM gps;// istanzio l'oggetto GPS della classe GSMGPS all'interno del metodo
						//in modo che abbia visibilità solo all'interno del metodo e una volta concluso venga distrutto
		
        // Configura il GSM
    if (gsm.begin(2400)){
    Serial.println("\n PRONTO");
    gsm.forceON();              
    started=true; 
  }
  else Serial.println("\n INATTIVO");	
				
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
	gps.getPar(lo,la,alt,time,vel);  
	
	Serial.println((String) lo);
	Serial.println((String) la);
	Serial.println((String) alt);
	Serial.println((String) time);
	Serial.println((String) vel);
	delay(100);
}
}

//Metodo che esegue una trsformazione in un numero reale di un array di catteri corrispondente al tempo
// Input: array di caratteri del tempo letto tramite getPar
// Output: un valore t che è ottenuto tramite conversione di ogni singolo carattere di interesse in un nuemro reale
// con parte intera corrispondente alle ore e parte decimale ai minuti
float SensorGPS::trasformazioneTempo (char * time)

{
	float t;
	// Trasformazione di ogni singolo carattere in float e poi modificato in base alla posizione da occupare nell'orario
        // Attenzione perché l'orario è riferito allo standard quindi Greenwich
	t= ((float)(time[0] - '0')*10) + ((float)(time[1] - '0')) + ((float)(time[2] - '0')/10) + ((float)(time[3] - '0')/100) + 1.0;
        // t= ((float)(time[8] - '0')*10 + 1) + ((float)(time[9] - '0')) + ((float)(time[10] - '0')/10) + ((float)(time[11] - '0')/100);
	Serial.println((String) time);

	return t;
}
