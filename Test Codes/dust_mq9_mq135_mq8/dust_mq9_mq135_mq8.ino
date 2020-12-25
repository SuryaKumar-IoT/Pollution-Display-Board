#include "dust.h"
#include "mq135.h"
#include "mq8.h"
#include "mq9.h"
void setup() 
{
  pinMode(ledPower,OUTPUT);
  Serial.begin(9600);
  Serial.print("Calibrating...Mq9\n");                
  Ro = MQCalibration(MQ9PIN);
  Serial.print("Calibration is done...\n"); 
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");
  Serial.print("Calibrating... MQ8\n");                
  Ro1 = MQ8Calibration(MQ8PIN);                       //Calibrating the sensor. Please make sure the sensor is in clean air 
                                                    //when you perform the calibration                    
  Serial.print("Calibration is done...\n"); 
  Serial.print("Ro1=");
  Serial.print(Ro1);
  Serial.print("kohm");
  Serial.print("\n");
  Serial.print("Calibrating...Mq135\n");                
  Ro2 = MQ135Calibration(MQ135PIN);
  Ro2=2.511;//Calibrating the sensor. Please make sure the sensor is in clean air                     
  Serial.print("Calibration is done...\n"); 
  Serial.print("Ro2=");
  Serial.print(Ro2);
  Serial.print("kohm");
  Serial.print("\n");
}

void loop()
{
   int l_pg=MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_LPG);
   int c_m=MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_CARBON_MONOXIDE);
   int met=MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_METHANE);
   int hy=MQ8GetGasPercentage(MQ8Read(MQ8PIN)/Ro1,GAS_HYDROGEN);
   int al=MQ8GetGasPercentage(MQ8Read(MQ8PIN)/Ro1,GAS_ALCOHOL);
   int cd=MQ135GetGasPercentage(MQ135Read(MQ135PIN)/Ro2,GAS_CARBON_DIOXIDE);
   int am=MQ135GetGasPercentage(MQ135Read(MQ135PIN)/Ro2,GAS_AMMONIUM);
   int ace=MQ135GetGasPercentage(MQ135Read(MQ135PIN)/Ro2,GAS_ACETONE);
   read_dust();
   Serial.print("LPG:");
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
   Serial.println(dustDensity);
   delay(5000);
}
