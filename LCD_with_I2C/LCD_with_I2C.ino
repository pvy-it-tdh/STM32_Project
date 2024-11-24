#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Địa chỉ I2C (có thể thay đổi thành 0x3F hoặc khác)

void setup() {
  lcd.begin(16, 2);                // Khởi tạo LCD 16x2
  lcd.backlight();                 // Bật đèn nền
  lcd.print("Hello, STM32!");      // Hiển thị nội dung
}

void loop() {
  // Đoạn mã cho vòng lặp chính (nếu cần)
}
