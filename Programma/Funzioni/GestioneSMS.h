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
	 boolean invioSMS(boolean &, boolean &, char *, char *);
	 // Metodo per la lettura di SMS
	 void letturaSMS(boolean &, boolean &);
	 // Metodo per la cancellazione di SMS
	 void cancellazioneSMS();
	 // Metodo che costruisce il messaggio da inviare
	 void costruzioneMessaggio(char *, char *);
	 // Metodo che controlla il contenuto dei messaggi ricevuti
	 void controlloSMS(boolean &);
	 // Metodo che controlla l'esistenza della password all'interno del messaggio
	 boolean controlloPassword();
	 // Metodo che controlla la decisione (SI o NO) all'interno del messaggio
	 void controlloContenuto(boolean &);
    
	
 private:
	
     const int LENGHT_MESS // lunghezza massima del messaggio
	 const int LENGHT_NUM // lunghezza massima del numero
	 int pos; // posizione del messaggio
	 char messaggio[LENGHT_MESS];  // Contenuto del messaggio da inviare
	 char numero[LENGHT_NUM]= "3333333333"; // Numero al quale inviare un messaggio
	 char number[LENGHT_NUM]; // Numero di chi ha inviato il messaggio
	 char message[LENGHT_MESS]; // Contenuto del messaggio ricevuto
	 
	
};
	
#endif