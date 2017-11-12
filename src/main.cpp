#include <Arduino.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <FS.h>

const char *ssid = "Studio20";        //  your network SSID (name)
const char *password = "Zulu1India2"; // your network password
String WebString = "";
String TimeString = "";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

WiFiServer server(80);

void setArduinoClock()
{
  if (year() <= 1970) // this is so it only starts the timeclient once, unless we go back to 1970 for some reason!
  {
    timeClient.begin(); // this is to get time from the NTP client
    delay(50);
    timeClient.update();
  }

  if (minute() % 5 == 0) /// this is so we only do a server time check every 5 minutes.
  {
    timeClient.update();
    setTime(timeClient.getEpochTime()); // set the arduino clock (Timelib) might have to do this every 10 mins or so
  }
}
void StartWifiConnection()
{

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  server.begin();

  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}
void UpdateTimeString()
{

  TimeString = ""; // clear the string
  if (hour() < 10)
  {
    TimeString += "0";
  }
  TimeString += hour();
  TimeString += ":";
  if (minute() < 10)
  {
    TimeString += "0";
  }
  TimeString += minute();
  TimeString += ":";
  if (second() < 10)
  {
    TimeString += "0";
  }
  TimeString += second();

}
void CompileWebPage()
{
  WebString = "";
  File indexFile = SPIFFS.open("/index.htm", "r");
  if (!indexFile)
  {
    Serial.println("file open failed");
  }

  // WebString.reserve(5000); // this might be useful if we run out of flash memory

  WebString += "HTTP/1.1 200 OK";
  WebString += "Content-Type: text/html";

  WebString += '\n'; // a new line here is important

  while (indexFile.available())
  {
    WebString += indexFile.readStringUntil('\n');
    WebString += '\n';
  }

  WebString.replace("#TIME_PLACEHOLDER#", TimeString);

  indexFile.close();
}
bool clientConnected()
{

  WiFiClient client = server.available();
  if (!client)
  {
    return false;
  }

  // DealWithClientRequest(); // i was going to split everthing below this mark, into another function

  // Wait until the client sends some data
  Serial.println("new client");

  while (!client.available())
  {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  UpdateTimeString();
  CompileWebPage();
  client.print(WebString);
}

void setup()
{
  Serial.begin(115200);

  StartWifiConnection();

  setArduinoClock();

  SPIFFS.begin();

}

void loop()
{

  setArduinoClock();

  if (!clientConnected())
  {
    return;
  }

}
