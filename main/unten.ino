int diff = 0;

// er hat gemerkt, dass da die Reflex-Folie ist
void untererRaum(){

  const int rampenZaehl = 3;
  // fahre mal ein Stueck in den Raum rein
  // => 1 - er hat sofort eine Dose gefunde
  // => 0 - keine Dose
  if( fahreInRaumRein() == 1){
    // die Dose steht vor ihm
    fahrZurDose();

    richteDichAus();

    linksWandDrehung();
    // links ist die Wand, also drehe dich andersherum
  }  
  else
  {
    // er muss die Dose erst finden
    int erg = findeDoseUgrob();
    // 1 - Dose ist nah drann
    // 2 - Dose ist weit weg
    if(erg == 2){
      dreheDichZurDoseWeit();
        fahrZurDose();  
    }else{
      dreheDichZurDoseNah();
    }    
  
    richteDichAus();

    drehung();
  }

  // er steht jetzt mit dem Hintern zur Dose und nimmt sie auf
 nimmDoseU();

  // er hat die Dose jetzt geladen

  // dreh dich ein wenig nach rechts


  abbruchVariable = 1; 
  // fahre am Rand entlang bis er schwarz sieht
  fahreSolangeWeissBisHindernisU();

  //legeDoseAbU();
}

void dreheDichZurDoseNah(){
  // drehe dich nach rechts, bis der US kleiner als 30 ist
  servoKopf.write(90);
  OnFwd(1,100);
  OnRev(2,50);
  delay(1200); 
  while(getUSDistInCm(US_PIN)>35){
    OnFwd(1,80);
    OnRev(2,20);
    delay(100); 
    //if(getUSDistInCm(US_PIN)<35){ 
    //  break;
    //}
    Off(3);
    delay(100);
  } 
  Off(3); 
  delay(500); 
  OnFwd(1,100); // und noch ein bisschen weiter 
  OnRev(2,50);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
  delay(300);


}



int fahreInRaumRein(){
  // erst mal reinfahren 
  OnFwd(3,100);
  delay(400);
  // wenn die Dose schon hier steht dann breche ab
  if( getUSDistInCm(US_PIN) < 60 )
  {
    raumZaehl = 2;   // Variable damit er Ã¼berflÃ¼ssige Funktionen Ã¼berspringt
    return 1;
  }
  // erst mal nach links drehen
  OnFwd(2,100);
  OnRev(1,15);
  delay(2500);
  Off(3);
  delay(50);
  OnRev(3,50);
  delay(1500);
  // fahre ein StÃ¼ck rÃ¼ckswÃ¤rts falls die Dose dort steht
  Off(3);
  delay(75);

  return 0;
}


// er steht im unteren Raum und soll
// jetzt die Wand entlang fahren, bis er
// rechts die Dose sieht
int findeDoseUgrob(){
                    // Endlosschleife
  int wandIstOK = 0;
  servoKopf.write(0);                   // drehe den Kopf nach rechts
  delay(1000);
  while(1==1){
    // gucke rechts

    int dist = getUSDistInCm(US_PIN);
    // ist die Dose da irgendwo?
    if( dist < 65 ){
      // ist sie weit weg?
      if(dist > 45){ 
        // ... soll er noch ein stueckchen vor fahren  
        OnFwd(3, 100);
        delay(500);
        Off(3);
        return 2;
      }
      // oder nah drann?
      else
      {
        return 1;
      }
    }

    // fahre ein stueckchen
    OnFwd(3, 80);
    delay(300);

    if(wandIstOK<2){
      Off(3);
      servoKopf.write(180);                   // drehe den Kopf nach links
      delay(1000);
      dist1 = getUSDistInCm(US_PIN);
      servoKopf.write(0);                   // drehe den Kopf nach rechts
      delay(600);
    }

    // Miss Entfernung
    // wenn die Wand zu weit aber nicht extrem weit weg ist, dann ...
    
    if( dist1 > 9 && dist1 < 40 && wandIstOK < 2 )
    {
      // ... dreh dich ein wenig zur Wand
      OnFwd(1, 10);
      OnFwd(2, 100);
      delay(200);
      Off(3);
    }else{
      wandIstOK++;
      delay(200);
    }

  }
}


void dreheDichZurDoseWeit(){

  int posKopf = 0;
  OnFwd(1,100);
  
  delay(500);

  while( posKopf < 60){
    // drehe dich ein wenig nach rechts
    OnFwd(1,60);
    //OnRev(2,20);
    posKopf += 10;
    servoKopf.write(posKopf);
    delay(300);
    Off(3);
    delay(100);



    while( getUSDistInCm(US_PIN) > 60 ){
      posKopf++;
      servoKopf.write(posKopf);
      delay(100);
      if(posKopf > 70){
        break;
      }
    }
    OnFwd(1,100);
    delay(150);
  }




}

