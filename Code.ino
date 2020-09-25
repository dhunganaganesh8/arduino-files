#include <ESP8266WiFi.h>
#include <Servo.h>
#include <ThingSpeak.h>

#define trigpin2 12 //D6
#define echopin2 14 //D5

const char* ssid = "my ssid";
const char* pass = "ssid pass";

unsigned long chId = chId;
const char* apiKey = "api key";

long duration;
int distance;

WiFiClient client;

void setup()
{
  Serial.begin(115200);

  pinMode(trigpin1, OUTPUT);
  pinMode(echopin1, INPUT);
  
  WiFi.disconnect();
  delay(5000);

  Serial.print("Connecting to ");
  Serial.print(ssid);
  delay(500);
  
  WiFi.begin(ssid, pass);

  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }

  ThingSpeak.begin(client);
}

void loop()
{
  digitalWrite(trigpin1, LOW);
  delayMicroseconds(5);

  digitalWrite(trigpin1, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigpin1, LOW);

  duration = pulseIn(echopin1, HIGH);
  distance = duration*0.034/2;

  Serial.print("Distance: ");
  Serial.println(distance);

  ThingSpeak.setField(1, distance);
  ThingSpeak.writeFields(chId, apiKey);

  delay(1000);
}
