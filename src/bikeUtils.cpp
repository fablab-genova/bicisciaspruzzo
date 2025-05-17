#include "bikeUtils.h"
#include "myUtils.h"
int columnNum = -1; // gestisce il numero della colonna

void addDecor(byte grigliaA[], byte grigliaB[], byte msgCode[])
{
  for (int i = 0; i < 8; i++)
  {
    addColumn(grigliaA[i], msgCode);
  }
  for (int i = 0; i < 8; i++)
  {
    addColumn(grigliaB[i], msgCode);
  }
}

void printCharacters(byte msgCode[], int dimensioneMsg)
{
  for (int c = 0; c < dimensioneMsg; c++)
  {
    for (int bit = 7; bit >= 0; bit--)
    { // Riga da alto (bit 7) a basso (bit 0)
      for (int j = 0; j < 8; j++)
      {
        Serial.print((msgCode[(c * 8) + j] >> bit) & 1);
      }
      Serial.println();
    }
    Serial.println();
  }
}
void onlyDecor(byte griglia1[], byte griglia2[], byte griglia3[], byte griglia4[], byte msgCode[])
{
  addDecor(griglia1, griglia2, msgCode);
  addDecor(griglia3, griglia4, msgCode);
}
void convertTextandDecor(String messaggio, byte griglia1[], byte griglia2[], byte griglia3[], byte griglia4[], byte msgCode[])
{
  addDecor(griglia1, griglia2, msgCode);
  convertText(messaggio, msgCode);
  addDecor(griglia3, griglia4, msgCode);
}
void convertText(String messaggio, byte msgCode[])
{
  String charToWrite;
  for (int c = 0; c < (messaggio.length()); c++)
  {
    charToWrite = messaggio.substring(c, c + 1);
    // Send the separated characted to addChar function    //
    // Serial.print("char to write: ");
    // Serial.println(charToWrite);
    addChar(charToWrite, msgCode); //
  }
  // Add a little space after each character             //
  // todo:inutile? non credo sia dopo ogni carattere ma penso sia alla fine del testo AC
  // addChar(" ", msgCode); //bho io gli ho tolti se poi vediamo che servono li rimetto AC
  // addChar(" ", msgCode); //bho io gli ho tolti se poi vediamo che servono li rimetto AC
}
void closeAll()
{
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
}
// questa fire e' quella di bikelangelo, apre le elettrovalvole ma non le chiude.
void fire(byte msgCode[], int c)
{
  boolean pintState;
  pintState = (msgCode[c] / B10000000) % B10; //
                                              // todo togliere i println
  digitalWrite(LED0, pintState);
  Serial.print("LED 0: ");
  Serial.println(pintState);
  pintState = (msgCode[c] / B1000000) % B10; //
  digitalWrite(LED1, pintState);
  Serial.print("LED 1: ");
  Serial.println(pintState);
  pintState = (msgCode[c] / B100000) % B10; //
  digitalWrite(LED2, pintState);
  Serial.print("LED 2: ");
  Serial.println(pintState);               //
  pintState = (msgCode[c] / B10000) % B10; //
  digitalWrite(LED3, pintState);
  Serial.print("LED 3: ");
  Serial.println(pintState);              //
  pintState = (msgCode[c] / B1000) % B10; //
  digitalWrite(LED4, pintState);
  Serial.print("LED 4: ");
  Serial.println(pintState);             //
  pintState = (msgCode[c] / B100) % B10; //
  digitalWrite(LED5, pintState);
  Serial.print("LED 5: ");
  Serial.println(pintState);            //
  pintState = (msgCode[c] / B10) % B10; //
  digitalWrite(LED6, pintState);
  Serial.print("LED 6: ");
  Serial.println(pintState); //
  pintState = msgCode[c] % B10;
  digitalWrite(LED7, pintState);
  Serial.print("LED 7: ");
  Serial.println(pintState);
  // delay(tempo_ms);//lo posso passare dal main per settarlo da http
  // closeAll()
}

