
# 🌡Temperature and humidity monitoring system and remote control of submersible water pump motor using Lora

## *Components:*
- Microcontroller: Arduino Nano (ATMega328P Old Bootloader)
- Display: OLED SSD 1306 128x64 0.96 inch & LCD 2.4INCH 240x320 TFT ILI9341
- Wireless: Module LORA SX1278 E32-433T20D (UART)
- Sensor: DHT11
- Other: Button, Resistor, Capacitor, IC7805, Led, Jack DC,...

Coding by Vinh Cao.
Language programing: C++ (PlatformIO - Visual Studio Code)

![images](https://cdn.platformio.org/images/platformio-logo.17fdc3bc.png)
![images](https://upload.wikimedia.org/wikipedia/commons/f/f3/Visual_Studio_Code_0.10.1_icon.png)

## Overview
#### Dự án này là đồ án 1 của mình phát triển trong môn học Project 1 (HK2 - Năm 3 - 2024 của Cao Văn Vinh, Khoa Điện - Điện tử - Trường ĐH Sư phạm Kỹ thuật Tp. HCM). Đồ án mang tính chất tham khảo.

### *Thiết kế và phát triển hệ thống giám sát và điều khiển động cơ bằng LoRa đáp ứng các yêu cầu:*

•	Khả năng giám sát và điều khiển động cơ từ xa một cách dễ dàng và hiệu quả.

•	Tầm hoạt động rộng, có thể lên đến vài km.

•	Độ tin cậy cao, khả năng chống nhiễu tốt.

•	Chi phí triển khai thấp, dễ dàng mở rộng.

![images](https://github.com/VinhCao09/LORA_Project1_ControlMotorandMonitor/blob/main/images/2.jpg)
![images](https://github.com/VinhCao09/LORA_Project1_ControlMotorandMonitor/blob/main/images/3.jpg)


## How to use
Tính toán transistor dẫn ở chế độ bão hòa:
![images](https://github.com/VinhCao09/LORA_Project1_ControlMotorandMonitor/blob/main/images/5.jpg)

##Schematic Master Block & Slave Block

![images](https://github.com/VinhCao09/LORA_Project1_ControlMotorandMonitor/blob/main/images/schematic.jpg)
make sure the com port is correct.

```bash
[env:nanoatmega328]
platform = atmelavr
board = nanoatmega328
framework = arduino
upload_port = COM[3]
monitor_speed = 9600
```

upload the code for Master & Slave

*Kết quả*

![images](https://github.com/VinhCao09/LORA_Project1_ControlMotorandMonitor/blob/main/images/1.jpg)


## ▶️Demo

https://www.youtube.com/watch?v=W1axdlKnvck

## 🚀 About Me
Hello 👋I am Vinh. I'm studying HCMC University of Technology and Education

**Major:** Electronics and Telecommunication

**Skill:** 

*- Microcontroller:* ESP32/8266 - ARDUINO - PIC - Raspberry Pi - PLC Rockwell Allen Bradley

*- Programming languages:* C/C++/HTML/CSS/PHP/SQL and
related Frameworks (Bootstrap)

*- Communication Protocols:* SPI, I2C, UART, CAN

*- Data Trasmissions:* HTTP, TCP/IP, MQTT

## Authors

- [@my_fb](https://www.facebook.com/vcao.vn)
- [@my_email](contact@vinhcaodatabase.com)

![Logo](https://codingninja.asia/images/codeninjalogo.png)

