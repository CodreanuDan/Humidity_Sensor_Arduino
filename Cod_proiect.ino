#include <dht.h>
#define dataPin 8
#define analogPin      A0          // analog pin for measuring capacitor voltage
#define chargePin      12         // pin to charge the capacitor - connected to one end of the charging resistor
#define dischargePin   11         // pin to discharge the capacitor
#define rezistorValue  1000000.0F   // change this to whatever rezistor value you are using

dht DHT;

unsigned long startTime;
//unsigned long stopTime;
unsigned long Tc;
float microFarads;                // floating point variable to preserve precision, make calculations
float nanoFarads;

void setup() {
  pinMode(chargePin, OUTPUT);     // chargePin iesire
  digitalWrite(chargePin, LOW);  // chargePin LOW= 0[V]
  Serial.begin(9600);             // initialize serial transmission for debugging
}

void loop() {
 
  int readData = DHT.read11(dataPin);
  // float temperatura = DHT.temperature;
  float umiditate = DHT.humidity;

  // Serial.print("Temperatura = ");
  // Serial.print(temperatura);
  // Serial.print(" *C ");
 
  Serial.print("  Umiditate = ");
  Serial.print(umiditate);
  Serial.println(" % ");

/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

  digitalWrite(chargePin, HIGH);  // set chargePin HIGH and capacitor charging
  startTime = millis();
  while(analogRead(analogPin) < 648){/*nu face nimic */}  // 647 is 63.2% of 1023, which corresponds to full-scale voltage 
  Tc= millis() - startTime; // Tc => Cx=Tc/R
  Serial.print("    Tc= ");
  Serial.print(Tc);  
  Serial.print("  [ms]    ");    
 
//calcul capacitate senzor si control afisare serial microF sau nF  
  microFarads = ((float)Tc) / rezistorValue*1000; // C=Tc/R de retinut conversia unitatilor de masura  
 if (microFarads > 1){
    Serial.print(microFarads);       // print the value to serial port
    Serial.println(" [uF]");     // print units and carriage return
 }

 else{
    // if value is smaller than one microFarad, convert to nanoFarads (10^-9 Farad). 
    // This is  a workaround because Serial.print will not print floats
   nanoFarads = microFarads * 1000.0;      // multiply by 1000 to convert to nanoFarads (10^-9 Farads)
   Serial.print(nanoFarads);         // print the value to serial port
   Serial.println(" [nF]   ");          // print units and carriage return
 }
  /* dicharge the capacitor  */
  digitalWrite(chargePin, LOW);             // chargePin LOW= 0[V]
  pinMode(dischargePin, OUTPUT);            // set discharge pin to output 
  digitalWrite(dischargePin, LOW);          // set discharge pin LOW 
  while(analogRead(analogPin) >0){  }        // wait until capacitor is completely discharged
  pinMode(dischargePin, INPUT);            // set discharge pin high impedance
 
  delay(2000);
}

/*  RCTiming_capacitance_meter
 *   Paul Badger 2008
 *   Paul Badger 2008
 *  Demonstrates use of RC time constants to measure the value of a capacitor 
 *
 * Theory   A capcitor will charge, through a resistor, in one time constant, defined as T seconds where
 *    TC = R * C
 * 
 *    TC = time constant period in seconds
 *    R = resistance in ohms
 *    C = capacitance in farads (1 microfarad (ufd) = .0000001 farad = 10^-6 farads ) 
 *
 * The capacitor's voltage at one time constant is defined as 63.2% of the charging voltage.
 *
 *  Hardware setup:
 *  Test Capacitor between common point and ground (positive side of an electrolytic capacitor  to common)
 *  Test Resistor between chargePin and common point
 *  220 ohm resistor between dischargePin and common point
 *  Wire between common point and analogPin (A/D input)
 */


