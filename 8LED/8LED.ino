#define LED1_PIN  PA0  // Đổi theo chân LED của bạn
#define LED2_PIN  PA1  // Đổi theo chân LED của bạn
#define LED3_PIN  PA2  // Đổi theo chân LED của bạn
#define LED4_PIN  PA3  // Đổi theo chân LED của bạn
#define LED5_PIN  PA4  // Đổi theo chân LED của bạn
#define LED6_PIN  PA5  // Đổi theo chân LED của bạn
#define LED7_PIN  PA6  // Đổi theo chân LED của bạn
#define LED8_PIN  PA7  // Đổi theo chân LED của bạn

void setup() {
  // Khởi tạo cổng Serial
  Serial.begin(9600);
  
  // Cấu hình các chân LED là OUTPUT
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
