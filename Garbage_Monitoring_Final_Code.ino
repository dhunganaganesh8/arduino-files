//nodeMCU #1

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ThingSpeak.h>


#define trigpin1 2  //D4        
#define echopin1 0  //D3

#define buzzPin 4   //D2

unsigned long chId = 979445;
const char* apiKey = "my api key";

char auth[] = "auth key";

char ssid[] = "my ssid";
char pass[] = "ssid pass";

WiFiClient client;
BlynkTimer timer;


void UltraSonicSensor(){
  long duration1;
  int distance1;

  digitalWrite(trigpin1, LOW);
  delayMicroseconds(5);

  digitalWrite(trigpin1, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigpin1, LOW);

  duration1 = pulseIn(echopin1, HIGH);
  distance1 = duration1*0.034/2;

  Serial.print("Distance1: ");
  Serial.println(distance1);
  
  Blynk.virtualWrite(V5, distance1);  
  Blynk.virtualWrite(V6, distance1);

  if(distance1 <= 15){
    Blynk.email("mail1@gmail.com", "Dustbin Alert", "Dustbin is nearly full!");
    Blynk.email("mail2@gmail.com", "Dustbin Alert", "Dustbin is nearly full!");
    Blynk.email("mail3@gmail.com", "Dustbin Alert", "Dustbin is nearly full!");
    Blynk.email("mail4@gmail.com", "Dustbin Alert", "Dustbin is nearly full!");
    Blynk.notify("Dustbin is nearly full!");
  }

  ThingSpeak.setField(1, distance1);
  ThingSpeak.writeFields(chId, apiKey);
  
}

void setup(){
  Serial.begin(115200);
 

  pinMode(trigpin1, OUTPUT);
  pinMode(echopin1, INPUT);

  pinMode(buzzPin, OUTPUT);
  digitalWrite(buzzPin, LOW);

  WiFi.disconnect();
  delay(5000);

  Serial.print("Connecting to ");
  delay(500);
  Serial.print(ssid);
  delay(500);
  
  WiFi.begin(ssid, pass);

  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
  
  Blynk.config(auth);
  delay(5000);

  ThingSpeak.begin(client);
  
  timer.setInterval(10000L, UltraSonicSensor);
}

void loop(){
  Blynk.run();
  timer.run();
  
  
}
