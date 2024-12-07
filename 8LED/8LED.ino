#include <Arduino.h>
#include <HardwareTimer.h>
#include<SimpleKalmanFilter.h>
#include<Wire.h>
#include <LiquidCrystal_I2C.h>
#define LM35_PIN PB0
#define LED_RUN PC13
#define INTERVAL 1000000  // 1 second
#define INTERVAL2 500000  // 0.5 second
#define LED1_PIN  PA0  
#define LED2_PIN  PA1  
#define LED3_PIN  PA2  
#define LED4_PIN  PA3  
#define LED5_PIN  PA4  
#define LED6_PIN  PA5  
#define LED7_PIN  PA6  
#define LED8_PIN  PA7
LiquidCrystal_I2C lcd(0x27, 16, 2);  
HardwareTimer Timer1(TIM1);
HardwareTimer Timer2(TIM2);
SimpleKalmanFilter kalman(2.0,2.0,0.01);

void adcRead() {
  int adcValue = analogRead(LM35_PIN);
  float voltage = adcValue * (3.3 / 4095.0); 
  float temperature = voltage * 100.0; 
  if(temperature>=70)
  {
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("High Temperature");
  }
  float smoothedTemp = kalman.updateEstimate(temperature);
  Serial.println(smoothedTemp);
}

void ngat() {
  static bool ledState = false;
  ledState = !ledState;  
  digitalWrite(LED_RUN, ledState ? HIGH : LOW);
}


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0); 
  lcd.print("D22CQDK01-N");
  lcd.setCursor(0, 1); 
  lcd.print("Phuc Vy");
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  pinMode(LED5_PIN, OUTPUT);
  pinMode(LED6_PIN, OUTPUT);
  pinMode(LED7_PIN, OUTPUT);
  pinMode(LED8_PIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');  // Đọc lệnh từ Serial

    if (command.startsWith("ON")) {
      int ledNumber = command.charAt(2) - '0'; // Lấy số LED (là ký tự số sau "ON")
      switch (ledNumber) {
        case 1: digitalWrite(LED1_PIN, HIGH); break;
        case 2: digitalWrite(LED2_PIN, HIGH); break;
        case 3: digitalWrite(LED3_PIN, HIGH); break;
        case 4: digitalWrite(LED4_PIN, HIGH); break;
        case 5: digitalWrite(LED5_PIN, HIGH); break;
        case 6: digitalWrite(LED6_PIN, HIGH); break;
        case 7: digitalWrite(LED7_PIN, HIGH); break;
        case 8: digitalWrite(LED8_PIN, HIGH); break;
        default: break;
      }
    }

    if (command.startsWith("OFF")) {
      int ledNumber = command.charAt(3) - '0'; // Lấy số LED (là ký tự số sau "OFF")
      switch (ledNumber) {
        case 1: digitalWrite(LED1_PIN, LOW); break;
        case 2: digitalWrite(LED2_PIN, LOW); break;
        case 3: digitalWrite(LED3_PIN, LOW); break;
        case 4: digitalWrite(LED4_PIN, LOW); break;
        case 5: digitalWrite(LED5_PIN, LOW); break;
        case 6: digitalWrite(LED6_PIN, LOW); break;
        case 7: digitalWrite(LED7_PIN, LOW); break;
        case 8: digitalWrite(LED8_PIN, LOW); break;
        default: break;
      }
    }
  }
}