/*  
 *  RCTiming_capacitance_meter
 *  Demonstrates the use of RC time constants to measure the value of a capacitor.
 *
 *  Theory: 
 *    A capacitor will charge through a resistor in one time constant, defined as T seconds where
 *    TC = R * C
 *    TC = time constant period in seconds
 *    R = resistance in ohms
 *    C = capacitance in farads (1 microfarad (µF) = 1e-6 farads) 
 *
 *    The capacitor's voltage at one time constant is defined as 63.2% of the charging voltage.
 *
 *  Hardware setup:
 *    - Test Capacitor between common point and ground (positive side of an electrolytic capacitor to common)
 *    - Test Resistor between chargePin and common point
 *    - 220 ohm resistor between dischargePin and common point
 *    - Wire between common point and analogPin (A/D input)
 */

#include <dht.h>
#include <avr/wdt.h>

#define dataPin 8             // Pin connected to the DHT11 sensor
#define analogPin A0          // Analog pin for measuring capacitor voltage
#define chargePin 12          // Pin to charge the capacitor - connected to one end of the charging resistor
#define dischargePin 11       // Pin to discharge the capacitor
#define resistorValue 1000000.0F // Resistor value used in ohms

dht DHT;
unsigned long startTime;
unsigned long Tc;
float microFarads;
float nanoFarads;

unsigned long previousDHTMillis = 0;
unsigned long previousCapacitorMillis = 0;
const int dhtInterval = 2000;  // Interval for DHT11 measurements (2 seconds)

//////////////////////////////////////////////> SETUP <///////////////////////////////////////////////
void setup() 
{
  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, LOW);   // Ensure the charge pin is LOW initially
  Serial.begin(9600);             // Initialize serial communication for debugging
}

////////////////////////////////////////////> DHT11 Measurement </////////////////////////////////////
void dht_11_measurement() 
{
  unsigned long dht11_currentMillis = millis();
  if (dht11_currentMillis - previousDHTMillis >= dhtInterval) 
  {
    int readData = DHT.read11(dataPin);
    float humidity = DHT.humidity;
    Serial.print("Humidity: ");
    Serial.print(int(humidity));
    Serial.println(" %");
    previousDHTMillis = dht11_currentMillis;
    wdt_enable(WDTO_2S);  // Watchdog timer to reset the system if it hangs
  }
}

////////////////////////////////////////////> LOOP <////////////////////////////////////////////////
void loop() 
{
  // Charge the capacitor
  digitalWrite(chargePin, HIGH);
  startTime = millis();

  // Wait until the capacitor's voltage reaches 63.2% of the charging voltage (approximately 648 out of 1023)
  while (analogRead(analogPin) < 648) { /* Wait */ }

  Tc = millis() - startTime; // Calculate the time constant (Tc)
  
  // Calculate capacitance in microfarads
  microFarads = (float)Tc / resistorValue * 1000;  // Convert to µF
  
  if (microFarads > 1) 
  {
    Serial.print("Capacitance: ");
    Serial.print(microFarads);
    Serial.println(" µF");
  } 
  else 
  {
    // If the value is less than 1 µF, convert to nanoFarads
    nanoFarads = microFarads * 1000.0;
    Serial.print("Capacitance: ");
    Serial.print(int(nanoFarads));
    Serial.println(" nF");
  }

  // Discharge the capacitor
  digitalWrite(chargePin, LOW);
  pinMode(dischargePin, OUTPUT);
  digitalWrite(dischargePin, LOW);

  // Wait until the capacitor is completely discharged
  while (digitalRead(dischargePin) == HIGH) { /* Wait */ }

  // Set discharge pin to high impedance state
  pinMode(dischargePin, INPUT);

  // Perform DHT11 measurement
  dht_11_measurement();

  // Reset the watchdog timer
  wdt_reset();

  // Delay for sample rate
  delay(50);
}
