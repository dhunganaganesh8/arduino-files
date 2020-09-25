//nodeMCU #2
#include <Servo.h>

#define trigpin2 13 //D7
#define echopin2 12 //D6

#define servoPin 5  //D1

Servo servo;

long duration2;
int distance2;

void setup() {
  // put your setup code here, to run once:
 servo.attach(servoPin);
 servo.write(0);

  pinMode(trigpin2, OUTPUT);
  pinMode(echopin2, INPUT);


}

void loop()
{
  digitalWrite(trigpin2, LOW);
  delayMicroseconds(5);

  digitalWrite(trigpin2, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigpin2, LOW);

  duration2 = pulseIn(echopin2, HIGH);
  distance2 = duration2*0.034/2;

  Serial.print("Distance2: ");
  Serial.println(distance2);

  if(distance2 < 30)
  {
    for(int i=0; i<=180; i+=1)
    {
      servo.write(i);
      delay(10);
    }

    delay(5000);
    
    for(int i=180; i>=0; i-=1)
    {
      servo.write(i);
      delay(15);
    }
  }
}
