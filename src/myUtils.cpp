
#include "myUtils.h"

void ACwireSetup()
{
    Serial.begin(115200);                // Inizializza la comunicazione seriale
    pinMode(LED0, OUTPUT);               // porta 3 gpio:36
    pinMode(LED1, OUTPUT);               // porta 3 gpio:36
    pinMode(LED2, OUTPUT);               // porta 4 gpio:39
    pinMode(LED3, OUTPUT);               // porta 5 gpio:34
    pinMode(LED4, OUTPUT);               // porta 6 gpio:35
    pinMode(LED5, OUTPUT);               // porta 8 gpio:33
    pinMode(LED6, OUTPUT);               // porta 9 gpio:25
    pinMode(LED7, OUTPUT);               // porta 10 gpio:26
    pinMode(LED_C, OUTPUT);              // porta 27 gpio:16
    pinMode(FIRE, INPUT_PULLUP);         // porta 29 gpio:5
    pinMode(ARM, INPUT_PULLUP);          // porta 36 gpio:22
    pinMode(Magneto, INPUT);             // porta 23 gpio:15
    pinMode(Magneto_push, INPUT_PULLUP); // porta 23 gpio:15

    digitalWrite(LED0, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);
    digitalWrite(LED7, LOW);
}