void umfahren(){
  Serial.print("p");
  
  // zentriere dich vor der Dose
  while(1==1){
    Off(3);
    delay(500);
    servoKopf.write(90+55);      // Links      
    delay(800);
    int rechtsDist = getUSDistInCm(US_PIN);

    servoKopf.write(90-55);      // rechts
    delay(800);
    int linksDist = getUSDistInCm(US_PIN);
    servoKopf.write(90);      // Links    

    if (rechtsDist > 10 && linksDist > 10){
      // jetzt bin ich zentriert - also gehts weiter
      break; 
    } 
    else if (rechtsDist <= 10 && linksDist > 10){  
      OnFwd(2,75);
      OnRev(1,75);
      delay(100);
    }
    else if (rechtsDist > 10 && linksDist <= 10){  
      OnFwd(1,75);
      OnRev(2,75);
      delay(100);

    }
    else if (rechtsDist <= 10 && linksDist <= 10){ 
      OnRev(3,100);
      delay(250);
      wand();
      break;
    }
  }// end while


  Serial.println("umfahren");
  /*    unsigned long merkMillis = millis();
   delay(200000);
   unsigned long vergangen;
   
   
   vergangen=millis()-merkMillis;
   */
  servoKopf.write(0);      // Rechts
  delay(1000);

  if(getUSDistInCm(US_PIN)>30){       // Ist auf der rechten Seite frei
    Serial.println("rechts frei!?");
    servoKopf.write(90);
    delay(1000); 
    OnRev(3,100);  // rÃ¼ckwaerts
    delay(100);
    OnFwd(1,90);  // drehe dich rechts
    OnRev(2,100);
    delay(1250);
    OnRev(3,60);
    delay(250);
    OnFwd(2,100);
    OnFwd(1,Kreis);      //Fahre Halbkreis   
    delay(1500);
    abbruchVariable = 1;    

    // fahre weiter im Halbkreis und schaue dabei nach der Linie
    while(abbruchVariable == 1){ 
      for(int zaehl = 0; zaehl < 7; zaehl++){
        Off(2); 
        OnFwd(1,30); 
        delay(10);
        if(analogRead(MITTE_RECHTS_PIN)<sw || abbruchVariable == 2){ 
          abbruchVariable = 2; 
          break;
        }
      }

      for(int zaehl = 0; zaehl < 40; zaehl++){
        Off(1); 
        OnFwd(2,100); 
        delay(10);
        if(analogRead(MITTE_RECHTS_PIN)<sw || abbruchVariable == 2){
          abbruchVariable = 2;
          break;
        }
      }
    }
    OnFwd(3,100);
    delay(300);
    abbruchVariable = 1;
    while(analogRead(MITTE_LINKS_PIN) > sw && analogRead(MITTE_RECHTS_PIN) > sw){
      OnFwd(1,90);
      OnRev(2,80);  
      analogRead(MITTE_LINKS_PIN);
      analogRead(MITTE_RECHTS_PIN);
    }
    Off(3);
    delay(1000);
    return;
  }  


  else{
    Serial.println("links");
    servoKopf.write(90);
    delay(1000);
    OnRev(3,100);  // rueckwaerts
    delay(100);
    OnFwd(2,90);  // drehe dich auf der Stelle links
    OnRev(1,100);

    delay(1250);
    OnRev(3,60);
    delay(250);
    OnFwd(1,100);
    OnFwd(2,Kreis);
    delay(1500);

    while(abbruchVariable == 1){ 
      for(int zaehl = 0; zaehl < 10; zaehl++){
        Off(1); 
        OnFwd(2,30); 
        delay(10);
        if(analogRead(MITTE_LINKS_PIN)<sw || abbruchVariable == 2){ 
          abbruchVariable = 2; 
          break;
        }
      }

      for(int zaehl = 0; zaehl < 40; zaehl++){
        Off(2); 
        OnFwd(1,100); 
        delay(10);
        if(analogRead(MITTE_LINKS_PIN)<sw || abbruchVariable == 2){
          abbruchVariable = 2;
          break;
        }
      }
    }
    OnFwd(3,100);
    delay(300);

    while(analogRead(MITTE_LINKS_PIN) > sw && analogRead(MITTE_RECHTS_PIN) > sw){
      OnFwd(2,90);
      OnRev(1,80);   
      analogRead(MITTE_LINKS_PIN);
      analogRead(MITTE_RECHTS_PIN);
    }

    Off(3);
    delay(1000);
    return;

  }
}




