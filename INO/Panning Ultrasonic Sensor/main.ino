#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const int trigPin = 2;
const int echoPin = 3;
LiquidCrystal_I2C lcd(0x27,20,4);
long duration;
int distance;
int maxdistance;
int mindistance;
Servo myservo1; 
int position;
void setup() {
  maxdistance=0;
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  myservo1.attach(4);
  Serial.begin(9600); 
  lcd.init();
  lcd.backlight();
  }
void loop() {
  position++;
  if (position > 120) position = 0, mindistance=maxdistance, maxdistance=0;
  myservo1.write(position);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
 if (distance < 1000 and distance > maxdistance ) maxdistance = distance;
 if (distance > 0 and distance < mindistance ) mindistance = distance;
  lcd.setCursor(0,0);
  lcd.print("Distance");
  lcd.setCursor(9,0);
  lcd.print("     ");
  lcd.setCursor(9,0);
  lcd.print(distance);
  //----------------
  
  lcd.setCursor(0,1);
  lcd.print("Max");
  lcd.setCursor(4,1);
  lcd.print("     ");
  lcd.setCursor(5,1);
  lcd.print(maxdistance);

  lcd.setCursor(10,1);
  lcd.print("Min");
  lcd.setCursor(14,1);
  lcd.print("     ");
  lcd.setCursor(15,1);
  lcd.print(mindistance);
  //---------------------
  lcd.setCursor(0,2);
  lcd.print("Position");
  lcd.setCursor(9,2);
  lcd.print("     ");
  lcd.setCursor(9,2);
  lcd.print(position);
  Serial.print("DIS=");
  Serial.println(distance);
  Serial.print("POS=");
  Serial.println(position);
}
