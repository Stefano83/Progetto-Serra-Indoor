#ifndef GestioneSD_h

#define GestioneSD_h

#include <WProgram.h>

// Libreria per la gestione della SD card
// Inpunt: valori letti dai sensori
// Output: 
// salvare i dati in un file sulla SD card attraverso il PIN collegato alla SD

class GestioneSD
	
{
	
 public:
	// Costruttore
     GestioneSD(int);
	// Metodo che prende in input i valori letti dai sensori e li salva in un file sulla SD card
     void valoriSD(int &, int &);
	// Metodo che prende in input il messaggio di risposta e lo salva in un file
     void msgSD(char *);;
    
	
 private:
	
     int _pinSD;
	
};
	
#endif
