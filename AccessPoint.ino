#include <WiFi.h>
#include "esp_wifi.h"

const char* ssid           = "ESP_Teste";                // Nome do SSID
const char* password       = "teste12345";               // Senha do SSID -> null = sem senha
const int   channel        = 1;                         // WiFi Channel -> entre 1 e 13
const bool  hide_SSID      = false;                     // Se true, SSID não irá aparecer em scan básico de WiFi
const int   max_connection = ESP_WIFI_MAX_CONN_NUM;     // Número máximo de clientes conectados (15)

void setup()
{
    Serial.begin(115200); // velocidade da serial
    Serial.println("----- CRIANDO AP");
    WiFi.onEvent(WiFiEvent); //método que monitora os eventos do WiFi
    WiFi.mode(WIFI_AP); //seta o modo do WiFi para AP
    WiFi.softAP(ssid, password, channel, hide_SSID, max_connection); // configura o AP
    WiFi.enableAP(true); //ativa o AP
    Serial.print("----- AP criado com o IP de gateway ");
    Serial.println(WiFi.softAPIP());
}

void loop(){
  display_connected_devices();
  delay(1000);
}

// método para mostrar os dispositivos conectados (MAC e IP)
void display_connected_devices()
{
    wifi_sta_list_t wifi_sta_list;
    tcpip_adapter_sta_list_t adapter_sta_list;
    esp_wifi_ap_get_sta_list(&wifi_sta_list);
    tcpip_adapter_get_sta_list(&wifi_sta_list, &adapter_sta_list);

    if (adapter_sta_list.num > 0)
        Serial.println("----------- -----------");
    for (uint8_t i = 0; i < adapter_sta_list.num; i++) {
        tcpip_adapter_sta_info_t station = adapter_sta_list.sta[i];
        Serial.print((String)"Dispositivo " + i + " | MAC : ");
        Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X", station.mac[0], station.mac[1], station.mac[2], station.mac[3], station.mac[4], station.mac[5]);
        char str_ip[16];
        esp_ip4addr_ntoa(&(station.ip), str_ip, IP4ADDR_STRLEN_MAX);
        Serial.println((String) " | IP " + str_ip);
    }
}

// método que monitora os eventos do WiFi
void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info){
    switch (event) {
        case ARDUINO_EVENT_WIFI_AP_START:
            Serial.println("--- WiFi AP iniciado");
            break;
        case ARDUINO_EVENT_WIFI_AP_STOP:
            Serial.println("--- WiFi AP parou");
            break;
        case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
            Serial.println("--- Cliente conectou");
            break;
        case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
            Serial.println("--- Cliente desconectou");
            break;
        default: break;
    }
}
