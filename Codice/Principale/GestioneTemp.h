#ifndef GestioneTemp_h
#define GestioneTemp_h
#include <Arduino.h>



// Libreria per la gestione del valore di umidità del terreno
// Inpunt: non dovrebbe essere necessario alcun pin specifico
// Output: 
// chiude il tetto per deteminati valori di temperatura
// apre il tetto per deteminati valori di temperatura e umidità del terreno


class GestioneTemp
	
{
	
 public:
	 // Costruttore: non prende niente in input mentre come output stabilisce i valori da confrontare con il valore letto dal sensore
         GestioneTemp();
	 // Legge e controlla il valore di umidità deal sensore e in base al valore letto può:
	 // chiudere il tetto o inviare messaggio di approvazione o non fa niente
	 void ControlloTemp(int, int, int, int, int, int &, float &, bool &, bool &, char *);
	 
	
    
	
 private:
 
 int UMIDTERR_MAX2; // valore di umidità massimo oltre il quale si chiude il tetto
 float TEMP_MAX; // valore di temperatura massima al di sotto del quale si può chiudere il tetto
 float TEMP_MAX2; // valore di temperatura massima al di sotto del quale si può aprire il tetto
 float TEMP_MIN; // valore di temperatura minima al di sopra del quale si può chiudere il tetto
 float TEMP_MIN2; // valore di temperatura massima al di sopra del quale si può aprire il tetto
};
	
#endif
