#include <AFMotor.h>
#include "Wire.h"


#define trigpin 9
#define echopin 10
const int accellADDR = 0x68;

int16_t gyrox, gyroy;
char tmp_str[2];
char *int16_str(int16_t i, char str)
{
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

AF_Stepper steppx(200, 1); // (steps per rev, which slot)
AF_Stepper steppy(200, 2);


float getDistance()
{
  // first part is the signal out
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  // this is the amount of time the echopin gets a pulseIn
  float duration = pulseIn(echopin, HIGH);
  return (duration / 2) * 0.0342;
}

float getAvDistance(int n)
{
  float total = 0;
  for(int i = 0; i < n; i++)
  {
    total+=getDistance();
  }
  return total/n;
}



void setup()
{
  Serial.begin(9600);
  Serial.println("Stepper test!");

  Wire.begin();
  Wire.beginTransmission(accellADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);


  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  steppx.setSpeed(1);  // 20 rpm
  steppy.setSpeed(1);

}

void loop()
{
  //Serial.println(getAvDistance(4));

  Wire.beginTransmission(accellADDR);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(accellADDR, 2*2, true);
  gyrox = Wire.read() << 8 | Wire.read();
  gyroy = Wire.read() << 8 | Wire.read();
  Serial.print("\nGyro x:");
  Serial.println(int16_str(gyrox, tmp_str));
  Serial.print("Gyro y: ");
  Serial.println(int16_str(gyroy, tmp_str));

  /*
  steppy.onestep(BACKWARD, SINGLE); // keeps stepp_y upright

  for(int i = 0; i < 50 ; i++)
  {
    Serial.print(i);
    steppx.onestep(FORWARD, SINGLE);

    /*  collect data
        into datbuf
    */
  /*
    delay(350);
  }

  steppy.onestep(BACKWARD, SINGLE);

  /*  send datbuf to
      the esp
      then clear datbuf
  */
  delay(3000);
/*
  for(int i = 0; i < 50 ; i++)
  {
   Serial.print(i);

   steppx.onestep(BACKWARD, SINGLE);
   /*  collect data
       into datbuf
   */
 /*
   delay(350);
  }
  /*  send datbut to Serial
      clear datbuf
  */
/*
  steppy.onestep(BACKWARD, SINGLE);
  delay(1000);
 */
}
