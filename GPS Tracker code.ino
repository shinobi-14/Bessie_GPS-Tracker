#include <LoRa.h>
#include <TinyGPS++.h>
#include "FastLED.h"

#define NUM_LEDS 1
#define DATA_PIN 26

TinyGPSPlus tinyGPS;
#define GPS_BAUD 9600

// Use HardwareSerial on ESP32 (UART2)
HardwareSerial GPSSerial(2);

CRGB leds[NUM_LEDS];

void setup() 
{
  Serial.begin(115200);
  GPSSerial.begin(GPS_BAUD, SERIAL_8N1, 17, 16); // RX=17 (GPS TX), TX=16 (GPS RX)

  // LED setup
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(64);

  // LoRa setup
  Serial.println("LoRa Sender");
  LoRa.setPins(5, 32, 33);
  LoRa.setTxPower(20);
    
  if (!LoRa.begin(915E6)) {   // unchanged
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSignalBandwidth(125000); 
}  

void ledburn()
{
  leds[0] = CRGB(24,0,0);
  FastLED.show();
  delay(500);
  leds[0] = CRGB(0,24,0);
  FastLED.show();
  delay(500);
  leds[0] = CRGB(0,0,24);
  FastLED.show();
  delay(500);
  leds[0] = CRGB(12,0,12);
  FastLED.show();
  delay(500);
  leds[0] = CRGB(12,12,0);
  FastLED.show();
  delay(500);
  leds[0] = CRGB(0,12,12);
  FastLED.show();
  delay(500);
  leds[0] = CRGB(8,8,8);
  FastLED.show();
  delay(500);
}

void loraprint()
{
  LoRa.beginPacket();
  LoRa.println("This is Bessie");
  LoRa.print("Lat: "); LoRa.println(tinyGPS.location.lat(), 6);
  LoRa.print("Long: "); LoRa.println(tinyGPS.location.lng(), 6);
  LoRa.print("Alt: "); LoRa.println(tinyGPS.altitude.feet());
  LoRa.print("Course: "); LoRa.println(tinyGPS.course.deg());
  LoRa.print("Speed: "); LoRa.println(tinyGPS.speed.kmph());
  LoRa.print("Sats: "); LoRa.println(tinyGPS.satellites.value());
  LoRa.print("Date: ");
  LoRa.print(tinyGPS.date.day());
  LoRa.print("/");
  LoRa.print(tinyGPS.date.month());
  LoRa.print("/");
  LoRa.println(tinyGPS.date.year());
  LoRa.endPacket();
}

void loop() 
{
  ledburn();
  loraprint();
  smartDelay(100);
}
  
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (GPSSerial.available())
      tinyGPS.encode(GPSSerial.read());
  }
  while (millis() - start < ms);
}
