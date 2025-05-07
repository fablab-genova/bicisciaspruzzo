#ifndef Arduino
#define Arduino
#include <Arduino.h>
#endif
#ifndef BIKE_UTILS_H
#define BIKE_UTILS_H
// chiude tutte le valvole
void closeAll();

// stampa sulla seriale il carattere
void printCharacters(byte msgCode[], int dimensioneMsg);

// aggiunge una colonna (istante, lo stato delle 8 valvole espresse come byte)
void addColumn(byte x, byte msgCode[]);

// aggiunge un carattere (8 colonne)
void addChar(String y, byte msgCode[]);

// converte la stringa in caratteri (array di byte)
void convertText(String messaggio, byte msgCode[]);

// parte a sganciare il messaggio
void fire(byte msgCode[], int posizione);

// crea un messaggio utilizzando solo i 4 colori
void onlyDecor(byte griglia1[], byte griglia2[], byte griglia3[], byte griglia4[], byte msgCode[]);

// aggiunge i decori al testo, due prima e due dopo
void convertTextandDecor(String messaggio, byte griglia1[], byte griglia2[], byte griglia3[], byte griglia4[], byte msgCode[]);
#endif