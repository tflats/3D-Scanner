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


String charToString(char* chars, int size)
{
  String s = "";
  for(int i = 0; i < size; i++)
  {
    s = s + chars[i];
  }
  return s;
}