void richteDichAus(){
  while(getUSDistInCm(US_PIN)>9){
    OnFwd(3,100);
    delay(50);
  }      
  OnRev(3,100);
  delay(100);

  // jetzt hat er was gesehen
  // ist es die Dose?
  while(1==1){
    Off(3);
    delay(500);
    servoKopf.write(90+44);      // Rechts      
    delay(800);
    int rechtsDist = getUSDistInCm(US_PIN);

    servoKopf.write(90-44);      // Links
    delay(800);
    int linksDist = getUSDistInCm(US_PIN);
    servoKopf.write(90);      

    if (rechtsDist > 15 && linksDist > 15){
      break;
    } 
    else if (rechtsDist <= 15 && linksDist > 15){  
      OnFwd(2,75);
      OnRev(1,75);
      delay(100);
    }
    else if (rechtsDist > 15 && linksDist <= 15){  
      OnFwd(1,75);
      OnRev(2,75);
      delay(100);

    }
    else if (rechtsDist <= 15 && linksDist <= 15){ 
      OnFwd(1,100);
      OnRev(2,100);
      delay(1000);
      while(getUSDistInCm(US_PIN) > 25){
        OnFwd(1,100); 
        OnRev(2,100);
        delay(50);
      }
      OnFwd(2,100);
      OnRev(1,100);
      delay(150);



    }
  }
}

void drehung(){
  // er steht also wirklich vor der Dose
  OnRev(3,100);
  delay(100);
  Off(3);
  delay(500);
  OnFwd(2,100);
  OnRev(1,100);
  delay(1500);
  while(getUSDistInCm(US_HINTEN_PIN)>20){
    OnFwd(2,70);
    OnRev(1,70);
    delay(50);
  }
  OnFwd(2,70);
  OnRev(1,70);
  delay(500);
}

void linksWandDrehung(){
  OnRev(3,100);
  delay(100);
  Off(3);
  delay(500);
  OnFwd(1,100);
  OnRev(2,100);
  delay(1500);
  while(getUSDistInCm(US_HINTEN_PIN)>20){
    OnFwd(1,70);
    OnRev(2,70);
    delay(50);
  }
  OnFwd(1,70);
  OnRev(2,70);
  delay(300);


}

void  nimmDoseU(){
  OnRev(3,100);
  delay(50);
  Off(3);
  delay(500);
  for(int oeffnen = 180; oeffnen > 0; oeffnen--){
    Greifarm.write(oeffnen);     // Hoch
    delay(20);
  }
  delay(100);
  // Fahre bis zur Dose aber maximal 5000 Millisekunden
  unsigned long merk = millis();
  while(getUSDistInCm(US_HINTEN_PIN)>4 && (millis()-merk)< 2500){
    OnRev(3,40);
    delay(50);
  }
  OnRev(3,50);
  delay(300);
  Off(3);
  delay(50);
  for(int oeffnen = 0; oeffnen < 160; oeffnen++){
    Greifarm.write(oeffnen);     // Hoch
    OnRev(3,50);
    delay(20);
  }   // Zu
  delay(500);
  Off(3);
  for(int heben = 20; heben < 180; heben++){
    Hebarm.write(heben);     // Hoch
    delay(20);
  }
  Off(3);
  delay(500);
    servoKopf.write(90);
    OnFwd(1,75);
    OnRev(2,75);
    delay(750);
    Off(3);
    delay(300);
}



