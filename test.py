import serial
import time

# Cấu hình cổng Serial
ser = serial.Serial('COM5', 9600, timeout=1)  # Thay đổi cổng phù hợp
time.sleep(2)  # Đợi STM32 khởi động

def send_command(command):
    ser.write((command + '\n').encode())  # Gửi lệnh kèm ký tự xuống dòng
    time.sleep(0.1)  # Chờ STM32 xử lý

# Điều khiển LED
send_command("ON1")  # Bật LED1
time.sleep(2)
send_command("OFF1")  # Tắt LED1
time.sleep(2)

# Đóng cổng Serial khi kết thúc
ser.close()
