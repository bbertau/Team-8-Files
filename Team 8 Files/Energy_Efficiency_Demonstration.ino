// The purpose of this program is to calculate the energy efficiencty of a circuit 
// by reading the true power output of the connected circuit, and divide it by the
// theoretical power of the circuit. LEDs will illuminate, with more brightness
// as the degree of efficiency increases.
// Author: Brent Bertaux, Team 8


const int voltagePin = A0;    // Analog pin for voltage measurement
const int currentPin = A1;    // Analog pin for current measurement
const int ledPins[] = {2, 3, 4, 5, 6};  // Pins connected to LEDs

void setup() {
  Serial.begin(9600);  

  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  int rawVoltage = analogRead(voltagePin);
  
  float voltage = (float)rawVoltage * (9.0 / 1023.0);  // 9V Power Supply

  int rawCurrent = analogRead(currentPin);

  float current = map(rawCurrent, 0, 1023, 0, 10);  // Current Calculation

  float inputPower = rawVoltage * rawCurrent;
  float outputPower = voltage * current;
  
  // Calculate efficiency as a percentage
  float efficiency = (output / inputPower) * 100;

  int numLedsToLight = 0;

  if (efficiency >= 0 && efficiency < 20) {
    numLedsToLight = 1;
  } else if (efficiency >= 20 && efficiency < 40) {
    numLedsToLight = 2;
  } else if (efficiency >= 40 && efficiency < 60) {
    numLedsToLight = 3;
  } else if (efficiency >= 60 && efficiency < 80) {
    numLedsToLight = 4;
  } else if (efficiency >= 80 && efficiency <= 100) {
    numLedsToLight = 5;
  }

// Display LEDs
  for (int i = 0; i < 5; i++) {
    if (i < numLedsToLight) {
      digitalWrite(ledPins[i], HIGH); // Turn on the LED
    } else {
      digitalWrite(ledPins[i], LOW); // Turn off the LED
    }
  }

  Serial.print("Efficiency (%): ");
  Serial.println(efficiency, 2); 
  
  delay(15000); // Check readings on 15 second intervals

}
