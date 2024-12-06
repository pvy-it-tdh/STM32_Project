#include <Arduino.h>
#include <HardwareTimer.h>

#define LM35_PIN PA0
#define LED PC13
#define INTERVAL 1000000  // 1 second
#define INTERVAL2 500000  // 0.5 second

HardwareTimer Timer1(TIM1);
HardwareTimer Timer2(TIM2);

void adcRead() {
  int adcValue = analogRead(LM35_PIN);
  float voltage = adcValue * (3.3 / 4095.0); // Calculate voltage
  float temperature = voltage * 100.0;      // Convert to temperature
  Serial.println(temperature);              // Print temperature to Serial Monitor
}

void ngat() {
  static bool ledState = false;
  ledState = !ledState;  // Toggle LED state
  digitalWrite(LED, ledState ? HIGH : LOW);
}

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);  // Initialize Serial Monitor
  
  Timer1.pause();
  Timer1.setOverflow(INTERVAL, MICROSEC_FORMAT);
  Timer1.attachInterrupt(ngat);
  Timer1.resume();

  Timer2.pause();
  Timer2.setOverflow(INTERVAL2, MICROSEC_FORMAT);
  Timer2.attachInterrupt(adcRead);
  Timer2.resume();
}

void loop() {
  // Main loop remains empty
}
