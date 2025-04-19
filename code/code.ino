#include <WiFi.h>
#include <WiFiAP.h>
#include "SPIFFS.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>

/* These are the access point credentials.
  To get an open AP set APPASSWORD as an empty string.
*/
#define APSSID "BICISCIASPRUZZO"
#define APPASSWORD ""

/* The port of the web server */
#define WEBPORT 80

/* 
In the early stage of development we are gonna use the built in led and button
*/
#ifndef LED_BUILTIN
#define LED_BUILTIN 2  // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED
#endif
#define BOOT_BUTTON 0  // GPIO0 We use it for debugging in the early stage of development

const char *ssid = APSSID;
const char *password = APPASSWORD;
int clickCounter = 0;

AsyncWebServer server(WEBPORT);
AsyncWebSocket ws("/ws");

void setup() {
    pinMode(BOOT_BUTTON, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);

    Serial.println("Configuring file system...");
    if(!SPIFFS.begin(true)){
        Serial.println("Mounting SPIFFS failed");
        return;
    }
    Serial.println("SPIFFS mount succeded");

    Serial.println("Listing files:");
    File root = SPIFFS.open("/");
    while (File file = root.openNextFile()) {
        Serial.println(file.name());
    }

    Serial.println("Configuring access point...");
    if (!WiFi.softAP(ssid, password)) {
        Serial.println("Soft AP creation failed.");
        while (1); // hang here forever
    }
    Serial.println("AP configured sucessfully");
    printMyIP();
    IPAddress myIP = WiFi.softAPIP();

    ws.onEvent(onWebSocketEvent);
    server.addHandler(&ws);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Client requested: /");
        logRequest(request);


    // Print client IP
    Serial.print("Client IP: ");
    Serial.println(request->client()->remoteIP());

    // Print headers (optional)
    int headers = request->headers();
    for (int i = 0; i < headers; i++) {
        AsyncWebHeader* h = request->getHeader(i);
        Serial.printf("Header: %s = %s\n", h->name().c_str(), h->value().c_str());
    }

    if (request->hasParam("name")) {
        String name = request->getParam("name")->value();
        Serial.print("Received name: ");
        Serial.println(name);
    }

    request->send(SPIFFS, "/index.html", "text/html");
    });

    server.onNotFound([](AsyncWebServerRequest *request){
    Serial.print("Unhandled request: ");
    Serial.println(request->url());
        logRequest(request);


    request->send(SPIFFS, "/index.html", "text/html");  // Captive behavior
    });

    server.begin();
    Serial.println("Server started");
}

void loop() {
    checkForPressedButton();
}

void checkForPressedButton(){
    if (digitalRead(BOOT_BUTTON) == LOW) {
        Serial.println("BOOT button pressed!");
        printMyIP();
        clickCounter++;
        String msg = "counter:" + String(clickCounter);
        ws.textAll(msg);
    delay(400);
    }
}

void printMyIP() {
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
}

void logRequest(AsyncWebServerRequest *request) {
  Serial.printf("➡️ %s %s from %s\n", 
    request->methodToString(), 
    request->url().c_str(),
    request->client()->remoteIP().toString().c_str()
  );
}

void onWebSocketEvent(
    AsyncWebSocket *server,
    AsyncWebSocketClient *client,
    AwsEventType type,
    void *arg,
    uint8_t *data,
    size_t len
  ) {
  if (type == WS_EVT_CONNECT) {
    Serial.printf("WebSocket client connected: %u\n", client->id());
  } 
  else if (type == WS_EVT_DISCONNECT) {
    Serial.printf("WebSocket client disconnected: %u\n", client->id());
  } 
  else if (type == WS_EVT_DATA) {
    // Data received from client
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len) {
      data[len] = 0;  // Null-terminate the data
      String message = (char*)data;
      Serial.printf("Received from client: %s\n", message.c_str());

      if (message == "button_click") {
        // handleClickOrButton();
        clickCounter++;
        // Send the counter back to the client
        String response = "counter:" + String(clickCounter);
        client->text(response);
      }
    }
  }
}
