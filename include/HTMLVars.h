#ifndef Arduino
#define Arduino
#include <Arduino.h>
#endif

#ifndef HTML_VAR
#define HTML_VAR
// per non dichiararlo due volte in giro
extern String messaggio; // la stringa da stampare
extern int tempo_ms;     // il tempo tra una colonna e l'altra
extern bool webFlag;     // decide tra web server e pronto a spruzzare
extern bool InterruptEn; // modalita magneti o modalità a tempo
extern String indexHtml; // lo uso per creare la pagina index aggiornata
extern String gridHtml;  // lo uso per creare la pagina grid aggiornata
extern String StyleHtml; // lo uso per usare lo style in tutte le pagine
extern byte griglia1[8]; // decoro 1
extern byte griglia2[8]; // decoro 2
extern byte griglia3[8]; // decoro 3
extern byte griglia4[8]; // decoro 4
extern int decor;        // mi dice se voglio stampare solo decori (-1),solo scritta(0), o scritta e decori (1)

void createIndexHtml(); // aggiorna index con i nuovi valori delle variabili
void creategridHtml();  // aggiorna grid con i nuovi valori delle variabili
#endif