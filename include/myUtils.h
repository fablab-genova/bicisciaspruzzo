#ifndef Arduino
#define Arduino
#include <Arduino.h>
#endif
#ifndef MY_UTILS_H
#define MY_UTILS_H

// gestisco la board

//

////////IN/OUT
#define LED0 4
#define LED1 18
#define LED2 19
#define LED3 5
// cavi raggruppati in gruppi da 4
#define LED4 14
#define LED5 26
#define LED6 25
#define LED7 27

#define ARM 13 // interruttore per passare tra la funzione webserver e quella bike (watermike vs waterbike)

#define LED_C 21   // led che mi dice che è pronto a scaricare acqua//
#define FIRE 22    // tasto per scaricare l'acqua
#define Magneto 32 // sensore spazio/velocita probabilmente magnetico
#define Magneto_push 23

void ACwireSetup();

#endif