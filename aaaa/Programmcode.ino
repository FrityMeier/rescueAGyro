void fahren(int mLinks, int mRechts, int pause){
  OnFwd(1,mLinks); 
  OnFwd(2,mRechts); 
  delay(pause); 
}


void kai(int mLinks, int mRechts, int pause, int zustand, String meldung){
  zustand_change(0,zustand);
  OnFwd(1,mLinks); 
  OnFwd(2,100); 
  delay(10); 
  // Serial.print(" mitte_l ");
}


void OnFwd(int m, int v){

  // bei negativen Werten "OnRev" aufrufen
  if(v < 0) {
    OnRev(m, -v);
    return;
  }

  // PINS als Ausgaenge setzen
  DDRD |= B11110000;
  DDRB |= B00000011;

  // den Wert auf "100" deckeln
  if(v > 100) {
    v = 100;
  }
  v = map(v, 0, 100, 0, 255);

  // Motor A
  if(m==1 || m==3){
    digitalWrite(4, LOW); //vrA1
    digitalWrite(9, HIGH);//vrA2    
    analogWrite(5, v); //enA
  }

  // Motor B
  if(m==2 || m==3){
    digitalWrite(7, LOW);//vrB1
    digitalWrite(8, HIGH);//vrB2    
    analogWrite(6, v);
  }    
}

void OnRev(int m, int v)
{
  // bei negativen Werten "OnFwd" aufrufen
  if(v < 0) {
    OnFwd(m, -v);
    return;
  }

  // PINS als Ausgaenge setzen
  DDRD |= B11110000;
  DDRB |= B00000011;

  // den Wert auf "100" deckeln
  if(v > 100) {
    v = 100;
  }

  v = map(v, 0, 100, 0, 255);

  // Motor A
  if(m==1 || m==3){
    digitalWrite(4, HIGH);
    digitalWrite(9, LOW);    
    analogWrite(5, v);
  }

  // Motor B
  if(m==2 || m==3){
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);    
    analogWrite(6, v);
  }    
}


//schaltet den Motor aus. Die Rï¿½der "blockieren"
void Off(int m)  {
  // PINS als Ausgaenge setzen
  DDRD |= B11110000;
  DDRB |= B00000011;

  //Motor A
  if (m == 1  ||  m == 3) {
    digitalWrite(4, HIGH);
    digitalWrite(9, HIGH);
    analogWrite(5, 255);
  }

  //Motor B
  if (m==2 || m==3) {
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    analogWrite(6, 255);
  }
}


