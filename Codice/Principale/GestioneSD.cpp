#include <call.h>
#include <gps.h>
#include <GSM.h>
#include <inetGSM.h>
#include <LOG.h>
#include <SIM900.h>
#include <sms.h>
#include <Streaming.h>
#include <WideTextFinder.h>

#include <ArduinoStream.h>
#include <bufstream.h>
#include <ios.h>
#include <iostream.h>
#include <istream.h>
#include <MinimumSerial.h>
#include <ostream.h>
#include <Sd2Card.h>
#include <SdBaseFile.h>
#include <SdFat.h>
#include <SdFatConfig.h>
#include <SdFatmainpage.h>
#include <SdFatStructs.h>
#include <SdFatUtil.h>
#include <SdFile.h>
#include <SdInfo.h>
#include <SdStream.h>
#include <SdVolume.h>


#include "GestioneSD.h"
#include "SensorGPS.h"
#include <Arduino.h>
#include <SoftwareSerial.h>
                


			
			
		GestioneSD::GestioneSD(int pinSD)	
		{
		pinMode(pinSD,OUTPUT); // imposta il pinSD come OUTPUT in particolare il pin digitale 10
		_pinSD=pinSD;
		ORARIO_IN=23.00;
		ORARIO_FIN=23.15;
		}	

		// Scrive valori di temperatura in un file di testo nella SD
		void GestioneSD::tempSD(float & temp, char * time)	
		{
			SdFat sd;
		//creo un oggetto dalla classe File
			SdFile FileSD;
		//inizializza la classe e specifica
		//il pin SD Card
			if (sd.begin(_pinSD) == true)
			//inizializzazione ok
		{
			
		//Apro un file di testo in modalità scrittura che nomino con (se il file non esiste lo creo, se il file esiste scrivo dopo l'ultima paroal che ho scritto)
			FileSD.open("Temp.txt", O_CREAT | O_APPEND | O_WRITE);
		//se non ci sono problemi nell'apertura dei file scrivo
		//al suo interno
				FileSD.println( (String)time + "\tTemp:" + (int)temp);
				Serial.println(temp);
		//chiudo il file
				FileSD.close();

			
			
		  }
		  else
		  //problemi nell'inizializzazione
			Serial.println("\n ERRORE INIZIALIZZAZIONE");
		}
		
		
		// Scrive valori di umidità del terreno in un file di testo nella SD
		void GestioneSD::umtSD(int & umt, char * time)	
		{
			SdFat sd;
		//creo un oggetto dalla classe File
			SdFile FileSD;
		//inizializza la classe e specifica
		//il pin SD Card
			if (sd.begin(_pinSD) == true)
			//inizializzazione ok
		{
			
		//Apro un file di testo in modalità scrittura che nomino con (se il file non esiste lo creo, se il file esiste scrivo dopo l'ultima paroal che ho scritto)
			FileSD.open("Umt.txt", O_CREAT | O_APPEND | O_WRITE);
		//se non ci sono problemi nell'apertura dei file scrivo
		//al suo interno
				FileSD.println((String)time + "\tUmid:" + umt);
				Serial.println(umt);
		//chiudo il file
				FileSD.close();

			
			
		  }
		  else
		  //problemi nell'inizializzazione
			Serial.println("\n ERRORE INIZIALIZZAZIONE");
		}


		// Salva messaggi di risposta in un file di testo nella SD
		void GestioneSD::msgSD(char* msg)
			
		{
			SdFat sd;
		//creo un oggetto dalla classe File
			SdFile FileSD;
		//inizializza la classe e specifica
		//il pin SD Card
			if (sd.begin(_pinSD) == true)
			//inizializzazione ok
		{
			
		//Apro un file di testo in modalità scrittura che nomino con 
			FileSD.open("Messaggi.txt", O_CREAT | O_APPEND | O_WRITE);
		//se non ci sono problemi nell'apertura dei file scrivo
		//al suo interno
			
				FileSD.println("Messaggio:" + (String)msg);
		//chiudo il file
				FileSD.close();
					
			
		  }
		  else
		  //problemi nell'inizializzazione
			Serial.println("\n ERRORE INIZIALIZZAZIONE");
		}


		void GestioneSD::leggiValori()
		{
			SdFat sd;
		//creo un oggetto dalla classe File
			SdFile FileSD;
		//inizializza la classe e specifica
		//il pin SD Card
			if (sd.begin(_pinSD) == true)
			//inizializzazione ok
			{
				FileSD.open("Temp.txt", O_READ);
					// leggi dal file sino alla fine
					while (FileSD.available()) {

					  char data = FileSD.read();
					  Serial.write(data);  
					  //chiudo il file
					  FileSD.close();}
					  
					  FileSD.open("Umt.txt", O_READ);
					// leggi dal file sino alla fine
					while (FileSD.available()) {

					  char data = FileSD.read();
					  Serial.write(data);  
					  //chiudo il file
					  FileSD.close();}
			}
			else
		  //problemi nell'inizializzazione
			Serial.println("\n ERRORE INIZIALIZZAZIONE");

		}


		void GestioneSD::leggiMessaggi()
		{
			SdFat sd;
		//creo un oggetto dalla classe File
			SdFile FileSD;
		//inizializza la classe e specifica
		//il pin SD Card
			if (sd.begin(_pinSD) == true)
			//inizializzazione ok
			{
				FileSD.open("Messaggi.txt", O_READ);
				
					// leggi dal file sino alla fine
					while (FileSD.available()) {

					  char messaggi = FileSD.read();
					  Serial.write(messaggi);  
					  //chiudo il file
					FileSD.close();

					}
			}
			else
		  //problemi nell'inizializzazione
			Serial.println("\n ERRORE INIZIALIZZAZIONE");

		}


		void GestioneSD::azzeraDati()
		{
		SdFat sd;
		//creo un oggetto dalla classe File
			SdFile FileSD;
		//inizializza la classe e specifica
		//il pin SD Card
			if (sd.begin(_pinSD) == true)
			//inizializzazione ok
			{
				FileSD.open("Temp.txt", O_TRUNC);
				FileSD.close();
				FileSD.open("Umt.txt", O_TRUNC);
				FileSD.close();
				}
			else
		  //problemi nell'inizializzazione
			Serial.println("\n ERRORE INIZIALIZZAZIONE");}


			
			
		void GestioneSD::azzeraMessaggi()
		{
		SdFat sd;
		//creo un oggetto dalla classe File
			SdFile FileSD;
		//inizializza la classe e specifica
		//il pin SD Card
			if (sd.begin(_pinSD) == true)
			//inizializzazione ok
			{
				FileSD.open("Messaggi.txt", O_TRUNC);
				FileSD.close();
				}
					
			else
		  //problemi nell'inizializzazione
			Serial.println("\n ERRORE INIZIALIZZAZIONE");}
			
			
		
		void GestioneSD::invioDati( char * time)
		{
			SdFat sd;
		//creo un oggetto dalla classe File
			SdFile FileSD;
		//inizializza la classe e specifica
		//il pin SD Card
			if (sd.begin(_pinSD) == true)
			//inizializzazione ok
			{
				SensorGPS sensorGPS;
				sensorGPS.letturaTempo(time);  // lettura del valore di tempo
				float t = sensorGPS.trasformazioneTempo(time); // trasformo alcuni pezzi(quelli che equivalgono a ore e minuti) dell'array di caratteri in float
				// Controllo se sono nella fascia orario prestabilita per l'irrigazione e se l'irrigazione non sia stata già avviata
				if (t >= ORARIO_IN && t <= ORARIO_FIN)
				leggiValori();
				Serial.println(dati);
				// funzione che invia i dati al server}
				azzeraDati();
				
				
				leggiMessaggi();
				Serial.println(messaggi);
				// funzione che invia i dati al server}
				azzeraMessaggi();
					}
			else
		  //problemi nell'inizializzazione
			Serial.println("\n ERRORE INIZIALIZZAZIONE");
		}
		
