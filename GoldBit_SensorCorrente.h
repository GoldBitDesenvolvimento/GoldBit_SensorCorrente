#ifndef GoldBit_SensorCorrente_h
#define GoldBit_SensorCorrente_h
#include "Arduino.h"

#define ACS722 1
#define ACS711EX 2

class Sensor
{
public: 
  Sensor(int _ID, double _start, double _final, int _pin)
  {
    ID = _ID;
    start = _start;
    final = _final;
    pin =_pin;
  }
  boolean getState()
  {
    switch(ID){
    case ACS722:
      return leituraACS722();
      break;
      case ACS711EX:
      return leituraACS711EX();
      break;
    }
  }

  boolean leituraACS722(){
    /*const int sensorPin = A0;
    float sensorValue_aux = 0;
    float sensorValue = 0;
    float currentValue = 0;
    float voltsporUnidade = 0.0048828125;
    float currenteValue;
    for(int i=500; i>0; i--)
    {
      valorSensor_aux = (analogRead(A0) - 511); // Faz a leitura do sensor e subtrai 511 (511 = sem corrente no circuito = 0A)
      valorSensor += pow(valorSensor_aux,2);  // Soma os quadradosos das leituras no laço
    }
    valorSensor = (sqrt(valorSensor/ 500)) * voltsporUnidade; // Tira a raiz quadrada da média da somatória dos valores aferidos
    valorCorrente = (valorSensor/66)*1000; // Calcula a corrente considerando a sensibilida do sensor para 60mV/A
    if(valorCorrente < start) //Se a corrente lida for menor que 0.50
    {
      //Serial.println("Lampada Apagada"); //Imprime na serial "Lâmpada Apagada"
      return 0;
    }
    else
    {
      //Serial.println("Lampada Acesa"); //Senão, imprime na serial "Lâmpada Acesa"
      return 1;
    }*/
  }
boolean leituraACS711EX(){
	int    Sensitivity    = 66; // mV/A
	//long   InternalVcc    = readInternalVcc();
	long   InternalVcc;
	
	//double ZeroCurrentVcc = InternalVcc / 2;
	double ZeroCurrentVcc ;
	//double SensedVoltage  = (RawADC * InternalVcc) / 1024;
	double SensedVoltage ;
	//double Difference     = SensedVoltage - ZeroCurrentVcc;
	double Difference   ;
	//double SensedCurrent  = Difference / Sensitivity;
	double SensedCurrent ;
 double RawADC;
	int count =0;
	for(int i =0;i<500;i++){
		
		RawADC = analogRead(pin);
		InternalVcc    = readInternalVcc();
		ZeroCurrentVcc = InternalVcc / 2;
		SensedVoltage  = (RawADC * InternalVcc) / 1024;
		Difference     = SensedVoltage - ZeroCurrentVcc;
		SensedCurrent  = Difference / Sensitivity;
		if(SensedCurrent>start)  
			count++;
	}
	if(count>5)
		return true;
  return false;  
}
void printDouble(double val, byte precision) 
{
  Serial.print (int(val));
  if( precision > 0) 
  {    
    Serial.print(".");
    unsigned long frac, mult = 1;
    byte padding = precision -1;
    while(precision--) mult *=10;
    if(val >= 0) frac=(val-int(val))*mult;
     else frac=(int(val)-val)*mult;
    unsigned long frac1 = frac;
    while(frac1 /= 10) padding--;
    while(padding--) Serial.print("0");
    Serial.print(frac,DEC) ;
 
  }
}
long readInternalVcc() 
{
  long result;
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2);                          // Wait for Vref to settle
  ADCSRA |= _BV(ADSC);               // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result;       // Back-calculate AVcc in mV
  return result;
}
 
  private:
  
  public:
  int ID, pin;
  double start, final;
};
#endif


