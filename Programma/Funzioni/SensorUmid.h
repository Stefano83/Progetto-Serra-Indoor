#ifndef SensorUmid_h

#define SensorUmid_h

#include <WProgram.h>

// Libreria per la lettura del valore di umidità del terreno
// Inpunt: valore ricevuto sul pin analogico collegato al sensore (A0 in questo caso)
// Output: aggiorna la variabile umid che contiene l'ultimo valore letto dal sensore
	
class SensorUmid
	
{
	
 public:
	// Costruttore: prende in input il pin collegato al sensore
     SensorUmid(int pinUT);
	 // Metodo di aggiornamento del valore della variale umid che prende in input la variabile
	 // e come output ne aggiorna il contenuto
	 void letturaUT(int &);
	
    
	
 private:
	
	 int _pinUT;
	
};
	
#endif