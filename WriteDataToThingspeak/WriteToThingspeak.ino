#include <WiFiS3.h>
#include "secrets.h"
#include "ThingSpeak.h"

#include <Wire.h>

#include "SparkFun_Particle_Sensor_SN-GCJA5_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_Particle_SN-GCJA5
SFE_PARTICLE_SENSOR myAirSensor;

WiFiClient client;

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int status = WL_IDLE_STATUS;


void setup() {
Serial.begin(115200);
ConnectWiFi();
ThingSpeak.begin(client);

  Serial.println(F("Panasonic SN-GCJA5 Example"));

  Wire.begin();

  if (myAirSensor.begin() == false)
  {
    Serial.println("The particle sensor did not respond. Please check wiring. Freezing...");
    while (1)
      ;
  }

  Serial.println("Sensor started");
  Serial.println("PM:1.0, 2.5, 10, Counts: 0.5, 1, 2.5, 5, 7.5, 10,");


}

void PrintNetwork()
{
Serial.print("WiFi Status: ");
Serial.println(WiFi.status());
Serial.print("SSID: ");
Serial.println(WiFi.SSID());
IPAddress ip = WiFi.localIP();
Serial.print("IP Address: ");
Serial.println(ip);
}

void ConnectWiFi()
{
// check for the WiFi module:
if (WiFi.status() == WL_NO_MODULE) {
Serial.println("Communication with WiFi module failed!");
while (true);
}
String fv = WiFi.firmwareVersion();
if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
Serial.println("Please upgrade the firmware");
}
// Attempt to connect to WiFi network:
while (status != WL_CONNECTED) {
Serial.print("Attempting to connect to WPA SSID: ");
Serial.println(ssid);
// Connect to WPA/WPA2 network:
status = WiFi.begin(ssid, pass);
// wait 10 seconds for connection:
delay(10000);
}
// You're connected now, so print out the data:
Serial.println("You're connected to Wifi");
PrintNetwork();
}


void ThingSpeakWrite(float channelValue, int channelField)
{
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
int x = ThingSpeak.writeField(myChannelNumber, channelField, channelValue, myWriteAPIKey);
if(x == 0){
Serial.println((String)"Channel " +channelField+ " updated successfully.");
}
else{
Serial.println("Problem updating channel. HTTP error code " + String(x));
}
}


void loop()
{
float pm1_0 = myAirSensor.getPM1_0();
  Serial.print(pm1_0, 2); //Print float with 2 decimals
  Serial.print(",");

ThingSpeakWrite(pm1_0, 3);
delay(2000);                   //TS needs a 15s delay between data sample uploads ***  but we have student license so its 1s now

}

