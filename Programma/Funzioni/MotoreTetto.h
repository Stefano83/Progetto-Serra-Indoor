#ifndef MotoreTetto_h

#define MotoreTetto_h

#include <WProgram.h>

// Libreria per la gestione del motore che gestisce il tetto
// Inpunt: non dovrebbe essere necessario alcun pin specifico
// Output: 
// pin che imposta la direzione di rotazione
// pin che attiva il motore

class MotoreTetto
	
{
	
 public:
	// Costruttore
     MotoreTetto(int pinDir, int stepperPin,int vel);
	// Metodo che avvia il motore con una certa direzione di rotazione e per un numero di passi definito in base alla distanza da chiudere
     void avvioMotore(bool); 
	
    
	
 private:
	
     int _pinDir;
	 int _stepperPin;
	 int _vel;
	 int passi;
	
};
	
#endif
