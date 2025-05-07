#ifndef Arduino
#define Arduino
#include <Arduino.h>
#endif

#ifndef webserverBike
#define webserverBike

// invia il file html
void sendHtml();

// prepara il webserver all'indirizzo watermike.local
void setupWebServer();

// gestisce i client
void handleWebserver();

#endif