// der US-Sensor liegt auf dem Pin
// USvorne bzw
// UShinten
int getUSDistInCm(int pin){
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration;
  int cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(15);
  digitalWrite(pin, LOW);
  delayMicroseconds(20);
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pin, INPUT);
  duration = pulseIn(pin, HIGH, 30000ul);
  cm = duration / 58; //microsecondsToCentimeters(duration);
  if(cm <= 0) cm = 999;
  //if(cm != oldDist){
   Serial.print(cm);
   Serial.print("u ");
  //}
  return cm;
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

int microsecondsToCentimeters(long microseconds)
{

  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return (int)(microseconds / 29 / 2);
}