void addColumn(byte x, byte msgCode[])
{
  columnNum += 1;
  msgCode[columnNum] = (x); // TO DO: tengo que meter este array como argumento de la funcion por que si no no puedo declararlo despues de leer lo largo q es el texto
}
void addChar(String y, byte msgCode[])
{
  if (y == "1")
  {
    addColumn(B0010001, msgCode);
    addColumn(B0100001, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "2")
  {
    addColumn(B0100001, msgCode);
    addColumn(B1000011, msgCode);
    addColumn(B1000101, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B0110001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "3")
  {
    addColumn(B0100010, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B0110110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "4")
  {
    addColumn(B0001100, msgCode);
    addColumn(B0010100, msgCode);
    addColumn(B0100100, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B0000100, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "5")
  {
    addColumn(B1110010, msgCode);
    addColumn(B1010001, msgCode);
    addColumn(B1010001, msgCode);
    addColumn(B1010001, msgCode);
    addColumn(B1001110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "6")
  {
    addColumn(B0111110, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B0100110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "7")
  {
    addColumn(B1000000, msgCode);
    addColumn(B1000111, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B1010000, msgCode);
    addColumn(B1100000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "8")
  {
    addColumn(B0110110, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B0110110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "9")
  {
    addColumn(B0110010, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B0111110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "0")
  {
    addColumn(B0111110, msgCode);
    addColumn(B1000101, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1010001, msgCode);
    addColumn(B0111110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "A")
  {
    addColumn(B0011111, msgCode);
    addColumn(B0100100, msgCode);
    addColumn(B1000100, msgCode);
    addColumn(B1000100, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "B")
  {
    addColumn(B1111111, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B0110110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "C")
  {
    addColumn(B0111110, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B0100010, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "D")
  {
    addColumn(B1111111, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B0111110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "E")
  {
    addColumn(B1111111, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "F")
  {
    addColumn(B1111111, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B1000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "G")
  {
    addColumn(B0111110, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000101, msgCode);
    addColumn(B0100110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "H")
  {
    addColumn(B1111111, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "I")
  {
    addColumn(B0000000, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "J")
  {
    addColumn(B0000000, msgCode);
    addColumn(B0000010, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1111110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "K")
  {
    addColumn(B1111111, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0010100, msgCode);
    addColumn(B0100010, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "L")
  {
    addColumn(B1111111, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "M")
  {
    addColumn(B1111111, msgCode);
    addColumn(B0100000, msgCode);
    addColumn(B0011000, msgCode);
    addColumn(B0100000, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "N")
  {
    addColumn(B1111111, msgCode);
    addColumn(B0010000, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0000100, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "O")
  {
    addColumn(B0111110, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B0111110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "P")
  {
    addColumn(B1111111, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B0110000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "Q")
  {
    addColumn(B0111100, msgCode);
    addColumn(B1000010, msgCode);
    addColumn(B1000010, msgCode);
    addColumn(B1000010, msgCode);
    addColumn(B0111101, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "R")
  {
    addColumn(B1111111, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B1001100, msgCode);
    addColumn(B1001010, msgCode);
    addColumn(B0110001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "S")
  {
    addColumn(B0110010, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B0100110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "T")
  {
    addColumn(B1000000, msgCode);
    addColumn(B1000000, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B1000000, msgCode);
    addColumn(B1000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "U")
  {
    addColumn(B1111110, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B1111110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "V")
  {
    addColumn(B1111100, msgCode);
    addColumn(B0000010, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000010, msgCode);
    addColumn(B1111100, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "W")
  {
    addColumn(B1111110, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000110, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B1111110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "X")
  {
    addColumn(B1100011, msgCode);
    addColumn(B0010100, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0010100, msgCode);
    addColumn(B1100011, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "Y")
  {
    addColumn(B1110000, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0001111, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B1110000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "Z")
  {
    addColumn(B1000011, msgCode);
    addColumn(B1000101, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1010001, msgCode);
    addColumn(B1000011, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "Z")
  {
    addColumn(B1000011, msgCode);
    addColumn(B1000101, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1010001, msgCode);
    addColumn(B1000011, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == " ")
  {
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == ".")
  {
    addColumn(B0000000, msgCode);
    addColumn(B0000011, msgCode);
    addColumn(B0000011, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "_")
  {
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "-")
  {
    addColumn(B0000000, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "!")
  {
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B1111101, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "(")
  {
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0111110, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == ")")
  {
    addColumn(B1000001, msgCode);
    addColumn(B0111110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "%")
  {
    addColumn(B1100010, msgCode);
    addColumn(B1100100, msgCode);
    addColumn(B0001000, msgCode);
    addColumn(B0010011, msgCode);
    addColumn(B0100011, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == ",")
  {
    addColumn(B0000000, msgCode);
    addColumn(B0000101, msgCode);
    addColumn(B0000110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "?")
  {
    addColumn(B0100000, msgCode);
    addColumn(B1000101, msgCode);
    addColumn(B1001000, msgCode);
    addColumn(B0110000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "#")
  {
    addColumn(B0010100, msgCode);
    addColumn(B0111110, msgCode);
    addColumn(B0010100, msgCode);
    addColumn(B0111110, msgCode);
    addColumn(B0010100, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "@")
  {
    addColumn(B0111110, msgCode);
    addColumn(B1000001, msgCode);
    addColumn(B1011101, msgCode);
    addColumn(B1011101, msgCode);
    addColumn(B0111000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
  else if (y == "$")
  {
    addColumn(B0110010, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B1111111, msgCode);
    addColumn(B1001001, msgCode);
    addColumn(B0100110, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B0000000, msgCode);
    addColumn(B00000000, msgCode); // aggiunto per avere lettere a 8 istanti AC
  }
}
