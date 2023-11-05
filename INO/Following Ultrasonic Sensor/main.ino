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
int fposition;
int fpon;
int fdist;
void setup() {
  maxdistance=0;
  fposition=0; 
  fdist=0; 
  fpon=0;
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  myservo1.attach(4);
  Serial.begin(115200); 
  lcd.init();
  lcd.backlight();
  }
void loop() {
  // position = position +10;
 if (fpon==0)position ++;
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
 if (distance > 0 and distance < mindistance ) mindistance = distance, fposition=position;
 // if (distance+200>fdist and fpon==1) fpon=0;
 if (fposition > 10 and fpon==0 ) {
  position = fposition,fpon=1,fdist=distance;
  lcd.setCursor(10,0);
  lcd.print("Locked");

 }else {
  if (distance+200>fdist) fpon=0;
   lcd.setCursor(10,0);
   lcd.print("Unlocked");
 }
  lcd.setCursor(0,0);
  lcd.print("Dist");
  lcd.setCursor(5,0);
  lcd.print("     ");
  lcd.setCursor(5,0);
  lcd.print(distance);
  //----------------
  
  lcd.setCursor(0,1);
  lcd.print("MaxD");
  lcd.setCursor(5,1);
  lcd.print("     ");
  lcd.setCursor(5,1);
  lcd.print(maxdistance);

  lcd.setCursor(10,1);
  lcd.print("MinD");
  lcd.setCursor(15,1);
  lcd.print("     ");
  lcd.setCursor(15,1);
  lcd.print(mindistance);
  //---------------------
  lcd.setCursor(0,2);
  lcd.print("Pos");
  lcd.setCursor(4,2);
  lcd.print("     ");
  lcd.setCursor(4,2);
  lcd.print(position);
  //-----------------
  lcd.setCursor(0,3);
  lcd.print("FP");
  lcd.setCursor(3,3);
  lcd.print("   ");
  lcd.setCursor(3,3);
  lcd.print(fposition);

   lcd.setCursor(7,3);
  lcd.print("FD");
  lcd.setCursor(10,3);
  lcd.print("    ");
  lcd.setCursor(10,3);
  lcd.print(fdist);

  //-----------------
  Serial.print("DIS=");
  Serial.println(distance);
  Serial.print("POS=");
  Serial.println(position);
}
