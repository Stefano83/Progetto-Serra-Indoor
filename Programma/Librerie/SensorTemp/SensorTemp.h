#ifndef SensorTemp_h

#define SensorTemp_h

#include <WProgram.h>

// Libreria per la lettura del valore di temperatura dell'aria
// Inpunt: valore ricevuto sul pin digitale collegato al sensore (pin 6 nel nostro caso)
// Output: aggiorna la variabile temp che contiene l'ultimo valore letto dal sensore
	
class SensorTemp
	
{
	
 public:
	// Costruttore: prende in input il pin collegato al sensore
     SensorTemp(int pinTA);
	 // Metodo di aggiornamento del valore della variale temp che prende in input la variabile
	 // e come output ne aggiorna il contenuto
	 void letturaTA(float &);
	
    
	
 private:
	
	 int _pinTA;
	
};
	
#endif