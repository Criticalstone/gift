/* Simple USB Keyboard Example
   Teensy becomes a USB keyboard and types characters

   You must select Keyboard from the "Tools > USB Type" menu

   This example code is in the public domain.
*/
#define SIZE 5
#include <Bounce.h>

int count = 0;
int buttonPin = 5;
int buttonvoltPin = 4;


Bounce bouncer = Bounce(buttonPin, 5); 
String texts[SIZE] = {"Merry Christmas shenmue151!",
                   "This little box is full of happiness.", 
                   "Even though it only has one button",
                   "...",
                   "(Don't tell him that, he may get upset)",
                   "Source code can be found on github.com/criticalstone/"};

int printDelays[SIZE] = {10,10,10,500,0};

int delays[SIZE] = {0,300, 0, 400,0};

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  pinMode(buttonPin, INPUT);
  pinMode(buttonvoltPin, OUTPUT);
}

void loop() {
  digitalWrite(buttonvoltPin, HIGH);
  
  /*printDel("Press the button to continue, current document will be deleted", 10);
  printDel("....", 500);
  Keyboard.println();
  */
  for(int i = 0; i < SIZE; i++) {
    printDel(texts[i], printDelays[i]);
    Keyboard.println();
    delay(delays[i]);
  }

  waitHold(buttonPin, 1000);
  
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
