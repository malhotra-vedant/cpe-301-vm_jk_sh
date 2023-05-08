// NOTE - THIS IS ONLY TESTING CODE

#include <LiquidCrystal.h>

const int rs = A3, en = A5, d4 = A9, d5 = A10, d6 = A11, d7 = A12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(A14,OUTPUT);
  pinMode(A13,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A1,OUTPUT); 
  digitalWrite(A14,LOW); 
  digitalWrite(A13,HIGH); 
  digitalWrite(A4,LOW); 
  digitalWrite(A0,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(A1,HIGH);
   
  lcd.begin(16, 2);
  // Test the LCD 
  lcd.print("Test");
}

void loop() {
  lcd.setCursor(0, 1);
  // number of seconds since last reset
  lcd.print(millis() / 1000);
  analogWrite(13, 0);
}