/*
Creazione web server tramite Ethernet Shield.
Saranno visualizzati i dati forniti dai sensori e l'eventuale azionamento dell'irrigatore.        
*/

// Includo le librerie per la gestione della rete

#include <SPI.h>
#include <Ethernet.h>

/* 
Dichiaro l'indirizzo MAC del nostro Arduino con valori di esempio che andranno modificati in seguito. 
*/

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Inizializzo la libreria Ethernet con l'indirizzo IP e la porta predefinita per l'HTTP

EthernetServer server(80);

/* Dichiaro le variabili.
Nel primo blocco definisco i Pin di Input di Arduino che riceveranno i dati, con valori di esempio e che andranno modificati.
Nel secondo blocco dichiaro le variabili di lettura dati derivanti dai valori restituiti dai Pin.
Infine dichiaro la variabile booleana avvioIrrigatore che dipende dal programma di elaborazione dati.
*/

int analogTA = 0;
int analogUT = 1;
int digitalGPS = 2; 

float letturaTA = analogRead (analogTA); 
int letturaUT = analogRead (analogUT);
char letturaGPS = digitalRead (digitalGPS);

boolean avvioIrrigatore = false;

// Inizio blocco setup

void setup() {
  
  // Apro la comunicazione seriale e attendo la sua connessione
 
  Serial.begin(9600);
  while (!Serial) {
  ; 
  }

  // Avvio la connessione Ethernet al server 
 
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Impossibile configurare Ethernet tramite DHCP");
    for(;;)
      ;
  }
  
  // Visualizza indirizzo IP locale
  Serial.print("Il mio indirizzo IP è: ");
  
  // Stampo il valore di ciascun byte dell'indirizzo IP  
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();
}
 
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("L'indirizzo IP del server è: ");
  Serial.println(Ethernet.localIP());
}

// Fine blocco setup

// Inizio blocco loop

void loop() {
  
  // Per proseguire attendo una connessione da parte di un client. 
  
  EthernetClient client = server.available();

  if (client) {
    Serial.println("Nuovo client");
      
  // Una richiesta HTTP termina con una riga nuova. Dichiaro una variabile booleana che mi servirà in seguito.
  boolean currentLineIsBlank = true;
  
  // Inizio un ciclo while in cui eseguo operazioni fin quando la connessione è attiva, verificando che comunichi con il mio server. 
    while (client.connected()) {
      
      if (client.available()) {
        
        /* Leggo dal client la richiesta della pagina. Se è richiesto un carattere di linea nuova e la variabile currentLineIsBlank è 
        vera inizio la comunicazione con il client. */
        char c = client.read();
        Serial.write(c);
       
        if (c == '\n' && currentLineIsBlank) {
          
          // Invio al client gli header della mia pagina html
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          
          // Inizio pagina html
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
      
          // Visualizzo i parametri misurati dai rispettivi sensori, leggendoli dai Pin di Input di Arduino       
      
          client.print("La temperatura dell'aria è: ");
          client.println("<b>");
          client.print(letturaTA);
          client.print(" °C");
          client.println("</b>");
          client.println("<br />"); 
          
          client.print("L'umidità del terreno è: ");
          client.println("<b>");
          client.print(letturaUT);
          client.println("</b>");
          client.println("<br />");    
          
          client.print("Le coordinate geografiche e l'ora di misurazione sono:  ");
          client.println("<b>");
          client.print(letturaGPS);
          client.println("</b>");
          client.println("<br />");
      
          /* In base alle misurazioni dei sensori di temperatura aria e umidità del terreno posso avviare o meno l'irrigatore 
          se i valori superano certi limiti stabiliti all'interno del programma di elaborazione dati */ 
      
          if (avvioIrrigatore = true) {
               client.println ("Ho avviato l'irrigatore ");         
          } 
          
          else {
               client.println ("Non abbiamo bisogno di avviare l'irrigatore "); 
          }
          
          client.println ("</br>");
          client.println ("</html>");
          break;
        }
        
        /* Per ogni ciclo di while verifico la comunicazione con il client, se ricevo una linea vuota continuo la comunicazione e imposto
        la variabile currentLineIsBlank a "vero", altrimenti se ricevo un carriege return (\r) la imposto a "falsa". */
        
        if (c == '\n') {
          currentLineIsBlank = true;
        } 
        
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    
    // Per ogni ciclo di loop imposto un tempo di attesa di un millisecondo
    
    delay(1);
    
    // Chiudo la connessione con il client dopo aver completato l’invio di informazioni. Il server può rispondere alle richieste successive.

    client.stop();
    Serial.println("Client disconnesso");
  }
}
