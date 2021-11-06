#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

/* Pin connections to Arduino:
 * 
 * GPS 
 * Vcc --> +5V
 * GND --> analog GND
 * RX --> D4
 * TX --> D3
 * 
 * Display
 * VDD --> +5V
 * GND --> analog GND
 * SCK --> A5
 * SDA --> A4
 */

static const int RXPin = 3, TXPin = 4; //GPS communication
static const uint32_t GPSBaud = 9600;

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET); //Connection to I2C SCK and SDA

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

double maxDist = 0, trip = 0, currDist = 0;  
double maxAlt = 0, currAlt = 0;
double originLat = 0, originLong = 0;
double currLat = 0, currLong = 0;
double maxVel = 0, currVel = 0;
int dispDelay = 500; //miliseconds

void setup()
{
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);// initialize with the I2C addr 0x3C (for the 128x32)(initializing the display)

  ss.begin(GPSBaud);

  // Startup message
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("GPS Tracker ");
  display.setCursor(0, 10);
  display.print("v1.0 ");
  display.setCursor(0, 20);
  display.print("by Jubeezoobi ");
  display.display(); //show
  delay(2*dispDelay);

  // User personal message
  display.setCursor(0, 0);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Shahar");
  display.setCursor(0, 10);
  display.print("Ta'ase Li");
  display.setCursor(0, 20);
  display.print("Yeled");
  display.display(); // show
  delay(2*dispDelay);
}

void loop()
{
  // Determine origin position
  if (originLat <= 0) {
      if (ss.available() > 0) {
        gps.encode(ss.read());
        if (gps.location.isUpdated()){
          originLat = gps.location.lat();
          originLong = gps.location.lng();
          delay(2*dispDelay); 
        }
      }
    }

  else {
    // Run update loop if satelites are available
    while (ss.available() > 0) {
      gps.encode(ss.read());
      if (gps.location.isUpdated()){
  
        // Show current location (lat, long) - just any location  
        currLat = gps.location.lat();
        currLong = gps.location.lng();
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.print("CURRENT: ");
        display.setCursor(0, 10);
        display.print("LAT= "); display.print(currLat, 6);
        display.setCursor(0, 20);
        display.print("LONG= "); display.print(currLong, 6);
        display.display();
        delay(5*dispDelay);
  
        // Show origin location (lat, long) - first location that is not (0, 0)
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.print("ORIGIN: ");
        display.setCursor(0, 10);
        display.print("LAT= "); display.print(originLat, 6);
        display.setCursor(0, 20);
        display.print("LONG= "); display.print(originLong, 6);
        display.display();
        delay(5*dispDelay);
  
        // Show distance - maximum from origin [m] and trip [m]
        currDist = ceil(sqrt(pow((currLat - originLat),2) + pow((currLong - originLong),2)));
        trip = trip + currDist;
        if (currDist > maxDist) {
          maxDist = currDist;
        }
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.print("DIST: ");
        display.setCursor(0, 10);
        display.print("MAX [m] = "); display.print(maxDist);
        display.setCursor(0, 20);
        display.print("TRIP [m] = "); display.print(trip);
        display.display();
        delay(5*dispDelay);
  
        // Show altitude - current [m] and maximum [m]
        currAlt = gps.altitude.meters();
          if (currAlt > maxAlt) {
            maxAlt = currAlt;
          }
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.print("ALT: ");
          display.setCursor(0, 10);
          display.print("CURR [m] = "); display.print(currAlt);
          display.setCursor(0, 20);
          display.print("MAX [m] = "); display.print(maxAlt);
          display.display();
          delay(5*dispDelay);

          // Show velocity - current [Km/h] and maximum [Km/h]
        currVel = gps.speed.kmph();
          if (currVel > maxVel) {
            maxVel = currVel;
          }
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.print("VELOCITY: ");
          display.setCursor(0, 10);
          display.print("CURR [Km/h] = "); display.print(currVel);
          display.setCursor(0, 20);
          display.print("MAX [Km/h] = "); display.print(maxVel);
          display.display();
          delay(5*dispDelay);
      }
    }
  } 
}
  
  
