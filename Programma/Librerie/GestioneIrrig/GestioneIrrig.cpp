#include <wprogram.h>
#include "SensorUmid.h"
#include "GestioneIrrig.h"
//#include "SensorGPS.h"
#include "Irrigatore.h"
#include <Arduino.h>
#include <SoftwareSerial.h>

	
// Costruttore: imposta i valori della variabili di stato e della variabili con i valori da confrontare 	
GestioneIrrig::GestioneIrrig()
{
	Serial.begin(9600); // configuro la seriale
	irrig_av=false;
    UMIDTERR_MAX3=650;
	ORARIO_IN=18.00;
	ORARIO_FIN=19.30;
}	


// Metodo che gestisce se e quando avviare l'irrigazione e se e quando spegnere l'irrigatore
void GestioneIrrig::controlloIrrig(int pinIrrig, int pinUT, int & umid, bool & irrig, char * time)
{
	if(!irrig_av)
	{
/*    SensorGPS sensorGPS;
	  sensorGPS.letturaTempo(time);  // lettura del valore di tempo
	  float t = sensorGPS.trasformazioneTempo(time); // trasformo alcuni pezzi(quelli che equivalgono a ore e minuti) dell'array di caratteri in float
		// Controllo se sono nella fascia orario prestabilita per l'irrigazione e se l'irrigazione non sia stata già avviata
		if (t >= ORARIO_IN && t <= ORARIO_FIN)
		  {
			Serial.println("IRRIGAZIONE INIZIATA");
            Irrigatore irrigatore(pinIrrig);
			irrigatore.avvioIrrigatore(); // Avvio l'irrigazione
			irrig_av=true; // imposta la variabile di stato a true cioè irrigazione avviata
		  }
		else 
		  {
			Serial.println("FASCIA ORARIA NON RISPETTATA: IRRIGAZIONE NON INIZIATA");
		  }*/
		}
		
	
	else
	{
        SensorUmid sensorUmid(pinUT);
		sensorUmid.letturaUT(umid); // leggo il valore di umidità del terreno
		if(umid > UMIDTERR_MAX3)  // controllo se l'umidità rilevata è maggiore di un certo valore, se così fosse spengo l'irrigatore
		  {
            Irrigatore irrigatore(pinIrrig);
			irrigatore.spegniIrrigatore();
			irrig_av=false; // imposto la variabile di stato a false cioè irrigazione finita
			irrig=false; // imposto la variabile di stato a false cioè in attesa della prossima approvazione di irrigazione
		  }
	}
}
