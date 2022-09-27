#include <WiFi.h>
#include <heltec.h>

#define waitSerial 1

char* ssid = "Hidroponia";
char* pass = "abcd1234";

WiFiClient client();

void wifiSetup() {
  Heltec.display -> clear();

  //desconecta de conexao previa
  WiFi.disconnect(true);
  delay(100);

  WiFi.setAutoConnect(true);
  WiFi.begin(ssid, pass);
  delay(100);
  int count = 0;

  while (WiFi.status() != WL_CONNECTED && count < 10) {
    count += 1;
    Serial.print("tentando se conectar ");
    Serial.println(ssid);
    Heltec.display -> drawString(0, 0, "tentando se conectar...");
    Heltec.display -> display();
    delay(500);
  }
  Heltec.display -> clear();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Falha ao conectar ao WiFi");

    Heltec.display -> clear();
    Heltec.display -> drawString(0, 0, "Falha ao conectar.");
    Heltec.display -> display();

  } else {
    Serial.println("Conectado ao Wifi");
    
    Heltec.display -> clear();
    Heltec.display -> drawString(0, 0, "Conectado ao WiFi");
    Heltec.display -> display();
    
    delay(500);
    
    Serial.print("Endereço Ip: ");
    Serial.println(WiFi.localIP());
  }
}

void setup() {

  Heltec.begin(true /*Display*/, false /*LoRa Disable*/, true /*Serial Enable*/, false /*LoRa don't use PABOOST*/);
  Serial.begin(9600);
  
  #ifdef waitSerial 
  delay(5000);
  #endif
  
  wifiSetup();
  
}

void loop() {

}
