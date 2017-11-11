#include <Arduino.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <FS.h>

const char *ssid = "Studio20";        //  your network SSID (name)
const char *password = "Zulu1India2"; // your network password
String WebString = "";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setArduinoClock()
{
  // thinking about adding this function to the loop, so that the Arduino clock doesn't get too far out time.
  // might write something that only updates the clock every 10 minutes or so

  timeClient.update();
  setTime(timeClient.getEpochTime()); // set the arduino clock (Timelib) might have to do this every 10 mins or so
}
void CompileWebPage()
{

  File indexFile = SPIFFS.open("/index.htm", "r");
  if (!indexFile)
  {
    Serial.println("file open failed");
  }

  // WebString.reserve(5000); // this might be useful if we run out of flash memory

  while (indexFile.available())
  {
    WebString += indexFile.readStringUntil('\n');
    WebString += '\n';
  }

  indexFile.close();
}
void StartWifiConnection()
{

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
}
void setup()
{
  Serial.begin(115200);

  StartWifiConnection();

  timeClient.begin(); // this is to get time from the NTP client

  setArduinoClock();

  SPIFFS.begin();
}

void loop()
{

  CompileWebPage();
  Serial.print(WebString);

  // timeClient.update();

  // Serial.println(timeClient.getFormattedTime());

  Serial.print("the hours is : ");
  Serial.println(hour());

  Serial.print(" the min is: ");
  Serial.println(minute());

  Serial.print("the second is : ");
  Serial.println(second());

  // Serial.println(timeClient.getHours());

  // delay(1000);
}
