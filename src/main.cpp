#include <Arduino.h>

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TimeLib.h>

const char *ssid = "Studio20";        //  your network SSID (name)
const char *password = "Zulu1India2"; // your network password

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  timeClient.begin(); // this is to get time from the NTP client
  timeClient.update();
  setTime(timeClient.getEpochTime()); // set the arduino clock (Timelib)
}

void loop()
{
  // timeClient.update();

  // Serial.println(timeClient.getFormattedTime());

  Serial.print("the hours is : ");
  Serial.println(hour());

  Serial.print(" the min is: ");
  Serial.println(minute());

  Serial.print("the second is : ");
  Serial.println(second());

  // Serial.println(timeClient.getHours());

  delay(1000);
}
