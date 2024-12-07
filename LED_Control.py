import tkinter as tk
from tkinter import ttk
import serial
import threading
import time
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# Cấu hình cổng serial
try:
    ser = serial.Serial('COM5', 9600, timeout=1)  # Đổi 'COM5' theo cổng STM32 của bạn
except serial.SerialException:
    ser = None
    print("Không thể mở cổng serial. Kiểm tra kết nối!")

# Hàm điều khiển tốc độ động cơ
def set_motor_speed():
    if ser and ser.is_open:
        try:
            speed_value = int(speed_entry.get())
            if 0 <= speed_value <= 100:
                command = f'SPEED{speed_value}\n'.encode()
                ser.write(command)
                motor_status_label.config(text=f"Tốc độ động cơ: {speed_value}%", fg="blue")
            else:
                motor_status_label.config(text="Giá trị không hợp lệ! Nhập từ 0 đến 100.", fg="red")
        except ValueError:
            motor_status_label.config(text="Lỗi: Giá trị không hợp lệ!", fg="red")

# Hàm bật/tắt LED
def turn_on_led(led_number):
    if ser and ser.is_open:
        command = f'ON{led_number}\n'.encode()
        ser.write(command)
        status_labels[led_number - 1].config(text=f"LED {led_number}: BẬT", fg="green")

def turn_off_led(led_number):
    if ser and ser.is_open:
        command = f'OFF{led_number}\n'.encode()
        ser.write(command)
        status_labels[led_number - 1].config(text=f"LED {led_number}: TẮT", fg="red")

# Đọc dữ liệu nhiệt độ
temperatures = []
time_stamps = []
def update_graph():
    line.set_data(time_stamps, temperatures)
    ax.relim()
    ax.autoscale_view()
    canvas.draw_idle()

def read_temperature():
    while True:
        if ser and ser.is_open:
            if ser.in_waiting > 0:
                try:
                    raw_data = ser.readline().decode().strip()
                    temperature_value = float(raw_data)
                    temperatures.append(temperature_value)
                    time_stamps.append(time_stamps[-1] + 0.5 if time_stamps else 0)
                    if len(temperatures) > 50:
                        temperatures.pop(0)
                        time_stamps.pop(0)
                    temperature_label.config(text=f"Nhiệt độ: {temperature_value:.2f} °C")
                    update_graph()
                except ValueError:
                    pass
        time.sleep(0.5)

# Giao diện Tkinter
root = tk.Tk()
root.title("Điều khiển LED và Động cơ với STM32")
root.geometry("900x600")
root.configure(bg="#f0f0f0")

# Tiêu đề
title_label = tk.Label(root, text="CONTROL", font=("Arial", 16, "bold"), bg="#f0f0f0")
title_label.grid(row=0, column=0, columnspan=2, pady=10)

# Khung điều khiển LED
led_frame = tk.LabelFrame(root, text="Điều khiển LED", font=("Arial", 12), bg="#e0e0e0", padx=10, pady=10)
led_frame.grid(row=1, column=0, sticky="nw", padx=20, pady=10)

status_labels = []
for i in range(1, 9):
    row = (i - 1) // 4
    col = (i - 1) % 4
    led_control = tk.Frame(led_frame, bg="#e0e0e0")
    led_control.grid(row=row, column=col, padx=10, pady=5)
    tk.Label(led_control, text=f"LED {i}", bg="#e0e0e0", font=("Arial", 10)).pack()
    ttk.Button(led_control, text="Bật", command=lambda i=i: turn_on_led(i)).pack(pady=2)
    ttk.Button(led_control, text="Tắt", command=lambda i=i: turn_off_led(i)).pack(pady=2)
    status_label = tk.Label(led_control, text="TẮT", font=("Arial", 10), fg="red", bg="#e0e0e0")
    status_label.pack()
    status_labels.append(status_label)

# Khung điều khiển động cơ
motor_frame = tk.LabelFrame(root, text="Điều khiển Động cơ", font=("Arial", 12), bg="#d0d0d0", padx=10, pady=10)
motor_frame.grid(row=2, column=0, sticky="nw", padx=20, pady=10)

tk.Label(motor_frame, text="Tốc độ (0-100%):", bg="#d0d0d0", font=("Arial", 10)).pack(pady=5)
speed_entry = ttk.Entry(motor_frame, width=10)
speed_entry.pack(pady=5)
set_speed_button = ttk.Button(motor_frame, text="Cài đặt", command=set_motor_speed)
set_speed_button.pack(pady=5)
motor_status_label = tk.Label(motor_frame, text="Tốc độ động cơ: --%", font=("Arial", 10), fg="gray", bg="#d0d0d0")
motor_status_label.pack(pady=5)

# Đồ thị nhiệt độ
graph_frame = tk.LabelFrame(root, text="Đồ thị Nhiệt độ", font=("Arial", 12), bg="#f0f0f0", padx=10, pady=10)
graph_frame.grid(row=1, column=1, rowspan=2, sticky="nsew", padx=20, pady=10)

fig = Figure(figsize=(5, 4), dpi=100)
ax = fig.add_subplot(1, 1, 1)
line, = ax.plot([], [], 'b-', marker='o')
ax.set_title("Nhiệt độ theo thời gian")
ax.set_xlabel("Thời gian (s)")
ax.set_ylabel("Nhiệt độ (°C)")
canvas = FigureCanvasTkAgg(fig, master=graph_frame)
canvas.get_tk_widget().pack()

# Đóng kết nối serial
def on_closing():
    if ser and ser.is_open:
        ser.close()
    root.destroy()

root.protocol("WM_DELETE_WINDOW", on_closing)

# Luồng đọc nhiệt độ
if ser:
    temperature_thread = threading.Thread(target=read_temperature, daemon=True)
    temperature_thread.start()

root.mainloop()
