const int SCHWELLE_NEIGUNG = 20;
const int ZZ_NEIGUNG = 10;
const int NEIGUNG_NULL = 322;
int obenZaehl=0;
int raumZaehl=0;

void neigung_begin(){
  //for(int n=0; n<10; n++){
  //  NEIGUNG_NULL += analogRead(NEIGUNGPIN);
  //  delay(100);
  //} 
  //NEIGUNG_NULL /= 10;
  //Serial.print(NEIGUNG_NULL);
  //delay(1000);
  //Serial.print(";");
}

void checkForNeigung(){
  int val = NEIGUNG_NULL - analogRead(NEIGUNGPIN);

  Serial.print(val);
  Serial.print(";");
  Serial.print(untenZaehl);
  Serial.print(";");
  Serial.print(untenAufNeigung());
  Serial.print(";");
  Serial.print(obenZaehl);
  Serial.print(";");
  Serial.print(neigung_istNachObenGeneigt());
  Serial.print("n ");
  
  // miss die Neigung - NEIGUNGPIN
  if(val > SCHWELLE_NEIGUNG)
  {
    // erhoehe die neigungszahl, falls ueber einem bestimmten Wert
    obenZaehl++;
    if(obenZaehl > SCHWELLE_NEIGUNG + 10){
      obenZaehl = SCHWELLE_NEIGUNG + 10;
    }
  }
  else if(val < -SCHWELLE_NEIGUNG)
  {
    untenZaehl++;
    if(untenZaehl > SCHWELLE_NEIGUNG + 10){
      untenZaehl = SCHWELLE_NEIGUNG + 10;
    }

  }
  else
  {
    // nicht nach oiben
    // und nicht nach unten
    obenZaehl -= 2;
    if(obenZaehl < 0){
      obenZaehl=0;
    }
    untenZaehl -= 2;
    if(untenZaehl < 0){
      untenZaehl=0;
    }
  }
}

bool neigung_istNachObenGeneigt(){
  if(obenZaehl > ZZ_NEIGUNG)
  {
    return true;
  }
  else
  {
    return false;
  }  
}

bool untenAufNeigung(){
  if(untenZaehl > ZZ_NEIGUNG)
  {
    return true;
  }
  else
  {
    return false;
  }  
}












/*
servoKopf.write(180);                   // Links
 delay(1000);
 int sollDist = getUSDistInCm(US_PIN);
 if(sollDist < 7){
 sollDist=7;
 }
 else if(sollDist > 15){
 sollDist = 15;  
 }
 
 
 
 while(1==1){                            // Rampe
 if( neigung() > 305){
 neigZaehl++;
 }
 else{
 neigZaehl-=10;
 if(neigZaehl<0){
 neigZaehl=0;
 }
 }
 int dist = getUSDistInCm(US_PIN);
 if(dist > 10 && dist < 999){
 OnFwd(2,75);
 OnFwd(1,40);
 delay(100);
 OnFwd(3, 66);
 delay(100);
 }
 else if(dist < sollDist){
 OnFwd(1,75);
 OnFwd(2,35);
 delay(100);
 OnFwd(3, 66);
 delay(100);
 }
 else{
 OnFwd(3,66);
 delay(200);
 }
 if(neigZaehl >= 15){
 // stehen bleiben
/* OnRev(3,100);
 delay(400);
 OnFwd(1,100);
 OnRev(2,50);
 delay(1775);
 servoKopf.write(90);
 
 lichtZahl++;//frage Lichtsensor ab.
 // Kopf nach vorne
 
 // bis zur Wand geradeaus fahren
 
 // 90 Grad nach rechts
 
 // break;
 //obererRaum();
 }
 
 if(lichtZahl >= 1){
 }
 
 }
 */


