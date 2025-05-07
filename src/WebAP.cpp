#include "WebAP.h"
#include <WiFi.h> // Libreria per la gestione del WiFi

void wifiSetup()
{
  // Imposta l'ESP32 in modalità Access Point
  WiFi.mode(WIFI_AP);
  // Avvia l'Access Point con SSID "ESP32-AP" e nessuna password
  WiFi.softAP("waterMike"); // WiFi.softAP("ESP32-AP", "tua_password");->per aggiungere la password

  // Stampa l'indirizzo IP dell'Access Point
  Serial.print("Access Point avviato. Indirizzo IP: ");
  Serial.println(WiFi.softAPIP());
}