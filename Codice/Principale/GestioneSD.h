		#ifndef GestioneSD_h

		#define GestioneSD_h

		#include <Arduino.h>


		// Libreria per la gestione della SD card
		// Inpunt: valori letti dai sensori
		// Output:
		// salvare i dati in un file sulla SD card attraverso il PIN collegato alla SD

		class GestioneSD

		{

		 public:
			// Costruttore
			 GestioneSD(int);
			// Metodo che prende in input il valore letto di temperatura con l'orario della rilevazione e li salva in un file sulla SD card
			 void tempSD(float &, char *);
			 // Metodo che prende in input il valoro letto di umidità del terreno con l'orario della rilevazione e li salva in un file sulla SD card
			 void umtSD(int &, char *);
			// Metodo che prende in input il messaggio di risposta e lo salva in un file
			 void msgSD(char *);

			 void leggiValori();

			 void leggiMessaggi();

			void azzeraDati();

			void azzeraMessaggi();
			
			void invioDati( char *);


		 private:

			 int _pinSD;
			 float ORARIO_IN; // Orario dopo il quale è possibile far partire l'invio dati al server
			 float ORARIO_FIN; // Orario entro il quale è possibile far partire l'invio dati al server
			 char dati[];
			 char messaggi[];

		};

		#endif
