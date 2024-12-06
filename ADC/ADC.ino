#include <SimpleKalmanFilter.h>

#define LM35_PIN A0

// Khởi tạo bộ lọc Kalman với các tham số (R, Q, P)
SimpleKalmanFilter kalman(1, 1, 0.01);  

void setup() {
  Serial.begin(9600);  // Khởi tạo Serial với tốc độ 9600
  pinMode(LM35_PIN, INPUT);  // Cấu hình chân LM35 làm đầu vào
}

void loop() {
  // Đọc giá trị ADC từ cảm biến LM35 (0-1023)
  int adcValue = analogRead(LM35_PIN);

  // Chuyển đổi giá trị ADC thành điện áp
  float voltage = adcValue * (5.0 / 1023.0);  

  // Tính nhiệt độ bằng độ C (LM35 xuất ra 10mV/°C)
  float temperature = voltage * 100.0;

  // Áp dụng bộ lọc Kalman để làm mượt giá trị nhiệt độ
  float filteredTemperature = kalman.updateEstimate(temperature);

  // Xuất giá trị nhiệt độ đã được làm mượt qua Serial
  Serial.println(filteredTemperature);

  delay(500);  // Đợi 500ms trước khi đọc lại
}
