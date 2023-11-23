#include <TinyGPS.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(4,6,7,8,9,10);
const int trig = 3;
const int echo = 2;
TinyGPS gps; 
void setup()
{
  Serial.begin(9600);  
  lcd.begin(16,2);
  lcd.setCursor(0, 0);
  lcd.print("TINH TRANG:");
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  unsigned long duration;
  int distance;
  digitalWrite(trig, 0);
  delayMicroseconds(2);
  digitalWrite(trig, 1);
  delayMicroseconds(5);
  digitalWrite(trig, 0);
  duration = pulseIn(echo, HIGH);
  distance = int(duration / 2 / 29.412);
  int val= map(distance,0,1106,100,0); 
  lcd.setCursor(12, 0);
  lcd.print(val);
  lcd.print("% ");
  if(val<=30)
  {
    lcd.setCursor(0, 1);
    lcd.print("NAP NHIEN LIEU");
    while (Serial.available())
    {
      char c = Serial.read();
      Serial.print(c);
      if (gps.encode(c)) 
        newData = true;  
    }
  if (newData) 
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);   
    Serial.print("Latitude = ");
    Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" Longitude = ");
    Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
  }
 }
 else
  {
    lcd.setCursor(0, 1);
    lcd.print("NHIEN LIEU CON");
  }
  }