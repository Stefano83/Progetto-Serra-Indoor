#ifndef Input_h

#define Input_h

#include <WProgram.h>

	
class Input
	
{
	
 public:
	
     Input(int pinUT, int pinTA);
	
     void letturaUT(int &);
	 
	 void letturaTA(float &);
	 
	 void letturaGPS (char *, char *, char *);
	 
	 void letturaSMS(int &, char *, char*, int);
	
    
	
 private:
	
     int _pinUT;
	 int _pinTA;
	
};
	
#endif