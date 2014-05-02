void obererRaum(){
  const int rampenZaehl = 1;
  // fahre mal ein Stueck in den Raum rein
  // => 1 - er hat sofort eine Dose gefunde
  // => 0 - keine Dose
  if( fahreInRaumReinOben() == 1){
    // die Dose steht vor ihm
    
    fahrZurDose();

    richteDichAus();

    linksWandDrehungOben();
    // links ist die Wand, also drehe dich andersherum
  }  
  else
  {
    // er muss die Dose erst finden
    int erg = findeDoseOgrob();
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

int fahreInRaumReinOben(){
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
  //OnFwd(2,100);
  //OnRev(1,15);
  //delay(2000);
  Off(3);
  delay(50);
  OnFwd(1,50);
  OnFwd(2,60);
  delay(1500);
  // fahre ein StÃ¼ck rÃ¼ckswÃ¤rts falls die Dose dort steht
  Off(3);
  delay(75);

  return 0;
}




void findeDose(){
  // erst mal reinfahren 
  OnFwd(3,100);
  delay(500);
  OnFwd(1,100);
  OnRev(2,100);
  delay(150); 
  Off(3);
  delay(75); 
  
  // Endlosschleife
  servoKopf.write(0);                   // Rechts
  delay(1000);
  while(getUSDistInCm(US_PIN)>55){
    OnFwd(3, 66); 
    delay(50);

  }
  Off(3);
  delay(500);
  servoKopf.write(90);
  OnFwd(3,100);
  delay(300);
  OnFwd(1,100);
  OnRev(2,50);
  delay(900);   // max. 900
  while(getUSDistInCm(US_PIN)>50){
    OnFwd(1,85);
    OnRev(2,20);
    delay(100); 
    if(getUSDistInCm(US_PIN)<50){ break;}
    Off(3);
    delay(100);
  } 
  Off(3); 
  delay(500); 
  OnFwd(1,80);
  OnRev(2,100);
  delay(250);


}

void nimmDose(){
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
    servoKopf.write(90+44);      // Links      
    delay(800);
    int rechtsDist = getUSDistInCm(US_PIN);

    servoKopf.write(90-44);      // rechts
    delay(800);
    int linksDist = getUSDistInCm(US_PIN);
    servoKopf.write(90);      // Links    
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
      delay(175);



    }
  }
  // er steht also wirklich vor der Dose
  OnRev(3,100);
  delay(500);
  Off(3);
  delay(500);
  Greifarm.write(0);     // Auf
  OnFwd(1,100);
  OnRev(2,100);
  delay(1500);
  while(getUSDistInCm(US_HINTEN_PIN)>20){
    OnFwd(1,100);
    OnRev(2,100);
    delay(50);
  }
 
 OnFwd(1,100);
 OnRev(2,100);
 delay(125);
  Off(3);
  delay(500);
  while(getUSDistInCm(US_HINTEN_PIN)>4){
    OnRev(3,50);
    delay(50);
  }
  OnRev(3,50);
  delay(300);
  Greifarm.write(180);   // Zu
  delay(500);
  Off(3);
  for(int heben = 20; heben < 180; heben++){
    Hebarm.write(heben);     // Hoch
    delay(20);
  }
  /*delay(500);
  Hebarm.write(40);     // Hoch
  delay(500);
  Hebarm.write(60);     // Hoch
  delay(500);
  Hebarm.write(80);     // Hoch
  delay(500);
  Hebarm.write(100);     // Hoch
  delay(500);
  Hebarm.write(120);     // Hoch
  delay(500);
  Hebarm.write(140);     // Hoch
  delay(500);
  Hebarm.write(160);     // Hoch
  delay(500);
  Hebarm.write(180);     // Hoch
  delay(500);*/

  Off(3);
  delay(500);
}



void fahreSolangeWeissBisHindernis(){
  // fahre vor solange alle weiÃŸ sehen und kein kein Hindernis
  links = analogRead(LINKS_PIN);
  mitte_l = analogRead(MITTE_LINKS_PIN);
  mitte_r = analogRead(MITTE_RECHTS_PIN);
  rechts = analogRead(RECHTS_PIN);
  reflex = analogRead(REFLEX_PIN);

  while(links > sw && mitte_l > sw && mitte_r > sw && rechts > sw && getUSDistInCm(US_PIN) > 5 && reflex < Silber){
    OnFwd(3,75);
    delay(50);
    links = analogRead(LINKS_PIN);
    mitte_l = analogRead(MITTE_LINKS_PIN);
    mitte_r = analogRead(MITTE_RECHTS_PIN);
    rechts = analogRead(RECHTS_PIN);
    reflex = analogRead(REFLEX_PIN);

  }//  }
  // war das was schwarz? 
  links = analogRead(LINKS_PIN);
  mitte_l = analogRead(MITTE_LINKS_PIN);
  mitte_r = analogRead(MITTE_RECHTS_PIN);
  rechts = analogRead(RECHTS_PIN);
  reflex = analogRead(REFLEX_PIN); 
  if(links < sw){       
    // ist dort wirklich Schwarz
    Off(3);
    delay(2000);
    links = analogRead(LINKS_PIN);
    if(links < sw){  
       //OnFwd(3,100);
       //delay(200);
     /* while(rechts > sw){
        OnFwd(2,100);
        OnRev(1,50);
        delay(50);
        rechts = analogRead(RECHTS_PIN);
      }
      // lege Dose ab
      //  ecke();

      
      OnRev(1,100);
      OnRev(2,25);
      delay(1500);
      Off(3);
      delay(500);
      OnRev(1,100);
      OnFwd(2,100);
      delay(1000);
      Off(3);
      delay(500);
      OnRev(3,100);
      delay(1000);*/
   
    OnFwd(3,100);
    delay(400);
    OnFwd(1,100);
    Off(2);
    delay(2500);
    OnRev(3,100);
    delay(750);
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
      delay(5000);
    }
  }
      else if(reflex > Silber){ 
        OnRev(3,100);
        delay(750);
        OnFwd(1,100);
        Off(2);
        delay(500);
    }

  else{
    //Da ist ein Hindernis  
    servoKopf.write(90);
    // OnFwd(3,100);
    // delay(500);
    OnRev(3,100);
    delay(500);
    OnFwd(1,100);
    delay(450);
  }

}


void ecke(){
  OnFwd(2,100);
  OnRev(1,100);
  delay(1600);
  Hebarm.write(0);     // Runter
  delay(500);
  Greifarm.write(0);   // Auf
  delay(500);
  OnFwd(2,100);
  delay(750);
  Off(3);
  delay(5000);
  return;
}













void legeDoseAb(){

}


void linksWandDrehungOben(){
  OnRev(3,100);
  delay(100);
  Off(3);
  delay(500);
  OnRev(1,100);
  OnFwd(2,100);
  delay(1500);
  while(getUSDistInCm(US_HINTEN_PIN)>20){
    OnRev(1,66);
    OnFwd(2,66);
    delay(50);
  }
  OnRev(1,66);
  OnFwd(2,66);
  delay(350);


}

int findeDoseOgrob(){
                    // Endlosschleife
  int wandIstOK = 0;
  servoKopf.write(0);                   // drehe den Kopf nach rechts
  delay(1000);
  while(1==1){
    // gucke rechts

    int dist = getUSDistInCm(US_PIN);
    // ist die Dose da irgendwo?
    if( dist < 50 ){
      // ist sie weit weg?
      return 1;
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












