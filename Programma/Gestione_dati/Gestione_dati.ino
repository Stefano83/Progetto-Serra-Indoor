#include <Input.h>
#include <Output.h>
#include <DHT11.h>
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "gps.h "


Input input(A0, 6);
Output output(7,8,1);

#define LENGHT_MESS 180
#define LENGHT_NUM 12
#define TEMP_MAX 33.0  // valore massimo di temperatura
#define TEMP_MIN 5.0  // valore minomo di temperatura
#define TEMP_MAX2 25.0  // valore massimo di temperatura per riaprire il tetto
#define TEMP_MIN2 15.0  // valore minomo di temperatura per riaprire il tetto
#define UMIDTERR_MAX 800  // valore massimo di umidità del terreno
#define UMIDTERR_MIN 200  // valore minimo di umidità del terreno
#define UMIDTERR_MAX2 500  // valore massimo di umidità del terreno per riaprire il tetto
#define ORARIO1 18.30  // primo valore dell'intervallo dell'orario di irrigazione 
#define ORARIO2 19.00 // primo valore dell'intervallo dell'orario di irrigazione




float temp; // temperatura dell'aria
int umid;  // umidità del terreno
int pos; // posizione del messaggio
char lon[10];   // longitudine
char lat[10];   // latitudine
char time[15];  // tempo
char messaggio[LENGHT_MESS];  // Contenuto del messaggio da inviare
char numero[LENGHT_NUM]= "3333333333"; // Numero al quale inviare un messaggio
char number[LENGHT_NUM]; // Numero di chi ha inviato il messaggio
char message[LENGHT_MESS];


boolean irrig=false; // irrigatore da non avviare
boolean irriv_av=false;  // irrigazione in corso
boolean tetto=false;  // tetto aperto
boolean inviato=false; // nessun messaggio è stato inviato senza risposta
boolean dir=true; // direzione di rotazione oraria del motore cioè nella direzione che serve a chiudere il tetto
int passi=10000;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  controlloUT();
  controlloTA();
  controlloSMS();
  controlloIrrig();
  delay(600000);
  delay(1000);
}




void controlloUT()
{
  input.letturaUT(umid);
  Serial.print("Umidita Terreno: ");
  Serial.println(umid);
  delay(1000);
  if(umid > UMIDTERR_MAX && !tetto)  // controllo se l'umidità rilevata è dentro un certo range altrimenti passo il comando alla funzione di chiusura del tetto
  {
     output.Tetto(dir, passi);
     Serial.println("TETTO IN CHIUSURA");
     dir=false;
     tetto=true;
  }
  
  else if(umid < UMIDTERR_MIN && !inviato)
  {
      inviato = output.invioSMS(numero, messaggio);
      Serial.println((String) numero);
      Serial.println((String) messaggio);
      Serial.println("SMS INVIATO");
      inviato=true;
  }
}

void controlloTA()
{
  input.letturaTA(temp);
  Serial.print("Temperatura Aria: ");
  Serial.println(temp);
  delay(1000);
  if(temp > TEMP_MAX || temp < TEMP_MIN && !tetto)  // controllo se la temperatura rilevata è dentro un certo range altrimenti passo il comando alla funzione di chiusura del tetto
  {
    Serial.println("TETTO IN CHIUSURA");
     output.Tetto(dir, passi);
     dir=false;
     tetto=true;
  }
  else if (temp < TEMP_MAX2  && temp > TEMP_MIN2 && umid < UMIDTERR_MAX2 && tetto) // se il tetto è chiuso e la temperatura è compresa tra 10 e 30 gradi e l'umidità del terreno è minore di 700 allora il tetto è riaperto
  {
    Serial.println("TETTO IN APERTURA");
    output.Tetto(dir, passi);  
    dir=true;
    tetto=false;
  }
}


void controlloSMS()
{
  input.letturaSMS(pos, number, message, LENGHT_MESS);
  Serial.println(pos);
  Serial.println((String) number);
  Serial.println((String) message);
  if(controlloPassword())
   {
     controlloContenuto();
     inviato=false;
   }
}


void controlloIrrig()
{
  if (irrig)
  {
    float tempo = trasformazioneTempo(); // trasformo alcuni pezzi(quelli che equivalgono a ore e minuti) dell'array di caratteri in float
    if (tempo >= ORARIO1 && tempo <= ORARIO2)
      {
        Serial.println("IRRIGAZIONE INIZIATA");
        output.avvioIrrigatore();
        irriv_av=true;
      }
    else 
      {
        Serial.println("FASCIA ORARIA NON RISPETTATA: IRRIGAZIONE NON INIZIATA");
      }
    }
    
    else if(irriv_av && umid > UMIDTERR_MAX)  // controllo se l'umidità rilevata è maggiore di un certo valore altrimenti spengo l'irrigatore
  {
    output.spegniIrrigatore();
    irriv_av=false;
    irrig=false;
  }
}



boolean controlloPassword()
{
  char *p; // puntatore che utilizzo per verificare Password
  
  p=strstr(message,"SERRA");
  if(p)
  {
    Serial.println("PASSWORD OK");
    return true;
  }
  else
  {
    output.cancellazioneSMS(pos); // Se nel messaggio la password è sbagliata allora il messaggio viene eliminato
    Serial.println(pos);  
    return false;
  }
}



void controlloContenuto()
{
  char *p; // puntatore che utilizzo per verificare il contenuto del messaggio
  p=strstr(message,"SI");
  if(p)
  {
    Serial.println("IRRIGATORE DA AVVIARE");
    irrig = true;
  }
  else
  {
    // Controlla se nel messaggio è contenuto NO e restituisce un puntatore alla prima occorrenza di NO in message, NULL se non lo trova
    p=strstr(message,"NO"); // se all'interno del messaggio c'è NO allora non si fa niente
    if(p)
    {
      Serial.println("IRRIGATORE DA NON AVVIARE");
    }
    else
    {
      output.cancellazioneSMS(pos); // Se nel messaggio non è contenuto nè SI nè NO allora il messaggio viene eliminato
      Serial.println(pos); 
    }   
  } 
}



float trasformazioneTempo()
{
  float t;
  t= ((float)(time[8] - '0')*10) + ((float)(time[9] - '0')) + ((float)(time[10] - '0')/10) + ((float)(time[11] - '0')/100);
  return t;
}
  
  
  
