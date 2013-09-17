#include <DHT11.h>	
#include <wprogram.h>
#include "Input.h"
#include <Arduino.h>
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "gps.h "
#include "sms.h"
	
	
Input::Input(int pinUT, int pinTA)
	
{
	
pinMode(pinUT,INPUT);
pinMode(pinTA,INPUT);
_pinUT=pinUT;
_pinTA=pinTA;
}	

void Input::letturaUT(int & umid)
	
{
	umid = analogRead(_pinUT);
}
	
void Input::letturaTA(float & temp)
	
{	
	DHT11 dht11(_pinTA); 
	float um;
	dht11.read(um, temp);
}


void Input::letturaGPS(char* lon, char* lat, char* time)

{
	GPSGSM gps;
	gps.attachGPS();
	
	char alt[10];
	char vel[10];
	gps.getPar(lon,lat,alt,time,vel);
}


void Input::letturaSMS(int & pos, char * number, char* message, int lenght)
{
	SMSGSM sms; // Creiamo un oggetto sms della classe SMSGSM
	pos=sms.IsSMSPresent(SMS_UNREAD);
 // Controllo se pos è diverso da 0 cioè controllo se ci sono nuovi messaggi
	if(pos != 0) 
	{
 // Legge il messaggio in posizione pos e posiziona il numero di chi lo ha inviato in number e il testo in message
		sms.GetSMS(pos,number,message, lenght);}
}