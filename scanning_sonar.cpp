#include <LiquidCrystal.h> 
#include <AccelStepper.h> 

const int trig = A0;
const int echo = A1;
const int buzzer = A2;
const int motorSpeed = 500;
const int distThresh = 20;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
AccelStepper stepper(AccelStepper::FULL4WIRE, 8, 10, 9, 11);

void information(int step) {


  digitalWrite(trig, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig, LOW);

  
  long duration = pulseIn(echo, HIGH); 
  long distance = duration * .034 / 2; 

  if (distance <= distThresh) {
    tone(buzzer, 1000);
    delay(2000); 
    noTone(buzzer);
  }

// Serial Display
  Serial.print("Step: "); 
  Serial.print(step); 
  Serial.print(" | Distance: "); 
  Serial.print(distance);
  Serial.print("cm"); 


// LCD Display
  lcd.clear(); 
  lcd.setCursor(0,0); 
  lcd.print("Distance: "); 
  lcd.print(distance); 
  lcd.print("cm"); 

}


void setup() {

stepper.setCurrentPosition(0); 
pinMode(echo, INPUT);
pinMode(trig, OUTPUT);

lcd.begin(16, 2); 
lcd.setCursor(0,0);
lcd.print("Ultrasonic Detection");
lcd.setCursor(0,1); 
lcd.print("System");
delay(4000);
lcd.clear();

pinMode(buzzer, OUTPUT);

stepper.setMaxSpeed(motorSpeed); 
stepper.setAcceleration(500); 

Serial.begin(9600); 
}


void loop() {


for (int i = 0; i <= 1024; i += 50) {
  int step = i;
  stepper.moveTo(i); 
  stepper.runToPosition(); 
  information(step);
  delay(100); 
}


for (int i = 1024; i >= 0; i -= 50) {
  int step = i; 
  stepper.moveTo(i);
  stepper.runToPosition(); 
  information(step); 
  delay(100);
}



}
