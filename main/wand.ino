
void wand(){
  OnRev(2,100);
  OnFwd(1,100);
  delay(900);

  unsigned long vergangen;
  unsigned long merkMillis = millis();
  vergangen=millis()-merkMillis;

  OnFwd(3,100);
  while(analogRead(MITTE_LINKS_PIN) > sw && analogRead(MITTE_RECHTS_PIN) > sw && analogRead(LINKS_PIN) > sw && analogRead(RECHTS_PIN) > sw){
    OnFwd(3,100);

    unsigned long vergangen;
    vergangen=millis()-merkMillis;
    if(vergangen > 1000){
      wandr();
      break;
    }

    delay(50);
  }
  Off(3);
  delay(1);
  loop();
}


void wandr(){
  OnFwd(1,100);
  OnRev(2,100);
  delay(1800);
  OnFwd(3,100);
  delay(500);
  while(analogRead(MITTE_LINKS_PIN) > sw && analogRead(MITTE_RECHTS_PIN) > sw && analogRead(LINKS_PIN) > sw && analogRead(RECHTS_PIN) > sw){
    OnFwd(3,100);
    delay(50);
  }
  OnFwd(3,100);
  delay(250);
  loop();
}//}


