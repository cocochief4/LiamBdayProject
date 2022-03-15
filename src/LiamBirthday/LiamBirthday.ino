//Add required Libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

//Rendering Matrix Display
Adafruit_7segment matrix = Adafruit_7segment();

#define buttonA 7
#define buttonALight 6
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
  //Initialize pins and serial communication.
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
  #endif
  matrix.begin(0x70); //Sets the clock rate (bits per sec)
}

//Loop to check if one of the teams has won.
void loop() {
  if (countRed < 99 && countBlue < 99) {
    checkButton();
    showScore(countBlue, countRed);
    digitalWrite(buzz, LOW);
  } else {
    digitalWrite(buzz, HIGH);
  }
}

//Checks if the buttons for the teams has been presed, if they have, add a point to the respective team and start a timer that counts until they can press the button again.
// This makes sure the games to not end really quickly. Sometimes, the delay does not work.
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

//Shows the score using Adafruit 7-segment display backpack library. Here is the link for more information: https://learn.adafruit.com/adafruit-led-backpack/0-dot-56-seven-segment-backpack-arduino-setup
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
