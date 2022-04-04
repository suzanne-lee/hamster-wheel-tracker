#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

int ledPin = 13;
int hallSensorPin = 3;
int prevState = 0;
int currState = 0;
int revolutions = 0;
float distance = 0;
float circumference = 67.544;
unsigned long prevRevTime = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(ledPin, OUTPUT);
  pinMode(hallSensorPin, INPUT);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Revs:");
  lcd.print(revolutions);
}

void loop() {
  prevState = currState;
  currState = digitalRead(hallSensorPin);

  if (prevState == HIGH && currState == LOW) {
    revolutions = revolutions + 1;
    distance = distance + circumference;
    unsigned long currRevTime = millis();
    float deltaTime = currRevTime - prevRevTime;
    // deltaTime in seconds
    deltaTime = deltaTime / 1000.0;

    // m per second
    float speed = circumference / 100 / deltaTime; 
    prevRevTime = currRevTime;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Revs:");
    lcd.print(revolutions);
    lcd.print(" S:");
    lcd.print(speed);
    lcd.setCursor(0,1);
    lcd.print("Dist:");
    lcd.print(distance/100);
    lcd.print("m");
  }

  if (currState == LOW) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
