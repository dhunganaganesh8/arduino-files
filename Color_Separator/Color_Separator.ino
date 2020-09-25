#include <Servo.h>
#include <Stepper.h>
#include <BlynkSimpleEthernet.h>

#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

Servo servo;

int frequency = 0;
int color=0;
const int stepsPerRevolution = 8;

Stepper myStepper(stepsPerRevolution, 7, 8, 9, 10);
BlynkTimer timer;

void setup() 
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 20%
  
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
  servo.attach(11);
  servo.write(0);
  delay(50);
  
  Serial.begin(9600);
  
  timer.setInterval(3000L, readColor);
}

void loop() {
  myStepper.step(1);
  delay(3000);  
  timer.run();  
}


// Custom Function - readColor()
void readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(50);
  
  
  if(R<45 & R>32 & G<65 & G>55)
  {
     servo.write(30); // Red
  }  
  if(R<53 & R>40 & G<53 & G>40)
  {
    servo.write(60); // Green
  }
  if(R<38 & R>24 & G<44 & G>30)
  {
    servo.write(90); // Yellow
  }
  if(G<58 & G>45 & B<40 & B>26)
  {
    servo.write(120); // Blue
  }
    
}
