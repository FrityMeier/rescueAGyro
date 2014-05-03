
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
