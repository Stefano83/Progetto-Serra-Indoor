/*
Creazione web server tramite Ethernet Shield.
Saranno visualizzati i dati ed i messaggi scritti sulla SD card dal programma principale.
*/

// Includo le librerie per la gestione della rete e della scheda SD

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

// Creo un oggetto file che rappresenta il contenento del file html della SD card 

File DatiSD;

// Dichiaro l'indirizzo MAC del nostro Arduino con valori di esempio che andranno modificati

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Inizializzo la libreria Ethernet con l'indirizzo IP e la porta predefinita per l'HTTP

EthernetServer server(80);

void setup() {
  
  // Apro la comunicazione seriale e attendo la sua connessione
 
  Serial.begin(9600);
    while (!Serial) {
      ; 
    }

  // Avvio la connessione Ethernet al server 
 
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Impossibile configurare Ethernet tramite DHCP");
    for (;;)
      ;
  }    
    
  // Controllo che la scheda SD sia attiva
  
    if (!SD.begin(4)) { 
      return; 
    }
  
  // Visualizzazione indirizzo IP locale
  
  Serial.print("Il mio indirizzo IP è: ");
  
  // Stampo il valore di ciascun byte dell'indirizzo IP  
  
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  
  Serial.println();

  Ethernet.begin(mac);
  server.begin();
  Serial.print("L'indirizzo IP del server è: ");
  Serial.println(Ethernet.localIP());
  
}

void loop() {
  
  // Per proseguire attendo una connessione da parte di un client 
  
  EthernetClient client = server.available();

  if (client) {
    
    Serial.println("Nuovo client");
      
    // Una richiesta HTTP termina con una riga nuova. Dichiaro una variabile booleana che mi servirà in seguito.
    
    boolean currentLineIsBlank = true;
  
    // Inizio un ciclo while in cui eseguo operazioni fin quando la connessione è attiva, verificando che comunichi con il mio server. 
   
    while (client.connected()) {
      
      if (client.available()) {
        
        /* Leggo dal client la richiesta della pagina. Se è richiesto un carattere di linea nuova e la variabile currentLineIsBlank 
        è vera inizio la comunicazione con il client. */
        
        char c = client.read();
        Serial.write(c);
       
        if (c == '\n' && currentLineIsBlank) {
          
          // Invio al client gli header della mia pagina html
          
          client.println ("HTTP/1.1 200 OK");
          client.println ("Content-Type: text/html");
          client.println ();
          
          // Leggo il file html dalla SD card assegnandolo all'oggetto file creato in precedenza
          
          DatiSD = SD.open ("index.htm");
          
          /* Verifico che abbia letto correttamente il file; con il metodo print della classe client indico al browser il contenuto 
          di tutte le linee del file. */ 
                   
          if (DatiSD) {
           
            while (DatiSD.available()) {
                client.print (DatiSD.read());
            }
            
            // Chiusura file
            
            DatiSD.close();
       
          }
       
          break;
          
        }
      
        /* Verifica comunicazione con il client, ricevendo una linea vuota (\n) si reimposta la currentLineIsBlank a true. 
        In caso di ricezione di un return (\r) viene invece impostata a false in modo da impedire al ciclo successivo di reinviare 
        nuovamente gli header e il file già inviato. */
      
        if (c == '\n') {
          currentLineIsBlank = true;
        } 
      
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
    
      }
    
      // Per ogni ciclo di loop imposto un tempo di attesa di un millisecondo
    
      delay(1);
    
      // Chiudo la connessione con il client dopo aver completato l’invio di informazioni. Il server può rispondere alle richieste successive.

      client.stop();
      Serial.println("Client disconnesso");
      
    }
    
  }
  
}
