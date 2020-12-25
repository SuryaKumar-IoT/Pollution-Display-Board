void setup()
{
  Serial2.begin(9600);
  Serial.begin(9600);
  Serial.println();
  Serial.println("LED DISPLAY BOARD TEST");
  delay(500);
  format_data();
}

void loop()
{
  
}
void format_data()
{
  Serial.println("Entering Into Write Mode");
  sendCommand("#");
  delay(200);
  Serial.println("Format Data");
  sendCommand("3");
  delay(200);
  Serial.println("Exit from Write Mode");
  Serial2.print("6");
  delay(200); 
}
void sendCommand(String chh)
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
    Serial.println(ch);
    delay(5);
  }
}
void sendMessage(String msg)
{
  xx:
  //Serial.println(ch);
  Serial2.println(msg);
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
    Serial.println(ch);
    delay(5);
  }
}
