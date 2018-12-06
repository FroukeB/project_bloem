//#include <LiquidCrystal.h> // includes the LiquidCrystal Library

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Addr, En, Rw, Rs, d4, d5, d6, d7, backlighpin, polarity

#include <Servo.h>
Servo myservo;  // create servo object to control a servo

const int trigPin = 9;
const int echoPin = 10;

long duration; // tijd dat de geluidsgolf nodig heeft van juitsturen naar terug
int distanceToCm;

int proximity = 0;
float graden;

float currentGraden = 0;

void setup() {
  myservo.attach(11);
  Serial.begin(9600);
  lcd.begin(16,2); // display instellen met width en height
  lcd.clear();
  lcd.print("hello, world");
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myservo.write(0); 
}
void loop() {
  
  // 2 miliseconden nemen om de trigPin vrij te maken
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // 10 seconden high state om ultra sound te produceren
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  // pulseIn is er om de tijd lezen die het geluid nodig heeft om uitgestuurd te worden te weerkaatsen en terug te keren
  // 2 parameters: 1 pin echo ontvanger geluid op high zetten de functie zal wachten tot de pin op hight is dit veroorzaakt door de gestuiterde geluidsgolf en het begint te timen, dan zal het wachten tot de pin LOW gaat wanneer de geluidsgolf zal eindigen wat de timing zal stoppen
  // duur van die puls keert terug en wordt doorgestuurd
  duration = pulseIn(echoPin, HIGH);
  
  // *0.034 de snelheid dat geluid zich in verplaatst en /2 omdat het 2 wegen doet = uitsturen en terug keren
  distanceToCm= duration*0.034/2;
  
  // lcd scherm leegmaken
  lcd.clear();
  lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("Distance: "); // Print string "Distance" on the LCD
  lcd.print(distanceToCm); // Print duration omgerekend in centimeter
  lcd.print(" cm"); // print sting "cm"
 
  lcd.setCursor(0,1);
  lcd.print("Duration: ");// Print string "Duration" on the LCD
  // tijd dat geluid nodig heeft om uit te sturen, te botsen en terug te keren printen
  lcd.print(duration);
  //delay(10);
   
//  Serial.print(duration);
//  Serial.println("duration");

  graden = map(distanceToCm, 0, 50, 0, 180);
  if (graden > 180) {
    graden = 180;
  }

  Serial.print(distanceToCm);
  Serial.println(" cm");

  Serial.print(graden);
  Serial.println(" graden");

  currentGraden += (graden - currentGraden) * 0.1;
  
   myservo.write(currentGraden);
   delay(10);
}
