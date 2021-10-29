#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

#define buttonA 13
#define buttonALight 12
#define buttonB 11
#define buttonBLight 10
#define buzz 9

int countRed = 0;
int countBlue = 0;
bool buttonClickedA = false;
bool buttonClickedB = false;
int timeRed = 0;
int timeBlue = 0;

void setup()  {
  pinMode(buzz, OUTPUT);
  digitalWrite(buzz, LOW);
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonBLight, OUTPUT);
  digitalWrite(buttonBLight, LOW);
  pinMode(buttonALight, OUTPUT);
  digitalWrite(buttonALight, LOW);
  Serial.begin(9600);
  Serial.println("Serial On");
  #ifndef __AVR_ATtiny85__
  //delete afterwards
  #endif
  matrix.begin(0x70);
}

void loop() {
  if (countRed < 99 && countBlue < 99) {
    checkButton();
    showScore(countBlue, countRed);
    digitalWrite(buzz, LOW);
  } else {
    digitalWrite(buzz, HIGH);
  }
}

void checkButton() {
  int aVal = digitalRead(buttonA);
    Serial.println(aVal);
  if (aVal == LOW && buttonClickedA == false && millis() - timeRed > 300) {
    digitalWrite(buttonALight, HIGH);
    countRed = countRed + 1;
    buttonClickedA = true;
    timeRed = millis();
    //Serial.println(countRed);
  } else if (aVal == HIGH && buttonClickedA == true) {
    buttonClickedA = false;
    digitalWrite(buttonALight, LOW);
  }
  
  int bVal = digitalRead(buttonB);
    Serial.println(bVal);
  if (bVal == LOW && buttonClickedB == false && millis() - timeBlue > 300) {
    digitalWrite(buttonBLight, HIGH);
    countBlue = countBlue + 1;
    buttonClickedB = true;
    timeBlue = millis();
    //Serial.println(countRed);
  } else if (bVal == HIGH && buttonClickedB == true) {
    buttonClickedB = false;
    digitalWrite(buttonBLight, LOW);
  }
}

void showScore(int countBlue, int countRed) {
  bool drawDots = false;
  bool drawColon = true;
  matrix.writeDigitNum(0, (countRed / 10) % 10, drawDots);
  matrix.writeDigitNum(1, countRed % 10, drawDots);
  matrix.drawColon(drawColon);
  matrix.writeDigitNum(3, (countBlue / 10) % 10, drawDots);
  matrix.writeDigitNum(4, countBlue % 10, drawDots);
  matrix.writeDisplay();
}
