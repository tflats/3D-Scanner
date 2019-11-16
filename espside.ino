#include <ESP8266WiFi.h>
#include "Wire.h"

const char *ssid =  "NETGEAR28"; //"arrows"; //
const char *pass = "quaintsocks591"; //"RedFordF150"; //

WiFiServer server(420);

void setup()
{
  Serial.begin(9600);
  Serial.println("Start I2C scanner ...");
  Serial.print("\r\n");
  byte count = 0;
  delay(100);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting....");
  }
  Serial.println("\nConnected");
  server.begin();

  IPAddress servaddr = WiFi.localIP();
  Serial.print("Servers Address: ");
  Serial.println(servaddr);

  Wire.begin(8);
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0)
      {
      Serial.print("Found I2C Device: ");
      Serial.print(" (0x");
      Serial.print(i, HEX);
      Serial.println(")");
      count++;
      delay(1);
      }
  }
   Serial.print("\r\n");
  Serial.println("Finish I2C scanner");
  Serial.print("Found ");
  Serial.print(count, HEX);
  Serial.println(" Device(s).");
}

void loop()
{
    
}
