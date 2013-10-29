#ifndef GestioneIrrig_h
#define GestioneIrrig_h
#include <WProgram.h>


// Libreria per la gestione dell'irrigatore
// Inpunt: non dovrebbe essere necessario alcun pin specifico
// Output: 
// avvia l'irrigatore se è nella fascia oraria prestbilita ed è stata data l'approvazione all'irrigazione
// spegne l'irrigatore  per deteminati valori di umidità del terreno


class GestioneIrrig
	
{
	
 public:
	 // Costruttore: non prende niente in input mentre come output stabilisce i valori di umidità del terreno da confrontare per spegnere l'irrigatore
         GestioneIrrig();
	 // Legge e controlla il valore di umidità dal sensore e in base al valore letto può:
	 // spegnere l'irrigazione
	 void controlloIrrig(int, int, int &, bool &, char *);
	 
	
    
	
 private:
 
 bool irrig_av; // variabile di stato che indica se l'irrigazione è in corso
 int UMIDTERR_MAX3; // valore di umidità massimo oltre il quale si chiude il tetto
 float ORARIO_IN; // Orario dopo il quale è possibile far partire l'irrigazione
 float ORARIO_FIN; // Orario entro il quale è possibile far partire l'irrigazione

};
	
#endif
