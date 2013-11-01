#ifndef SensorGPS_h

#define SensorGPS_h

#include <Arduino.h>


// Libreria per la lettura del valore della posizione tramite GPS
// Inpunt: legge il valore di umidità del terreno dal sensore
// Output: aggiorna la variabile:
// lon che contiene l'ultimo valore della longitudine letto
// lon che contiene l'ultimo valore della latitudine letto
// lon che contiene l'ultimo valore ti tempo letto

	
class SensorGPS
	
{
	
 public:
	// Costruttore: non prende niente in input mentre come output attiva il GPS
     SensorGPS();
	 // Metodo di aggiornamento del valore degli array lon, lat che prende in input gli array
	 // e come output ne aggiorna il contenuto
	 void letturaGPS (char *, char *);
	 // Metodo di aggiornamento del valore dell'array time che prende in input l'array
	 // e come output ne aggiorna il contenuto
	 void letturaTempo(char *);
	 // Metodo che serve a trasformare l'orario letto dal GPS e messo in un array di caratteri in un numero reale
	 // Input: prende l'array di caratteri time
	 // Output: restituisce un numero reale che corrisponde all'orario in minuti e secondi dell'ultima lettura GPS
	 float trasformazioneTempo (char *);
	
    
	
 private:
	
	bool started; // variabile di stato
     
	
};
	
#endif
