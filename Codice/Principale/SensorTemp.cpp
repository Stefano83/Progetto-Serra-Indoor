#include <DHT11.h>


#include "SensorTemp.h"
#include <Arduino.h>
#include <SoftwareSerial.h>
	
	
SensorTemp::SensorTemp(int pinTA)
	
{
//Serial.begin(9600); // configuro la seriale
pinMode(pinTA,INPUT);
_pinTA=pinTA; 
}	

	
void SensorTemp::letturaTA(float & temp)
	
{	
	DHT11 dht11(_pinTA); // istanzio l'oggetto dht11 della classe DHT11 all'interno del metodo

 // Serial.begin(9600);
  //while (!Serial) {}
  //    ;
	//in modo che abbia visibilità solo all'interno del metodo e una volta concluso venga distrutto
	float um; // variabile usata in maniera fittizia per la lettura congiunta di temperatura e umidità dell'aria
	int err; // variabile che indica il tipo di errore che eventualmente si riscontra; il valore è 0 se non ci sono errori
	
  if((err=dht11.read(temp, um))==0)  // istruzione di lettura dei valori e assegnazione alle variabili dedicate
  {
    Serial.print("Temperatura: "); // stampo sulla seriale valore di temperatura dell'aria appena letto
    Serial.println(temp);
    Serial.print("Umidità: "); // stampo sulla seriale valore umidità dell'aria appena letto
    Serial.println(um);
  }
  else
  {
    Serial.print("Errore");
    Serial.println(err);  
  }
  delay(100);
}
