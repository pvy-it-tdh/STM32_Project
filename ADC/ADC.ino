#define LM35_PIN A0 

void setup() {
  Serial.begin(9600);  // Khởi tạo Serial với tốc độ 9600
  pinMode(LM35_PIN, INPUT);  // Cấu hình chân LM35 làm đầu vào

  // Khởi tạo ADC
  analogReference(DEFAULT);  // Sử dụng nguồn tham chiếu mặc định
}

void loop() {
  // Đọc giá trị ADC từ cảm biến LM35 (0-1023)
  int adcValue = analogRead(LM35_PIN);

  // Chuyển đổi giá trị ADC thành nhiệt độ (LM35: 10mV/°C)
  float voltage = adcValue * (3.3 / 1023.0);  // Chuyển đổi giá trị ADC sang điện áp (0-5V)
  float temperature = voltage * 100.0;  // LM35 cung cấp 10mV/°C, do đó nhiệt độ = điện áp * 100

  // Gửi giá trị nhiệt độ qua Serial
  Serial.println(temperature);

  delay(500);  // Đợi 500ms trước khi đọc lại
}
