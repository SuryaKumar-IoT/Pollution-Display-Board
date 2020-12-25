#include "ThingSpeak.h"
#include "WiFi.h"
#include "DHT.h"
#include "dust.h"
#include "mq135.h"
#include "mq8.h"
#include "mq9.h"
WiFiClient client;
DHT dht(23,DHT11);
int t,h;
char temp[200];

void setup() 
{
  pinMode(2,OUTPUT);
  pinMode(ledPower,OUTPUT);
  Serial2.begin(9600);
  delay(200);
  dht.begin();
  delay(200);
  Serial.begin(9600);
  Ro = MQCalibration(MQ9PIN);
  Ro1 = MQ8Calibration(MQ8PIN);
  Ro2 = MQ135Calibration(MQ135PIN);
  Ro2=2.511;
  WiFi.begin("surya","surya1827");
  while(WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(2,HIGH);
    delay(50);
    digitalWrite(2,LOW);
    delay(20);
  }
  digitalWrite(2,HIGH);
  delay(200);
  ThingSpeak.begin(client);
  delay(200);
}

void loop()
{
  h = dht.readHumidity();
  t = dht.readTemperature();
  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  int l_pg=MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_LPG);
  int c_m=MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_CARBON_MONOXIDE);
  int met=MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_METHANE);
  int hy=MQ8GetGasPercentage(MQ8Read(MQ8PIN)/Ro1,GAS_HYDROGEN);
  int al=MQ8GetGasPercentage(MQ8Read(MQ8PIN)/Ro1,GAS_ALCOHOL);
  int cd=MQ135GetGasPercentage(MQ135Read(MQ135PIN)/Ro2,GAS_CARBON_DIOXIDE);
  int am=MQ135GetGasPercentage(MQ135Read(MQ135PIN)/Ro2,GAS_AMMONIUM);
  int ace=MQ135GetGasPercentage(MQ135Read(MQ135PIN)/Ro2,GAS_ACETONE);
  read_dust();
  /*Serial.print("Temp:");
  Serial.print(t);
  Serial.print(",Hum:");
  Serial.print(h);
  Serial.print(",LPG:");
  Serial.print(l_pg);
  Serial.print(",Carbon Monoxide:");
  Serial.print(c_m);
  Serial.print(",Methane:");
  Serial.print(met);
  Serial.print(",Hydrogen:");
  Serial.print(hy);
  Serial.print(",Alcohol:");
  Serial.print(al);
  Serial.print(",Carbon Dioxide:");
  Serial.print(cd);
  Serial.print(",Ammonium:");
  Serial.print(am);
  Serial.print(",Acetone:");
  Serial.print(ace);
  Serial.print(",Dust Density:");
  Serial.println(dustDensity);*/
  sprintf(temp,"<M Temperature:%d C Humidity:%d LPG:%d ppm CO:%d ppm CH4:%d ppm H2:%d ppm ALCOHOL:%d ppm CO2:%d ppm NH3:%d ppm ACETONE:%d ppm PM2.5:%f><S 4><D L1>",t,h,l_pg,c_m,met,hy,al,cd,am,ace,dustDensity);
  update_first_message(temp);
  clear_data();
  ThingSpeak.setField(1,t);
  ThingSpeak.setField(2,h);
  ThingSpeak.setField(3,l_pg);
  ThingSpeak.setField(4,c_m);
  ThingSpeak.setField(5,met);
  ThingSpeak.setField(6,hy);
  ThingSpeak.setField(7,al);
  ThingSpeak.setField(8,cd);
  int x=ThingSpeak.writeFields(1269569,"D9W3WT4HOD9NAK5D");
  if(x==200)
  {
    Serial.println("Data Uploaded to thingSpeak");
  }
  else
  {
    Serial.println("Error in Uploading Data");
  }
  delay(2000);
  ThingSpeak.setField(1,am);
  ThingSpeak.setField(2,ace);
  ThingSpeak.setField(3,dustDensity);
  int y=ThingSpeak.writeFields(1269574,"0VIHUC9RXY1U00IE");
  if(y==200)
  {
    Serial.println("Data Uploaded to thingSpeak");
  }
  else
  {
    Serial.println("Error in Uploading Data");
  }
  delay(40000);
  delay(20000);
}
void clear_data()
{
  for(int i=0;i<sizeof(temp);i++)
  {
    temp[i]=0;
    delay(20);
  }
  
}
void update_first_message(String msg)
{
  format_data();
  delay(550);
  SendCommand("*");
  delay(550);
  SendMessage(msg);
  delay(550);
  Serial.println("Message Updated SuccessFully");
}
void update_message(String msgg)
{
  SendCommand("#");
  delay(550);
  Serial2.print("6");
  delay(550);
  Serial2.print("6");
  delay(550);
  SendCommand("*");
  delay(550);
  SendMessage(msgg);
  delay(550);
  Serial.println("Message Updated SuccessFully");
}
void format_data()
{
  SendCommand("#");
  delay(550);
  SendCommand("4");
  delay(550);
  Serial2.print("6");
  delay(550);
  Serial2.print("6");
  delay(550);
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
