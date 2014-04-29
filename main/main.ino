#include <Servo.h>


Servo servoKopf;
const int SERVOKOPFPIN = 13;
const int NEIGUNGPIN = A5;

const int US_PIN = 10;
const int US_HINTEN_PIN = 2;
const int TASTER = 100;

const int LINKS_PIN = 2;
const int MITTE_LINKS_PIN = 1;
const int MITTE_RECHTS_PIN = 0;
const int RECHTS_PIN = 4;
const int REFLEX_PIN = 3;

int links;

int mitte_l;
int mitte_r;
int rechts;
int reflex;
int taster;
int dist1;
int dist2;
int rampenZaehl;
Servo Greifarm;
int SERVOGREIFPIN = 12;
Servo Hebarm;
int SERVOHEBPIN = 11;
int lichtZaehl;
int abbruchVariable = 1;
int untenZaehl = 0;

int sw = 100;
int Kreis = 15;
int Silber = 750;

void setup() {
  servoKopf.attach(SERVOKOPFPIN);
  servoKopf.write(90);
  Greifarm.attach(SERVOGREIFPIN);
  Greifarm.write(180);
  Hebarm.attach(SERVOHEBPIN);
  Hebarm.write(50);
  pinMode(TASTER, INPUT);
  
  delay(1000);  
  // 0=Rechts
  // 90=Geradeaus
  // 180=Links

  Serial.begin(57600);  
  /* while(1==1){
   getUSDistInCm(US_HINTEN_PIN);
   delay(100);
   } */
   //untererRaum();
   neigung_begin();
}


void loop() {   
  //Off(3);
  //delay(1);
  // sensoren abfragen
  links = analogRead(LINKS_PIN);
  mitte_l = analogRead(MITTE_LINKS_PIN);
  mitte_r = analogRead(MITTE_RECHTS_PIN);
  rechts = analogRead(RECHTS_PIN);
  reflex = analogRead(REFLEX_PIN);
  checkForNeigung();
  int dist = getUSDistInCm(US_PIN);  
  abbruchVariable = 1;
  // 1=links
  // 2=rechts
  Serial.print(links);
  Serial.print(";");
  Serial.print(mitte_l);
  Serial.print(";");
  Serial.print(mitte_r);
  Serial.print(";");
  Serial.print(rechts);
  Serial.print("l ");
  Serial.print(reflex);
  Serial.print("r ");

  // Entscheidung treffen


  
  if(neigung_istNachObenGeneigt()==true)
  {
    zustand_change(0,1);
    rampenZaehl = 1;
    Serial.print("nach oben");
    rampeHoch();
  }
  else if(untenAufNeigung()==true)
  {
    zustand_change(0,2);
    rampenZaehl = 2;
    Serial.print("nach unten");
    rampeRunter();
  }

  else if(reflex > Silber && rampenZaehl == 1)
  {
    zustand_change(1,1);
    obererRaum();

  }
  /*else if(reflex > Silber && rampenZaehl == 2)
  {
    zustand_change(1,2);
    untererRaum();

  }*/
  else if(reflex > Silber && rampenZaehl == 3)
  {
    zustand_change(1,2);
    untererRaum();
  }
  else if(rampenZaehl == 2 && rampenZaehl != 3)  // Einmal kurz anhalten
  {
    Off(3);
    delay(500);  
    //OnRev(3,100);
    //delay(100);
    rampenZaehl = 3;
  }
  else if(mitte_l < sw && rechts < sw)
  {
    OnFwd(1,100);
    OnRev(2,50);
    delay(350);
    
    Serial.print("Kreuzung");
    Off(3);
    delay(10);
  }
  else if(dist < 6)    // ist da ein Hindernis?
  {
    zustand_change(0,3);
    Off(3);
    delay(50);
    // ist da _wirklich_ ein Hindernis?
    if(getUSDistInCm(US_PIN)<7)
    {
      umfahren();
    }
  }
  else if(rechts < sw && mitte_r < sw)  // ? ? + +
  {                                     // die beiden rechten
    zustand_change(0,20);
    OnFwd(1,100); 
    OnRev(2,50);
    delay(700); 
  }
  /* else if(links < sw && mitte_l < sw)   // die beiden linken
   {
   zustand_change(0,21);
   OnRev(1,50); 
   OnFwd(2,100); 
   delay(700); 
   // Serial.print(" mitte_l ");
   }*/







  else if(rechts < sw)  // ? ? ? +
  {          // der rechte aeussere sieht schwarz -> Kreuzung
    zustand_change(0,4);
    OnFwd(1,100); 
    OnRev(2,80); 
    delay(410);
  }
  else if(links < sw)  // der linke
  {          // +---
    //zustand_change(0,10);
    Serial.print("links");
    OnFwd(2,100); 
    OnRev(1,80);
    unsigned long merkMillis = millis();  
    while(analogRead(RECHTS_PIN) > sw && (millis()-merkMillis)<410){
      delay(1);
    } 
  }
  else if(mitte_l < sw)  // die mittleren
  {
    zustand_change(0,8);
    OnRev(1,60); 
    OnFwd(2,100); 
    //delay(20); 
    Serial.print(" mitte_l ");
  }
  else if(mitte_r < sw)
  {
    //zustand_change(0,9);
    OnFwd(1,100); 
    OnRev(2,85); 
    delay(10); 
    Serial.print(" mitte_r ");
  }

  else  
  {
    OnFwd(3, 60);
    delay(5);
    zustand_change(0,14);
    
  }
  zustand_print();
  
}
//void untererRaum()
//{
//OnRev(1,100);
//OnFwd(2,100);
//delay(1000);

//}





