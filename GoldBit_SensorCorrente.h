#ifndef GoldBit_SensorCorrente_h
#define GoldBit_SensorCorrente_h
#include "Arduino.h"

#define ACS722 1

class Sensor
{
	public: 
	  Sensor(int _ID, double _start = 100, double _end = 500)
	  {
	  	ID = _ID;
	  	start = _start;
		end = _end;
	  }
	  bool getState()
	  {
	  	return 1;
	  }
	private:
		int ID;
		double start, end;
};
#endif



