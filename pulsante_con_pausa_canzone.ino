/***************************************************
DFPlayer - A Mini MP3 Player For Arduino
 <https://www.dfrobot.com/product-1121.html>
 
 ***************************************************
 This example shows the basic function of library for DFPlayer.
 
 Created 2016-12-07
 By [Angelo qiao](Angelo.qiao@dfrobot.com)
 
 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
 1.Connection and Diagram can be found here
 <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
 2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int button = A0; // pulsante su A0

int buttonstate = HIGH; // variabile lettura pulsante = alto

int a = 0; // variabile che conteggia la pressione del pulsante
int b = 0; // variabile che conteggia a che canzone siamo arrivati

void setup() {
  mySoftwareSerial.begin(9600);
  Serial.begin(115200); // apre la seriale di arduino su questo canale per leggere lo stato del dfplayer e delle variabili a e b
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(20);  // imposta il volume da 0 a 30

  pinMode (button, INPUT_PULLUP); // imposta il pulsante come input e per ivitare interferenze integra una resistenza all' interno di arduino in pullup cioè mettete sul pin A0 a 5 volt(HIGH) quando il pulsante viene premuto non avviene il cortocircuito perche' c' e' la resistenza e il gnd(LOW) si straferisce sul pin A0.

}

void loop() {
  buttonstate = digitalRead (button); // legge il pulsante ogni 20 millisecondi
  if (buttonstate == LOW) // se il pulsante viene premuto 
  {
    a = a + 1; // a passa da 0 a 1, seconda volta che lo premo a passa da 1 a 2 e cosi' via fino all' ultima traccia che a diventa 0 e ricomincia il conteggio 
    Serial.println("a = ");
    Serial.println(a);
    Serial.println("b = ");
    Serial.println(b);      
  }
  if (a == 1 && b == 0){ // se a è uguale a 1 e b è uguale a 0 allora fai partire la traccia
         myDFPlayer.play(1);
         delay (15000); // ferma tutto per 8 secondi questo valore lo puoi cambiare in base al tempo della traccia, qundi anche il pulsante verra' escluso per 8 secondi
         myDFPlayer.pause(); //pause the mp3                          
         b = b + 1; // b passa da 0 a 1
         Serial.println("a = ");
         Serial.println(a);
         Serial.println("b = ");
         Serial.println(b);
  }
  if (a == 2 && b == 1){ // se a è uguale a 2 e b è uguale a 1 allora fai partire la  seconda traccia
         myDFPlayer.start();  //start the mp3 from the pause
         delay (15000);
         myDFPlayer.pause(); //pause the mp3                           
         b = b + 1; // b passa da 1 a 2
         Serial.println("a = ");
         Serial.println(a);
         Serial.println("b = ");
         Serial.println(b);
  }
  if (a == 3 && b == 2){ // se a è uguale a 3 e b è uguale a 2 allora fai partire la  seconda traccia
         myDFPlayer.start();  //start the mp3 from the pause
         delay (15000);
         a = 0; // a passa da 19 a 0 per ricominciare il conteggio del pulsante
         b = 0; // b passa da 18 a 0 per ricominciare il conteggio delle canzoni         
         Serial.println("a = ");
         Serial.println(a);
         Serial.println("b = ");
         Serial.println(b);
  }
  delay (20);
}
