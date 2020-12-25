#include "DHT.h"

DHT dht(23,DHT11);
int t,h,f;
char temp[200];
void setup() 
{
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(200);
  Serial.println();
  Serial.println("Testing Led Board");
  delay(200);
  dht.begin();
  //format_data();
  delay(1000);
}
void loop()
{
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print("Temp:");
  Serial.print(t);
  Serial.print(",Hum:");
  Serial.println(h);
  delay(200);
  sprintf(temp,"<M Tem:%d C><S 4><D U1>",t);
  Serial.println(temp);
  update_first_message(temp);
  for(int i=0;i<sizeof(temp);i++)
  {
    temp[i]=0;
  }
  sprintf(temp,"<M Hum:%d ><S 4><D U1>",h);
  Serial.println(temp);
  update_message(temp);
  for(int i=0;i<sizeof(temp);i++)
  {
    temp[i]=0;
  }
  delay(20000);
  delay(20000);
}

void update_first_message(String msg)
{
  format_data();
  delay(2000);
  SendCommand("*");
  delay(2000);
  SendMessage(msg);
  delay(2000);
  Serial.println("Message Updated SuccessFully");
}
void update_message(String msgg)
{
  SendCommand("#");
  delay(2000);
  Serial2.print("6");
  delay(2000);
  Serial2.print("6");
  delay(2000);
  SendCommand("*");
  delay(2000);
  SendMessage(msgg);
  delay(2000);
  Serial.println("Message Updated SuccessFully");
}
void format_data()
{
  SendCommand("#");
  delay(2000);
  SendCommand("4");
  delay(2000);
  Serial2.print("6");
  delay(2000);
  Serial2.print("6");
  delay(2000);
  Serial.println("SuccessFully Formatted Data");
}
void SendCommand(String chh)
{
  xx:
  //Serial.println(ch);
    Serial2.print(chh);
    delay(20);
    if(Serial2.available()>0)
    {
      goto begin;
    }
    else
    {
      goto xx;
    }
  begin:
    while(!Serial2.available());
    while(Serial2.available()>0)
    {
      String ch=Serial2.readString();
      //Serial.println(ch);
      delay(5);
    }
    Serial2.flush();
    delay(200);
    Serial2.end();
    delay(200);
    Serial2.begin(9600);
    delay(200);
    //Serial.println("Data Read");
}
void SendMessage(String chh)
{
  xx:
  //Serial.println(ch);
    Serial2.println(chh);
    delay(20);
    if(Serial2.available()>0)
    {
      goto begin;
    }
    else
    {
      goto xx;
    }
  begin:
    while(!Serial2.available());
    while(Serial2.available()>0)
    {
      String ch=Serial2.readString();
      //Serial.println(ch);
      delay(5);
    }
    Serial2.flush();
    delay(200);
    Serial2.end();
    delay(200);
    Serial2.begin(9600);
    delay(200);
    //Serial.println("Data Read");
}
