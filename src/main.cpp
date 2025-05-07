/*
  inspired on https://github.com/sagarrabanana/Bikelangelo/blob/master/bikelangeloBT.ino#L69
*/

#include "webserverBike.h" //funzioni che gestiscono il web server
#include "WebAP.h"         //funzioni che gestiscono l'access point wifi
#include "bikeUtils.h"     //funzioni che gestiscono la conversione del testo in matrici di byte e gestiscono le elettrovalvole
#include "myUtils.h"       //funzioni che gestiscono i pin, dipendono dalla esp32/arduino utilizzata todo rename
#include "htmlVars.h"      //funzioni per le variabili a supporto delle pagine web e dei parametri GET todo SPIFFS?

// per interrupt debounce (magnete rilevato o tasto magnete)
unsigned long lastInterruptTime = 0;
const unsigned long debounceDelay = 50;      // millisecondi
const unsigned long debounceDelayPush = 500; // millisecondi per il tasto

volatile byte state = LOW; // per magneto, cambia valore all'interrupt del magnete

bool needToConvert = true; // converto il primo messaggio.... questo secondo me non serve, l'abbiamo ereditato dal codice di mikelangelo e ho pauraq a rimuoverlo
void magnetPush_detect()   // funzione pulsante magneto
{
  unsigned long currentTime = millis();
  if (currentTime - lastInterruptTime > debounceDelayPush)
  {
    lastInterruptTime = currentTime;
    Serial.println("cambio stato");
    state = !state; // todo mettere a 1 da valutare la possibilità che si meglio a uno, studiare la casistica e i tempi
  }
}
void magnet_detect() // This function is called whenever a magnet is detected
{
  unsigned long currentTime = millis();
  if (currentTime - lastInterruptTime > debounceDelay)
  {
    lastInterruptTime = currentTime;
    Serial.println("cambio stato");
    state = !state; // todo mettere a 1 da valutare la possibilità che si meglio a uno, studiare la casistica e i tempi
  }
}

void setup()
{
  ACwireSetup();                                         // funzione che setta i pin nella configurazione AC
  wifiSetup();                                           // crea access point wifi
  setupWebServer();                                      // crea il webserver e lo avvia
  attachInterrupt(Magneto, magnet_detect, FALLING);      // interrupt per il magneto
  attachInterrupt(Magneto_push, magnet_detect, FALLING); // interrupt per il magneto tasto
  webFlag = true;
}

void loop()
{

  if (digitalRead(ARM) == LOW) // se tengo premuto arm salto la fase webserver
  {
    webFlag = false;
  }
  if (webFlag) // controlla se essere in modalità web server  o acqua
  {
    digitalWrite(LED_C, HIGH);
    needToConvert = true;
    handleWebserver();    // Gestisce le richieste dei client
    needToConvert = true; // chiuso il webserver ricarica tutto
    delay(200);           // Piccola pausa per evitare l'uso eccessivo della CPU
    digitalWrite(LED_C, LOW);
    delay(200);
  }
  else
  {

    messaggio.toUpperCase();
    Serial.println("siamo nel loop BIKE not Mike con il messaggio : " + messaggio + "  la decorazione num: " + decor);
    int dimensioneMsg;
    // lo switch sotto deve calcolare la dimensione dell'array msgcode in caso di delimitatori (quante colonne o byte sarà)
    switch (decor)
    {
    case -1:
      dimensioneMsg = (8 * 4); // misura delle griglie per i decori (disegni da aggiungere al testo)
      break;
    default:
      Serial.println("switch decor default");
    case 0:
      dimensioneMsg = (8 * messaggio.length()); // bikelangelo metteva + 10
      break;
    case 1:
      dimensioneMsg = (8 * messaggio.length()) + (8 * 4); // bikelangelo metteva + 10
      break;
    }

    state = LOW; // aspetto il prossimo magnete
    byte msgCode[dimensioneMsg] = {0};
    Serial.println("MsgCode creato di  colonne: " + String(sizeof(msgCode) + "MsgCode creato di  caratteri: " + String(sizeof(msgCode) / 8)));
    if (needToConvert) // lo faccio ogni volta todo da togliere? leggi dichiarazione needToConvert
    {
      needToConvert = false; // stampa solo la prima scritta todo
      switch (decor)
      {
      case -1:
        onlyDecor(griglia1, griglia2, griglia3, griglia4, msgCode);
        break;
      default:
      case 0:
        convertText(messaggio, msgCode); // ci sarebbe il discorso spazi aggiunti alla fine
        break;
      case 1:
        Serial.println("MsgCode creato di  grandezza: ---->>" + String(sizeof(msgCode)));
        convertTextandDecor(messaggio, griglia1, griglia2, griglia3, griglia4, msgCode); // scusate i mille parametri(non voglio importare htmlvar in bikeutils)
        // printCharacters(msgCode);
        break;
      }
    }

    Serial.println("PRONTO A STAMPARE!!!!"); // aspetto il via con il tasto fire

    digitalWrite(LED_C, HIGH);
    bool trigger = digitalRead(FIRE);
    while (trigger) // aspetto il via con il tasto
    {
      trigger = digitalRead(FIRE);
    }

    Serial.println("Fire!!!!");

    // lampeggio per dire che sto per stampare, todo, da riumovere nella definitiva?
    for (int c = 0; c < 3; c++)
    {
      digitalWrite(LED_C, LOW);
      delay(300);
      digitalWrite(LED_C, HIGH);
      delay(300);
    }

    // per ogni colonna (o istante)
    // una colonna è il valore delle valvole aperte e chiuse in un determinato istante espresso come byte in cui il MSB rappresenta l'alto della lettera
    // 1 aperta 0 chiusa
    for (int c = 0; c < (dimensioneMsg);)
    {

      if (InterruptEn) // se modalità interrupt
      {
        if (state == 1) // attende che qualcun'altro metta state a 0 (non fa c++ se state non cambia)
        {
          // todo no interrupt
          fire(msgCode, c); // apro e chiudo le valvole
          c++;
          state = 0;
        }

        //
        // TODO todo
        // se la bici si ferma ora non chiudo le valvole!!
        //
        //
      }
      else
      { // modalità a tempo
        delay(tempo_ms);
        fire(msgCode, c);
        c++;
      }
    }
    delay(tempo_ms);
    closeAll();     // chiudo tutte le valvole
    webFlag = true; // deve essere riarmato
  }
}
