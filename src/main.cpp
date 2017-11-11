#include <Arduino.h>

/*
 * Time_NTP.pde
 * Example showing time sync to NTP time source
 *
 * This sketch uses the ESP8266WiFi library
 */
 
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "Studio20";  //  your network SSID (name)
const char *password = "Zulu1India2";       // your network password

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());

  delay(1000);
}
