void setup() 
{
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(200);
  Serial.println();
  Serial.println("Testing Led Board");
  delay(200);
  //format_data();
}

void loop()
{
  update_first_message("<M WELCOME TO Madblocks><S 4><D L1>");
  delay(20000);
  update_message("<M Surya Kumar IoT><S 4><D L1>");
  delay(20000);
  update_message("<M MadBlocks Technologies Pvt LTD><S 4><D L1>");
  delay(20000);
  while(1);
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
