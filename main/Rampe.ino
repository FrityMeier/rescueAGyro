
void rampeHoch(){
  //Off(3);
  //delay(2000);
  if(rechts < sw)  // ? ? ? +
  {          // der rechte aeussere sieht schwarz -> Kreuzung
    OnFwd(1,100); 
    Off(2); 
    delay(50); 
    Serial.print(" rechts ");
  }
  else if(mitte_l < sw)  // die mittleren
  {
    Off(1); 
    OnFwd(2,100); 
    delay(10); 
    Serial.print(" mitte_l ");
  }
  else if(mitte_r < sw)
  {
    OnFwd(1,100); 
    Off(2); 
    delay(10); 
    Serial.print(" mitte_r ");
  }
  else if(links < sw)  // der linke
  {          // +---
    Off(2); 
    OnFwd(1,100);  
    delay(50); 
    Serial.print(" links ");
  }
  else
  {
    OnFwd(3,100);
    delay(10);
  }
  Off(3);
  delay(5);
}


void rampeRunter(){
  //Off(3);
  //delay(2000);
  if(rechts < sw)  // ? ? ? +
  {          // der rechte aeussere sieht schwarz -> Kreuzung
    OnFwd(1,80); 
    OnRev(2,80); 
    delay(30); 
    Serial.print(" rechts ");
  }
  else if(mitte_l < sw)  // die mittleren
  { 
    OnRev(1,80); 
    OnFwd(2,80); 
    delay(20); 
    Serial.print(" mitte_l ");
  }
  else if(mitte_r < sw)
  {
    OnFwd(1,80); 
    OnRev(2,80); 
    delay(20); 
    Serial.print(" mitte_r ");
  }
  else if(links < sw)  // der linke
  {          // +---
    OnRev(1,80); 
    OnFwd(2,80);
    delay(30); 
    Serial.print(" links ");
  }
  else
  {
    OnFwd(3,100);
    delay(10);
  }
  Off(3);
  delay(10); 
}


