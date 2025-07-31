#include <LiquidCrystal.h> 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int trigPin = 8;
const int echoPin = 7;



void setup() {
  // put your setup code here, to run once:
  
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 


lcd.begin(16,2); 
lcd.print("Distance: ");
 
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

// Clear trigpin and send ultrasonic signal //
digitalWrite(trigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH);
delayMicroseconds(10); 
digitalWrite(trigPin, LOW);

// Listen for the echo and measure time //
long duration = pulseIn(echoPin, HIGH); 

// Calculation for distance // 
float distance = (duration * .034) / 2; 

// Display on serial monitor // 
Serial.print("Distance: ");
Serial.print(distance, 1); 
Serial.println(" cm");

// Display on lcd // 
lcd.setCursor(0,0); 
lcd.print("Distance: "); 
lcd.setCursor(0,1); 
lcd.print(distance, 1); 
lcd.print(" cm"); 

delay(300); 

}
