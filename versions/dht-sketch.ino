#include <DHT.h>
#include <heltec.h>

#define DHTPIN 23
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Variables
float hum;  // Stores humidity value
float temp; // Stores temperature value

void temperatureHumidity()
{
 delay(3000);

 // Read data and store it to variables hum and temp
 hum = dht.readHumidity();
 temp = dht.readTemperature();

 if (isnan(hum) || isnan(temp))
 {
  Serial.println("temp and hum is NaN!");
  dht.begin();
 }
 // Print temp and humidity values to serial monitor
 Serial.print("Humidade: ");
 Serial.print(hum);
 Serial.println("%");
 Serial.print("Temperatura: ");
 Serial.print(temp);
 Serial.println("ºC");
}

void setup()
{
 Serial.begin(9600);
 Heltec.begin(true /*Habilita o Display*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Habilita debug Serial*/, true /*Habilita o PABOOST*/);

 Heltec.display->init();
 Heltec.display->flipScreenVertically();
 Heltec.display->setFont(ArialMT_Plain_16);
 Heltec.display->clear();
 Heltec.display->drawString(33, 5, "Iniciado");
 Heltec.display->drawString(10, 30, "com Sucesso!");
 Heltec.display->display();

 delay(1000);
 dht.begin();
}

void loop()
{
 temperatureHumidity();

 Heltec.display->clear();
 Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
 Heltec.display->setFont(ArialMT_Plain_10);
 Heltec.display->drawString(33, 5, (String)hum);
 Heltec.display->drawString(60, 5, "%");
 Heltec.display->drawString(33, 30, (String)temp);
 Heltec.display->drawString(60, 30, "°C");
 Heltec.display->display();
}
