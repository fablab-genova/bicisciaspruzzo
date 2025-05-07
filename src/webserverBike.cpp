#include "webserverBike.h"
#include "htmlVars.h"
#include <WebServer.h>     // Libreria per il server web
#include <uri/UriBraces.h> // Libreria per la gestione degli URI dinamici
#include <ESPmDNS.h>       //libreria Multicast DNS, per usare un nome umano per la landing
// Creazione del server web sulla porta 80
WebServer server(80);

void handleSaveGrid()
{
  Serial.println("== saveGrid==");
  if (server.hasArg("data"))
  {
    String hex = server.arg("data");
    Serial.println("== hex ==: " + hex);
    byte grigliatmp[32];
    for (int i = 0; i < 32 && i * 2 + 1 < hex.length(); i++)
    {
      String byteStr = hex.substring(i * 2, i * 2 + 2);
      byte colVal = strtoul(byteStr.c_str(), NULL, 16);
      grigliatmp[i] = colVal; // griglia è un array di 8 byte
    }
    memcpy(griglia1, grigliatmp, 8);
    memcpy(griglia2, grigliatmp + 8, 8);
    memcpy(griglia3, grigliatmp + 16, 8);
    memcpy(griglia4, grigliatmp + 24, 8);
  }
  server.sendHeader("Location", "/");
  server.send(303); // 303 = "See Other" (standard per redirect dopo form GET)
}
void handleARM()
{
  Serial.println("== handleARM==");
  if (server.hasArg("ARM"))
  {
    String armamento = server.arg("ARM");
    if (armamento == "TRUE")
    {
      webFlag = false;
    }
    else
    {
      // Reindirizzamento alla homepage
      server.sendHeader("Location", "/");
      server.send(303); // 303 = "See Other" (standard per redirect dopo form GET)
    }
  }
}

void handleIndex()
{
  if (server.hasArg("text"))
    messaggio = server.arg("text");
  if (server.hasArg("time"))
    tempo_ms = server.arg("time").toInt();
  if (server.hasArg("decor"))
    decor = server.arg("decor").toInt();
  if (server.hasArg("flag"))
    InterruptEn = server.hasArg("flag");
  Serial.println("==Index Dati ricevuti ==");
  Serial.println("Testo: " + messaggio);
  Serial.println("Numero: " + String(tempo_ms));
  Serial.println("decori: " + String(decor));
  Serial.println("InterruptEn: " + InterruptEn ? "ON" : "OFF");
  createIndexHtml();
  server.send(200, "text/html", indexHtml);
}
void handleGrid()
{
  server.send(200, "text/html", gridHtml);
}
void handleWebserver()
{
  server.handleClient();
}
void setupWebServer()
{
  // Definisce la route per la pagina principale
  server.on("/", handleIndex);          
  server.on("/saveGrid", handleSaveGrid); 
  server.on("/griglia", handleGrid);
  server.on("/ARM", handleARM);

  server.begin();
  Serial.println("Server HTTP avviato");
  // attivo il mdns per rispondere con un hostname (nome umano)
  createIndexHtml();
  creategridHtml();
  if (MDNS.begin("waterMike"))
  { // hostname watermike.local
    Serial.println("mDNS avviato: puoi usare http://waterMike.local");
  }
  else
  {
    Serial.println("Errore nell'avvio di mDNS");
  }
}
// Funzione per inviare la pagina HTML al client
