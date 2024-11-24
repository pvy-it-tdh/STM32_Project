# Dự Án Điều Khiển LED, Giám Sát Nhiệt Độ và Điều Khiển Tốc Độ Motor DC 24V với Giao Diện Python

## Tổng Quan Dự Án
Dự án này liên quan đến việc điều khiển 8 đèn LED, hiển thị thông tin nhiệt độ từ cảm biến LM35 trên màn hình LCD, và điều khiển tốc độ của motor DC 24V thông qua PWM sử dụng Driver H-Bridge MC33883. Giao tiếp giữa STM32 và giao diện Python được thực hiện qua UART. Giao diện Python cung cấp các điều khiển đồ họa để điều khiển đèn LED, hiển thị dữ liệu nhiệt độ và điều chỉnh tốc độ motor.

### Tính Năng Chính:
- Điều khiển 8 đèn LED thông qua giao diện Python.
- Hiển thị dữ liệu nhiệt độ từ cảm biến LM35 trên màn hình LCD.
- Cập nhật đồ thị nhiệt độ theo thời gian thực trên giao diện Python.
- Điều khiển tốc độ motor DC 24V qua PWM với Driver H-Bridge MC33883.

---

## Yêu Cầu

### Phần Cứng:
- Vi điều khiển STM32 (hỗ trợ framework Arduino).
- 8 đèn LED.
- Cảm biến Nhiệt Độ LM35.
- Màn hình LCD (I2C/SPI).
- Motor DC 24V.
- Driver H-Bridge MC33883.

### Phần Mềm:
- **Framework STM32 Arduino**: Cài đặt gói hỗ trợ STM32 trong Arduino IDE.
- **Thư Viện Python**:
  - `pySerial` cho giao tiếp UART.
  - `tkinter` hoặc `PyQt` cho giao diện người dùng.
  - `matplotlib` cho việc vẽ đồ thị nhiệt độ theo thời gian thực.

---

## Cài Đặt Phần Mềm STM32

1. **Cài Đặt Gói STM32 trong Arduino IDE:**
   - Mở Arduino IDE và vào `File > Preferences`.
   - Thêm URL của gói STM32 vào trường `Additional Boards Manager URLs`.
   - Vào `Tools > Board > Boards Manager` và cài đặt gói STM32.

2. **Kết Nối STM32 với Máy Tính:**
   - Sử dụng ST-Link hoặc USB-to-serial adapter để giao tiếp UART.

3. **Cấu Hình Chân Cắm:**
   - **LEDs:** Cấu hình 8 chân GPIO để điều khiển đèn LED.
   - **LM35:** Sử dụng chân ADC để đọc dữ liệu từ cảm biến LM35.
   - **Điều Khiển Motor:** Sử dụng chân PWM để điều khiển tốc độ motor.

4. **Cài Đặt Mã Lệnh:**
   - Trong sketch Arduino cho STM32, sử dụng thư viện `Serial` để giao tiếp UART.
   - Viết các hàm để đọc dữ liệu từ cảm biến LM35, điều khiển đèn LED và điều chỉnh tốc độ motor.
   - Đảm bảo dữ liệu được gửi đến Python theo định dạng có thể phân tích để cập nhật thời gian thực.
