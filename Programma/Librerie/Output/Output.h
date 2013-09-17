#ifndef Output_h

#define Output_h

#include <WProgram.h>

	
class Output
	
{
	
 public:
	
     Output(int pinDir, int stepperPin, int pinIrrig);
	
     void avvioMotore(bool, int);
	 
	 void avvioIrrigatore();
	 
	 void spegniIrrigatore();
	 
	 bool invioSMS(char *, char *);
	 
	 void cancellazioneSMS(int);
	 
	
    
	
 private:
	
     int _pinDir;
	 int _stepperPin;
	 int _pinIrrig;
	
};
	
#endif