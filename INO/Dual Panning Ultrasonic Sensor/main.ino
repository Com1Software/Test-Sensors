#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 5;
const int echoPin2 = 6;

LiquidCrystal_I2C lcd(0x27,20,4);
long duration1;
int distance1;
int maxdistance1;
int mindistance1;
Servo myservo1; 
int position1;
long duration2;
int distance2;
int maxdistance2;
int mindistance2;
Servo myservo2; 
int position2;
void setup() {
  maxdistance1=0;
  maxdistance2=120;
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT); 
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT); 
  myservo1.attach(4);
  myservo2.attach(7);
  Serial.begin(9600); 
  lcd.init();
  lcd.backlight();
  }
void loop() {
  position1++;
  position2--;
  if (position1 > 120) position1 = 0, mindistance1=maxdistance1, maxdistance1=0;
   if (position2 < 1) position2 = 120, mindistance2=maxdistance2, maxdistance2=0;
  myservo1.write(position1);
  myservo2.write(position2);

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;
 
 
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;
 
 
 if (distance1 < 1000 and distance1 > maxdistance1 ) maxdistance1 = distance1;
 if (distance1 > 0 and distance1 < mindistance1 ) mindistance1 = distance1;
 if (distance2 < 1000 and distance2 > maxdistance2 ) maxdistance2 = distance2;
 if (distance2 > 0 and distance2 < mindistance2 ) mindistance2 = distance2;
 //------------------------
  lcd.setCursor(0,0);
  lcd.print("Dis");
  lcd.setCursor(5,0);
  lcd.print("     ");
  lcd.setCursor(5,0);
  lcd.print(distance1);
  lcd.setCursor(10,0);
  lcd.print("Dis");
  lcd.setCursor(15,0);
  lcd.print("     ");
  lcd.setCursor(15,0);
  lcd.print(distance2);
  //----------------
  
  lcd.setCursor(0,1);
  lcd.print("Min");
  lcd.setCursor(5,1);
  lcd.print("     ");
  lcd.setCursor(5,1);
  lcd.print(mindistance1);
   lcd.setCursor(10,1);
  lcd.print("Min");
  lcd.setCursor(15,1);
  lcd.print("     ");
  lcd.setCursor(15,1);
  lcd.print(mindistance2);


  lcd.setCursor(0,2);
  lcd.print("Max");
  lcd.setCursor(5,2);
  lcd.print("     ");
  lcd.setCursor(5,2);
  lcd.print(maxdistance1);

  lcd.setCursor(10,2);
  lcd.print("Max");
  lcd.setCursor(15,2);
  lcd.print("     ");
  lcd.setCursor(15,2);
  lcd.print(maxdistance2);


  //---------------------
  lcd.setCursor(0,3);
  lcd.print("Pos");
  lcd.setCursor(5,3);
  lcd.print("     ");
  lcd.setCursor(5,3);
    lcd.print(position1);
   lcd.setCursor(10,3);
  lcd.print("Pos");
  lcd.setCursor(15,3);
  lcd.print("     ");
  lcd.setCursor(15,3);
    lcd.print(position2);
  //--------------------

  Serial.print("DIS1=");
  Serial.print(distance1);
   Serial.print(",POS1=");
  Serial.print(position1);
  Serial.print(",MIN1=");
  Serial.print(mindistance1);
  Serial.print(",MAX1=");
  Serial.print(maxdistance1);
   Serial.print(",DIS2=");
  Serial.print(distance2);
   Serial.print(",POS2=");
  Serial.print(position2);
  Serial.print(",MIN2=");
  Serial.print(mindistance2);
  Serial.print(",MAX2=");
  Serial.println(maxdistance2);
  }