void fahreSolangeWeissBisHindernisU(){
  while(abbruchVariable==1){
    // fahre vor solange alle weiÃŸ sehen und kein kein Hindernis
    links = analogRead(LINKS_PIN);
    mitte_l = analogRead(MITTE_LINKS_PIN);
    mitte_r = analogRead(MITTE_RECHTS_PIN);
    rechts = analogRead(RECHTS_PIN);
    reflex = analogRead(REFLEX_PIN);

    // solange alle Sensoren weiÃŸ, der US kein HIndernis und der Reflex-Sensor kein Silber sieht ...
    // fahre geradeaus
    while(links > sw && mitte_l > sw && mitte_r > sw && rechts > sw && getUSDistInCm(US_PIN) > 7 && reflex < Silber){
      OnFwd(1,75);
      OnFwd(2,85);
      delay(100);
      links = analogRead(LINKS_PIN);
      mitte_l = analogRead(MITTE_LINKS_PIN);
      mitte_r = analogRead(MITTE_RECHTS_PIN);
      rechts = analogRead(RECHTS_PIN);
      reflex = analogRead(REFLEX_PIN);

    }

    // war das was schwarz? 
    links = analogRead(LINKS_PIN);
    mitte_l = analogRead(MITTE_LINKS_PIN);
    mitte_r = analogRead(MITTE_RECHTS_PIN);
    rechts = analogRead(RECHTS_PIN);
    reflex = analogRead(REFLEX_PIN); 
    
    if(links < sw && mitte_l < sw && mitte_r < sw || rechts < sw){
      Off(3);
      delay(100);
      //OnRev(3,100);
      //delay(500);
      links = analogRead(LINKS_PIN);
      mitte_l = analogRead(MITTE_LINKS_PIN);
      mitte_r = analogRead(MITTE_RECHTS_PIN);
      rechts = analogRead(RECHTS_PIN);
      if(links < sw && mitte_l < sw && mitte_r < sw && rechts < sw){ 
        OnRev(3,100);
        delay(500);
        OnFwd(1,80);
        OnRev(2,80);
        delay(2500);
        OnRev(3,100);
        delay(600);
        
        Hebarm.write(70);     // Runter
        delay(500);
        Off(3);
        delay(500);
        Greifarm.write(0);     // Auf
        delay(500);
        Off(3);
        delay(500);
        OnFwd(3,100);
        delay(1000);
        Greifarm.write(180);   // Zu
        delay(500);
        Off(3); 
        delay(2000);
        abbruchVariable = 2;
      }
    }
    else if(links < sw || mitte_l < sw){       
      // ist dort wirklich Schwarz
      Off(3);
      delay(2000);
      links = analogRead(LINKS_PIN);
      mitte_l = analogRead(MITTE_LINKS_PIN);
      if(links < sw || mitte_l < sw){ 
        eckeU();
      }
    }
    else if(reflex > Silber){ 
      OnRev(3,100);
      delay(800);
      OnFwd(1,100);
      OnRev(2,100);
      delay(700);
    }


    
    else if(getUSDistInCm(US_PIN) < 8 || rechts < sw){
      delay(100);
      OnRev(3,100);
      delay(500);
      while(getUSDistInCm(US_PIN) < 21){
          OnFwd(1,100);
          OnRev(2,90);
          delay(100);
            Serial.print("Kackspast");
            Serial.print(";");

      }
      //Da ist eine Wand  
    //  servoKopf.write(90);
      // OnFwd(3,100);
      // delay(500);
    //  OnRev(3,100);
    //  delay(500);
    //  OnFwd(1,100);
    //  OnFwd(2,15);
    //  delay(1250);
    }
  }
}


// er hat jetzt links schwarz gesehen uns doll die Dose nun absetzen
void eckeU(){
  abbruchVariable = 2;
  OnRev(3,100);
  delay(50);
  OnFwd(1,100);
  Off(2);
  delay(3750);
  
  OnRev(3,100);
  delay(900);
  
  Off(3);
  delay(500);
  
  Hebarm.write(70);     // Runter
  delay(500);
  Off(3);
  delay(500);
  Greifarm.write(0);     // Auf
  delay(500);
  Off(3);
  delay(500);
  OnFwd(3,100);
  delay(1000);
  Greifarm.write(180);   // Zu
  delay(500);
  Off(3); 
  delay(2000);
}


void fahrZurDose(){
  servoKopf.write(90);                   // drehe den Kopf nach vorne
  delay(500);

  int startDist = getUSDistInCm(US_PIN);

  delay(100);
  while( getUSDistInCm(US_PIN) > 10 ){
    // fahre kurz
    OnFwd(3,800);
    delay(300);  
    Off(3);
    startDist -= 10;

    // gucke nach Dose
    servoKopf.write(90-15);                   // drehe den Kopf nach rechts
    delay(200);
    int r = getUSDistInCm(US_PIN);

    servoKopf.write(90+15);                   // drehe den Kopf nach rechts
    delay(200);
    int l = getUSDistInCm(US_PIN);

    servoKopf.write(90);                   // drehe den Kopf nach rechts

    int diff = r - l;
    // korrigiere evtl

      if(diff < -10){
      OnFwd(1, 100);
      Off(2);
    }
    else if (diff > 10){
      OnFwd(2, 100);
      Off(1);
    }
    delay(200);      
    Off(3);
  }
}


