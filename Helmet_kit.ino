#include <Wire.h>
#include <Adafruit_SSD1306.h> // Include the OLED library
#include <WiFi.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET); // Initialize OLED display object

const char* ssid     = "wifi010";
const char* password = "12345678";

const char* host = "iotproject2024.000webhostapp.com";
const char* streamId   = "....................";
const char* privateKey = "....................";

#include <Adafruit_Sensor.h>
#include "DHT.h"
DHT dht;
//#define DHTPIN 15     // Digital pin connected to the DHT sensor
//#define DHTTYPE DHT11 // DHT 11

//DHT dht(DHTPIN, DHTTYPE);

//const int gasSensorPin = 7; // Define the pin where the digital output of the MQ sensor is connected

void setup(void) {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
dht.setup(15); 
  //Wire.begin(21, 22);

  // Initialize OLED display with Adafruit_SSD1306 constructor
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  display.display(); // Display Adafruit logo
  delay(2000);
  display.clearDisplay(); // Clear the display buffer

  display.setTextSize(1);      // Set text size
  display.setTextColor(SSD1306_WHITE); // Set text color
  display.setCursor(0, 0);     // Set cursor position
  display.println("Smart Helmet");
  display.println("for Mine workers");
  display.display(); // Display message

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);


    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
   
  delay(2000);

  display.clearDisplay(); // Clear the display buffer

  display.setTextSize(1);      // Set text size
  display.setTextColor(SSD1306_WHITE); // Set text color
  display.setCursor(0, 0);     // Set cursor position
  display.println("Smart Helmet");
  display.println("for Mine workers");
  display.display(); // Display message

  delay(2000);

  display.clearDisplay(); // Clear the display buffer
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("TP:       HM:    ");
  display.println("ST:");
  pinMode(12, INPUT);
  display.display();
  delay(2000);

 // pinMode(gasSensorPin, INPUT); // Initialize the gas sensor pin as input
}

void loop(void) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("TP:       HM:    ");
  display.println("ST:     ");

  temperature();
  humidity();
//  gasSensor();

  if (!digitalRead(12)) {
    display.setCursor(0, 18);
    display.println("Mine CLPD at L1");
  } else {
    display.setCursor(0, 15);
    display.println("ST: Normal");
  }

  display.display();
  delay(2000);
}

void temperature() {
  float tp = dht.getTemperature(); //dht.readTemperature(false);
  display.setCursor(20, 0);
  display.print("   ");
  display.setCursor(20, 0);
  display.print(tp);

  Serial.print("Temp: ");
  Serial.println(tp);
}

void humidity() {
  float hum = dht.getHumidity(); //dht.readHumidity();
  display.setCursor(80, 0);
  display.print("   ");
  display.setCursor(80, 0);
  display.print(hum);

  Serial.print("Hum: ");
  Serial.println(hum);
}
/*
void gasSensor() {
  int sensorValue = digitalRead(gasSensorPin);
  if (sensorValue == HIGH) {
    Serial.println("Hazardous gases detected!");
    display.setCursor(0, 25);
    display.println("Hazardous gases detected!");
  } else {
    Serial.println("Hazardous gases not detected.");
    display.setCursor(0, 25);
    display.println("Hazardous gases not detected.");
  }
}*/
