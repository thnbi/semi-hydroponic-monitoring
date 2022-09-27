#include <heltec.h>

#define outPin 13
#define inPin 2
#define led 12

int val = 0;

void setup() {
  
  Heltec.begin(true /*Display*/, true /*LoRa*/, true /*Serial */, false /*LoRa don't use PABOOST*/);
  
  pinMode(outPin, OUTPUT);
  pinMode(inPin, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {

  digitalWrite(outPin, HIGH);
  val = digitalRead(inPin);
  digitalWrite(led, val);
  delay(500);

  digitalWrite(outPin, LOW);
  val = digitalRead(inPin);
  digitalWrite(led, val);
  delay(500);

}
