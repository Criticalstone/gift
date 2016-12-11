/* Simple USB Keyboard Example
   Teensy becomes a USB keyboard and types characters

   You must select Keyboard from the "Tools > USB Type" menu

   This example code is in the public domain.
*/
#define SIZE 15
#include <Bounce.h>

int count = 0;
int buttonPin = 5;
int buttonvoltPin = 4;

const int first = 13;
const String NAME = "shenmue151";

Bounce bouncer = Bounce(buttonPin, 5); 
String texts[SIZE] = {"Merry Christmas " + NAME + "!",
                      "I am the little box of love, ", 
                      "I only have one button, but that will not stop me!",
                      "well, well",
                      "The question is, what is my purpose?",
                      "I am just a box, what can I do to make the world a better place?",
                      "I know! I can travel the world and spread my deep deep looove!", 
                      "The box itself is pretty robust and would probably be able to handle the stress very well",
                      "We have one problem though", 
                      "I can light, I can talk, I can think (I believe) and I do not need to breathe.",
                      "But I can not move the tiniest bit by myself",
                      "Would you pleease help me? :) :) :) :) :)",
                      "Press me!",

                      "Source code can be found on github.com/criticalstone/gift",
                      "Don't forget to tell my creator where I am by sending an email to Criticalstone. You can find his email on github."
                      };

int printDelays[SIZE] = {10, 10, 10, 30, 10, 10, 10, 10, 30, 10, 10, 5, 10, 50};

int delays[SIZE] = {300, 300, 1000, 1000, 300, 1000, 300, 300, 1000, 500, 0, 300, 0, 0};

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  pinMode(buttonPin, INPUT);
  pinMode(buttonvoltPin, OUTPUT);
}

void loop() {
  digitalWrite(buttonvoltPin, HIGH);
  
  waitClick(buttonPin);
  
  for(int i = 0; i < first; i++) {
    printDel(texts[i], printDelays[i]);
    Keyboard.println();
    delay(6*delays[i]);
  }

  waitHold(buttonPin, 1000);

  printDel(texts[first + 1], 10);
  
}

void printDel(String string, int del) {
  for (int i = 0; i < string.length(); i++) {
    Keyboard.print(string[i]);
    delay(del);
  }
}

void deleteRows(int num) {
  Keyboard.set_modifier(MODIFIERKEY_SHIFT);
  Keyboard.set_key2(KEY_HOME);
  for (int i = 1; i < num; i++) {
    Keyboard.set_key1(KEY_UP);
    Keyboard.send_now();
    Keyboard.set_key1(0);
    Keyboard.send_now(); 
    
  }
  Keyboard.set_key1(KEY_DELETE);
  Keyboard.send_now();
  resetKeyboard();
  resetMod();
}

void resetKeyboard() {
  Keyboard.set_key1(0);
  Keyboard.set_key2(0);
  Keyboard.set_key3(0);
  Keyboard.set_key4(0);
  Keyboard.set_key5(0);
  Keyboard.set_key6(0);
  Keyboard.send_now();
}

void resetMod() {
  Keyboard.set_modifier(0);
  Keyboard.send_now();
}

void waitHold(int pin, int timem) {
  int before = 0, after = 0;
  while (after - before < timem) {
    bouncer.update();
    while (bouncer.read() == LOW) {
      bouncer.update();
    }
    before = millis();
    while (bouncer.read() == HIGH) {
      bouncer.update();
    }
    after = millis();
    deleteRows(1);
    Keyboard.println(after-before);
  }
}

void waitClick(int pin){
  bouncer.update();
  while (bouncer.read() == LOW) {
    bouncer.update();
  }
  while (bouncer.read() == HIGH) {
    bouncer.update();
  }
  /*int reading = 0;
  while (reading == LOW){
    reading = digitalRead(buttonPin);
  }
  delay(50);
  while (reading == HIGH){
    reading = digitalRead(buttonPin);
  }*/
}
