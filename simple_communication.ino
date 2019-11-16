/*
this goes to the ARDUINO
it will get an float, for the distance.
then convert that float to an array of bytes
then send it over the serial1 line to the
esp.
*/
#define trigpin 9
#define echopin 10


void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial.println(":simple communications:");
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
}

void loop()
{
    if((Serial1.availableForWrite() > 60))
    {
      float distance =  getAvDistance(3);
      byte * b = (byte *) &distance;
      b[0] = '1';
      Serial2.write(b, 4);
      Serial.println(b[0]);
      Serial.println(b[1]);
      Serial.println(b[2]);
      Serial.println(b[3]);
      Serial.println("hello");
      delay(1000);
    }
    else
    {
      Serial.println("its full");
    }
    delay(3000);
}
