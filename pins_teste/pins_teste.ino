
#define LED22 22
#define LED2 2
#define LED17 17
#define LED32 32
#define LED33 33
#define LED25 25
#define LED12 12
#define LED13 13

void setup() {

  pinMode(LED22, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED17, OUTPUT);
  pinMode(LED32, OUTPUT);
  pinMode(LED33, OUTPUT);
  pinMode(LED25, OUTPUT);
  pinMode(LED12, OUTPUT);
  pinMode(LED13, OUTPUT);
  
}

void loop() {

  digitalWrite(LED22, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED17, HIGH);
  digitalWrite(LED32, HIGH);
  digitalWrite(LED33, HIGH);
  digitalWrite(LED25, HIGH);
  digitalWrite(LED12, HIGH);
  digitalWrite(LED13, HIGH);
  
  delay(100);
  

  digitalWrite(LED22, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED17, LOW);
  digitalWrite(LED32, LOW);
  digitalWrite(LED33, LOW);
  digitalWrite(LED25, LOW);
  digitalWrite(LED12, LOW);
  digitalWrite(LED13, LOW);
  
  delay(300);
}
