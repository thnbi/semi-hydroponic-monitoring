#include <ArduinoWebsockets.h> //biblioteca web sockets
#include <heltec.h> //biblioteca heltec
#include <WiFi.h> //biblioteca wifi
#include <DHT.h>
#include <heltec.h>

const char* ssid = ""; //ssi
const char* password = ""; //senha
const char* websockets_server_host = ""; //ip do servidor
const uint16_t websockets_server_port = 8080; //porta do servidor para a conexão
int status = WL_IDLE_STATUS;                     //status wifi

//esp32 estados
#define loraEstado false
#define displayEstado true
#define serialEstado true
#define PABOOSTEstado false
#define bandaDeTransmicao 433E3

using namespace websockets; //criando namespace para poder usar a classe WebsocketsClient

WebsocketsClient client; //objeto cliente

WiFiServer servidor(80);


//temperatura e umidade
float hum;  
float temp; 

//definindo dht
#define DHTPIN 23
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE); 



void setupWiFi(){
  Heltec.display->clear();
  //desconecta de uma possível conexão prévia.
  WiFi.disconnect(true);
  delay(100);
  
  //aqui vou criar uma rede:
 IPAddress ip(255, 255, 0, 0); //define um ip fixo 
  IPAddress gateway(191, 36, 11, 254 ); //gateway de rede
  IPAddress subnet(255, 255, 254, 0); //máscara de rede
  
  WiFi.mode(WIFI_STA); //ajusta o wifi para modo station
  WiFi.setAutoConnect(true); //ativa auto conexão
  WiFi.config(ip, gateway, subnet); //configura os endereços
  WiFi.begin(ssid, password); //informa o id e a senha do WiFi
  
  
  delay(100);
  
  byte count = 0; 


while(WiFi.status() != WL_CONNECTED && count<10){
    count++;
    delay(500);
  
    Heltec.display->drawString(0, 0, "Conectando WiFi...");
    Heltec.display-> display();
  }
  
  if(WiFi.status() == WL_CONNECTED){ //se conecta
    Heltec.display->clear();
    Heltec.display->drawString(0, 10, "WiFi conectada");
    Heltec.display-> display();
    
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    delay(100);

  }else{
    Heltec.display->drawString(0, 10, "Falha na conexão WiFi");
    Heltec.display->drawString(0, 25, "Senha ou ssid");
    Heltec.display->drawString(0, 35, "possívelmente incorreta");
    Heltec.display-> display();
    delay(5000);
    ESP.restart();
  }
  

}

void trataPacotes(){
  WiFiClient cliente = servidor.available(); 
  
  if(!cliente)return;
    Heltec.display->clear();
    Heltec.display->drawString(0, 0, "Servidor: " + WiFi.localIP().toString());
    Heltec.display->drawString(0, 10, "Cliente conectado");
    Heltec.display->display();
    
    while(cliente.connected()){ //executa enquanto houver conexão
      if(cliente.available()){
        //a partir daqui trabalho com  o cliente
      
      String(frontEnd) = 
      "<html>"
      "<h1>hello world!</h1>"
      "</html>";
      
      //escreve o html que será enviado para o cliente
      cliente.print(frontEnd);
      cliente.flush(); //envia os dados do buffer para o cliente
      }
      //aguarda para que o tráfego seja concluído
      delay(20);
      cliente.stop(); //força desconexão do cliente
    }

    Heltec.display->clear();
    Heltec.display->drawString(0, 0, "Servidor em:");
    Heltec.display->drawString(0, 10, WiFi.localIP().toString());
    Heltec.display->display();
}

void temperatureHumidity(){
  
    delay(3000);
    
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    
    if (isnan(hum) || isnan(temp)) {
      Serial.println("temp and hum is NaN!");
      dht.begin();
      
    }

    Serial.print("Humidade: ");
    Serial.print(hum);
    Serial.println("%");
    Serial.print("Temperatura: ");
    Serial.print(temp);
    Serial.println("ºC");
    
    Heltec.display->clear();
    Heltec.display->drawString(33, 30, (String)temp);
    Heltec.display->drawString(60, 30, "°C");
    Heltec.display->display();
      
}

void setup() {
  
  Serial.begin(9600);
  Heltec.begin(displayEstado, loraEstado, serialEstado, PABOOSTEstado, bandaDeTransmicao);
  Heltec.display->init();
  

  setupWiFi();  
}

void loop() {
  temperatureHumidity();
  trataPacotes();
  
}
