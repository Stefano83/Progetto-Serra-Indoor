#ifndef GestioneSMS_h
#define GestioneSMS_h

#include <WProgram.h>

// Libreria per la gestione degli SMS
// Inpunt: non dovrebbe essere necessario alcun pin specifico
// Output: 
// invia messaggi a un numero predefinito
// controlla contenuto dei messaggi ricevuti e in caso di esito positivo abilita l'irrigazione


	
class GestioneSMS
	
{
	
 public:
	// Costruttore
         GestioneSMS(); 
	// Metodo per l'invio di SMS
	 bool invioSMS(bool &, bool &, char *, char *);
	 // Metodo per la lettura di SMS
	 bool letturaSMS(bool &, bool &);
	 // Metodo per la cancellazione di SMS
	 void cancellazioneSMS();
	 // Metodo che costruisce il messaggio da inviare
	 void costruzioneMessaggio(char *, char *);
	 // Metodo che controlla il contenuto dei messaggi ricevuti
	 void controlloSMS(bool &, bool &, bool &);
	 // Metodo che controlla l'esistenza della password all'interno del messaggio
	 bool controlloPassword();
	 // Metodo che controlla la decisione (SI o NO) all'interno del messaggio
	 void controlloContenuto(bool &);
    
	
 private:
	
         static const int LENGHT_MESS = 180; // lunghezza massima del messaggio
	 static const int LENGHT_NUM = 12; // lunghezza massima del numero
	 int pos; // posizione del messaggio
	 char messaggio[];  // Contenuto del messaggio da inviare
         char numero[]; // Numero al quale inviare un messaggio
	 char number[]; // Numero di chi ha inviato il messaggio
	 char message[]; // Contenuto del messaggio ricevuto
	 
	
};
	
#endif
