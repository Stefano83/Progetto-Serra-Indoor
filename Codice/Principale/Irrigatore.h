#ifndef Irrigatore_h

#define Irrigatore_h

#include <Arduino.h>


// Libreria per la gestione dell'irrigatore
// Inpunt: non dovrebbe essere necessario alcun pin specifico
// Output: 
// pin che attiva l'irrigatore
	
class Irrigatore
	
{
	
 public:
	// Costruttore
     Irrigatore(int pinIrrig);
	// Avvio l'irrigatore
     void avvioIrrigatore();
	// Spegne l'irrigatore 
	 void spegniIrrigatore();
    
	
 private:
	
	 int _pinIrrig;
	
};
	
#endif
