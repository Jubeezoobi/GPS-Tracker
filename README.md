# GPS-Tracker
Connecting to GPS satellites and keeps record of maximum velocity and altitude on a small LCD display
I've taken the same hardware as other projects found on the web and completely rewrote the code to use tinyGPS++ library.

Hardware:
- Arduino Nano R3
- LCD screen: 0,96 Zoll OLED I2C Display 128 x 64 pixels compatible with Arduino and Raspberry Pi
- NEO-6M GPS module

Pin configuration:
GPS 
 * Vcc --> +5V
 * GND --> analog GND
 * RX --> D4
 * TX --> D3
Display
 * VDD --> +5V
 * GND --> analog GND
 * SCK --> A5
 * SDA --> A4

Arduino libraries used:
<Wire.h>
<Adafruit_GFX.h>
<Adafruit_SSD1306.h>
<TinyGPS++.h>
<SoftwareSerial.h>
