#include "heltec.h"
#include "DHT.h"

// leds
#define LED1 13
#define LED2 12

// dht sensor
#define DHTPIN 17
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define OLED 1

// variables
float hum;  //Stores humidity value
float temp; //Stores temperature value

void temperatureHumidity() {
  delay(3000);

  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  if (isnan(hum) || isnan(temp)) {
    Serial.println("temp and hum is NaN!");
    dht.begin();

  }
  //Print temp and humidity values to serial monitor
  Serial.print("Humidade: ");
  Serial.print(hum);
  Serial.println("%");
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.println("ºC");

}

void setup() {
#ifdef OLED
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, false /*PABOOST Enable*/);
#endif
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(DHTPIN, INPUT);

  Serial.begin(9600);

#ifdef OLED
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->clear();
  Heltec.display->drawString(33, 5, "Iniciado");
  Heltec.display->drawString(10, 30, "com Sucesso!");
  Heltec.display->display();
#endif

  delay(1000);
  dht.begin();
}

void loop() {

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(200);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(200);

  temperatureHumidity();

#ifdef OLED
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(33, 5, (String)hum);
  Heltec.display->drawString(60, 5, "%");
  Heltec.display->drawString(33, 30, (String)temp);
  Heltec.display->drawString(60, 30, "°C");
  Heltec.display->display();
#endif
}
