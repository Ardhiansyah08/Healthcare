#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

const char *ssid = "WiFi Yang Digunakan"; //SSID here
const char *pass = "Pass WiFi Yang Digunakan"; // Passowrd here
WiFiClient client;

unsigned long myChannelNumber =  ID Channel Thingspeak ; 
const char myWriteAPIKey[] = "Write API Key Channel Thingspeak"; 

int beat, bpm;
unsigned long millisBefore;
boolean countStatus;
// the setup routine runs once when you press reset:

void setup() {
  Serial.begin(9600);

   WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();  
  Serial.println("Mikrokontroler is connected!");
  ThingSpeak.begin(client);
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  //Serial.println(sensorValue);
  if (countStatus == 0) {
    if (sensorValue > 600) {
      countStatus = 1;
      beat++;
      Serial.println("Beat Detected!");
      Serial.print("Beat : ");
      Serial.println(beat);
    }
  } else{
    if (sensorValue < 500) {
      countStatus = 0;
    }
  }
  if (millis()-millisBefore>15000){
    bpm=beat*4;
    beat=0;
    Serial.print("BPM : ");
    Serial.println(bpm);
    millisBefore=millis();
  }
  ThingSpeak.writeField(myChannelNumber, No field thingspeak, Variabel Output, myWriteAPIKey);
  delay(1);        // delay in between reads for stability
}