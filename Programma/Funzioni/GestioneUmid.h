#ifndef GestioneUmid_h
#define GestioneUmid_h
#include <WProgram.h>


// Libreria per la gestione del valore di umidità del terreno
// Inpunt: non dovrebbe essere necessario alcun pin specifico
// Output: 
// chiude il tetto per deteminati valori di umidità del terreno
// invia un messaggio di approvazione di irrigazione per certi valori di umidità del terreno


class GestioneUmid
	
{
	
 public:
	 // Costruttore: non prende niente in input mentre come output stabilisce i valori da confrontare con il valore letto dal sensore
         GestioneUmid();
	 // Legge e controlla il valore di umidità del sensore e in base al valore letto può:
	 // chiudere il tetto o inviare messaggio di approvazione o non fa niente
	 void ControlloUmid(int , int , int , int ,int &, char *, char *, bool &, bool &, bool &, bool &);
	 
	
    
	
 private:
 
 int UMIDTERR_MAX; // valore di umidità massimo oltre il quale si chiude il tetto
 int UMIDTERR_MIN; // valore di umidità minimo al di sotto del quale si invia una richiesta di approvazione di irrigazione
	
	
};
	
#endif
