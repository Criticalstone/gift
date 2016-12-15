#define SIZE 20
#include <Bounce.h>

int ledPin = 12;
int buttonPin = 5;
int buttonvoltPin = 4;

int brightness = 0;
int fadeAmount = 1;

long lastTime = millis();
long currentTime = millis();

const int first = 13;
const String NAME = "shenmue151";

Bounce bouncer = Bounce(buttonPin, 5); 
String texts[SIZE] = {"Merry Christmas " + NAME + "!",
                      "I am the little christmas box, ", 
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
                      "Press me to accept!",

                      "Yay! Thank you!", 
                      "All you have to do now is to either keep me for a while and make some cool modifications to me", 
                      "(but keep my core functionality!) and then send me away to the next receiver.",
                      "If you can't find someone to send it to, ",
                      "either wait for next secret santa or send it back to my creator in Sweden",
                      "Source code can be found on github.com/criticalstone/gift",
                      "Don't forget to tell my creator where I am by sending an email to Criticalstone. You can find his email on github."
                      };

int printDelays[SIZE] = {10, 10, 10, 30, 10, 10, 10, 10, 30, 10, 10, 5, 10 ,10, 10, 10, 10, 10, 10, 50};

int delays[SIZE] = {300, 300, 1000, 1000, 300, 1000, 300, 300, 1000, 500, 0, 300, 0, 300, 0, 3000, 0, 2000, 1000, 1000};

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  pinMode(buttonPin, INPUT);
  pinMode(buttonvoltPin, OUTPUT);
}

void loop() {
  resetKeyboard();
  resetMod();
  digitalWrite(buttonvoltPin, HIGH);                    
  
  waitClick(buttonPin);
  
  for(int i = 0; i < first; i++) {
    printDel(texts[i], printDelays[i]);
    Keyboard.println();
    delay(6*delays[i]);
  }

  waitClick(buttonPin);

  for(int i = first; i < SIZE; i++) {
    printDel(texts[i], printDelays[i]);
    Keyboard.println();
    delay(6*delays[i]);
  }  
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
    updateLed();
  }
  while (bouncer.read() == HIGH) {
    bouncer.update();
    updateLed();
  }
}

void updateLed() {
  currentTime = millis();
  if (currentTime - lastTime > 5) {
    analogWrite(ledPin, brightness);
    brightness = brightness + fadeAmount;
    if (brightness >= 255 || brightness <= 0) {
      fadeAmount = -fadeAmount;
    }
    lastTime = currentTime;
  }
}

