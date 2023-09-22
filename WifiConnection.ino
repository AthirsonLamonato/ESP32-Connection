/*
  * Link pra incluir a placa ESP32 Dev Module
  * https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
  *
*/


#include <WiFi.h>  // Inclui a biblioteca Wi-Fi para Arduino

#define WIFI_SSID "********"     // Define o nome da rede Wi-Fi (SSID)
#define WIFI_PASSWORD "********"  // Define a senha da rede Wi-Fi

int led_wifi = 2;  // Define o pino do LED que será usado para indicar o status da conexão Wi-Fi

void connectToWifi() {
  Serial.println("Conectando ao Wifi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  // Inicia a conexão passando SSID e PASSWORD

  // Aguarda a conexão com a rede
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println("Conectando…");
  }

  Serial.println(WiFi.localIP());  // IP local atribuído ao dispositivo
}

void verifyWifi() {

  // Verifica se o dispositivo está conectado à rede Wi-Fi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Tentando conectar");  // Não conectado => Define o LED como LOW (apagado)
    digitalWrite(led_wifi, LOW);
  } else {
    digitalWrite(led_wifi, HIGH);  // Conectado => define o LED como HIGH (aceso)
  }
}

void setup() {
  pinMode(led_wifi, OUTPUT);  // Configura o pino do LED como saída
  Serial.begin(115200);       // Inicia a comunicação serial a uma taxa de 115200 bps (bits por segundo)
  connectToWifi();            // Chama a função para conectar-se à rede Wi-Fi no início do programa
}

void loop() {
  verifyWifi();  // Verifica o status da conexão Wi-Fi em loop
}
