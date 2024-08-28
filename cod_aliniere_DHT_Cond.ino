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
#include <dht.h>
#include <avr/wdt.h>
dht DHT;
#define dataPin 8
#define analogPin      A0         // analog pin for measuring capacitor voltage
#define chargePin      12         // pin to charge the capacitor - connected to one end of the charging resistor
#define dischargePin   11         // pin to discharge the capacitor
#define rezistorValue  1000000.0F // change this to whatever rezistor value you are using
// #define ledPin 13  //  the pin where the LED is connected
                                  // F formatter tells compliler it's a floating point value
unsigned long startTime;
//unsigned long stopTime;
unsigned long Tc;
float microFarads;                // floating point variable to preserve precision, make calculations
float nanoFarads;

unsigned long previousDHTMillis = 0;
unsigned long previousCapacitorMillis = 0;
unsigned long lastResetMillis = 0;
const int dhtInterval = 2000;  // Interval pentru DHT11 (2 secunde)

//////////////////////////////////////////////> SETUP <///////////////////////////////////////////////
void setup(){
  pinMode(chargePin, OUTPUT);     // chargePin iesire
  digitalWrite(chargePin, LOW);  // chargePin LOW= 0[V]
  // pinMode(ledPin, OUTPUT);  // LED pin as an output
  Serial.begin(9600);             // initialize serial transmission for debugging
}

// DHT 11 Measurement function:
void dht_11_measurement(){
    //  digitalWrite(ledPin, HIGH);  // Turn on the LED
     unsigned long dht11_currentMillis = millis();
     if (dht11_currentMillis - previousDHTMillis >= dhtInterval) {
       int readData = DHT.read11(dataPin);
       float umiditate = DHT.humidity;
       Serial.print(" ");
       Serial.print(int(umiditate));
       Serial.print(" ");
       previousDHTMillis = dht11_currentMillis;
      //  digitalWrite(ledPin, LOW);   // Turn off the LED
       wdt_enable(WDTO_2S);
     }
}
////////////////////////////////////////////> LOOP <////////////////////////////////////////////////
void loop(){

  //Analog Sensor
  digitalWrite(chargePin, HIGH);  // set chargePin HIGH and capacitor charging
  startTime = millis();
  while(analogRead(analogPin) < 648){/*nu face nimic */}  // 647 is 63.2% of 1023, which corresponds to full-scale voltage 
  Tc= millis() - startTime; // Tc => Cx=Tc/R
  //calcul capacitate senzor si control afisare serial microF sau nF  
  microFarads = (int((float)Tc)) / rezistorValue*1000; // C=Tc/R de retinut conversia unitatilor de masura  
  if (microFarads > 1){}
  else{
    // if value is smaller than one microFarad, convert to nanoFarads (10^-9 Farad). 
    // This is  a workaround because Serial.print will not print floats
    nanoFarads = microFarads * 1000.0;      // multiply by 1000 to convert to nanoFarads (10^-9 Farads)
    // Analog sensor write:
    Serial.println(int(nanoFarads));         // print the value to serial port <!!!>
 }
  /* dicharge the capacitor  */
  digitalWrite(chargePin, LOW);             // chargePin LOW= 0[V]
  pinMode(dischargePin, OUTPUT);            // set discharge pin to output 
  digitalWrite(dischargePin, LOW);          // set discharge pin LOW 
  while(digitalRead(dischargePin) == HIGH){} // wait until capacitor is completely discharged
  pinMode(dischargePin, INPUT);            // set discharge pin high impedance
  // DHT 11
  dht_11_measurement();
//////////////////////////////////////- TIME DELAY -////////////////////////////////////////
  delay(50); // Delay for sample rate
  wdt_reset();
}







