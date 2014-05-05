
#include <L3G.h>

L3G gyro;

void drehen_begin(){ drehen_begin(false); }
void drehen_begin(boolean test){
  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();
  
  if(test == true){
    Serial.println("Test drehen:");
    OnFwd(1, 100);
    OnRev(2, 100);
    drehen_herum();
    Off(3);
    delay(1000);
   
    while(1==1){
      gyro.read();
      Serial.print("G ");
      Serial.print("X: ");
      Serial.print((int)gyro.g.x);
      Serial.print(" Y: ");
      Serial.print((int)gyro.g.y);
      Serial.print(" Z: ");
      Serial.println((int)gyro.g.z);
      delay(100);
    }
  }
}

void drehen_herum(){
  long Nullwert = 0;
  for(int n=0; n<10; n++){
    gyro.read();  
    Nullwert += (long)gyro.g.z;
    delay(1);
  }
  Nullwert /= 10;
  long summe = 0; 
  while(summe<8500000l){
    gyro.read();  
    summe += ((long)gyro.g.z-Nullwert);
    delay(1);
  }
}
