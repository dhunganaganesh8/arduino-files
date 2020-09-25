#include <Servo.h>
#define trigpin1 4  //D2
#define echopin1 0   //D3

#define servo_pin 2 //D4

long duration1;
int distance1;

Servo servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(servo_pin);
  servo.write(0);
  servo.detach();

  pinMode(trigpin1, OUTPUT);
  pinMode(echopin1, INPUT);

  pinMode(servo_pin, OUTPUT);
  delay(5000);  

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigpin1, LOW);
  delayMicroseconds(2);

  digitalWrite(trigpin1, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigpin1, LOW);

  duration1 = pulseIn(echopin1, HIGH);
  distance1 = duration1*0.034/2;

  Serial.print("Distance :");
  Serial.println(distance1);
  delay(500);

  if(distance1 < 50)
  {
    servo.attach(servo_pin);
    delay(1);
    servo.write(0);  
    delay(3000);       
    servo.write(150);    
    delay(1000);
    servo.detach();
  }  

  delay(500);
}
