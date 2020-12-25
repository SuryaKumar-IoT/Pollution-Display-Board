#define         MQ135PIN                       (34)     //define which analog input channel you are going to use
#define         RL_VALUE_MQ135                 (1)     //define the load resistance on the board, in kilo ohms
#define         RO_CLEAN_AIR_FACTOR_MQ135      (3.59)  //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
#define         CALIBARAION_SAMPLE_TIMES     (50)    //define how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (500)   //define the time interal(in milisecond) between each samples in the
#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interal(in milisecond) between each samples in 
#define         GAS_CARBON_DIOXIDE           (9)
#define         GAS_AMMONIUM                 (10)
#define         GAS_TOLUENE                  (11)
#define         GAS_ACETONE                  (12)
//#define         accuracy                     (0)   //for linearcurves
#define         accuracy                   (1)   //for nonlinearcurves, un comment this line and comment the above line if calculations 
                                                   //are to be done using non linear curve equations
float           Ro2 = 10;                            //Ro is initialized to 10 kilo ohms

float MQ135ResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE_MQ135*(4096-raw_adc)/raw_adc));
}
float MQ135Calibration(int mq_pin)
{
  int i;
  float RS_AIR_val=0,r0;

  for (i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {                     //take multiple samples
    RS_AIR_val += MQ135ResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  RS_AIR_val = RS_AIR_val/CALIBARAION_SAMPLE_TIMES;              //calculate the average value

  r0 = RS_AIR_val/RO_CLEAN_AIR_FACTOR_MQ135;                      //RS_AIR_val divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                                 //according to the chart in the datasheet 

  return r0; 
}

float MQ135Read(int mq_pin)
{
  int i;
  float rs=0;

  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQ135ResistanceCalculation(map(analogRead(mq_pin),0,4096,0,1024));
    delay(READ_SAMPLE_INTERVAL);
  }

  rs = rs/READ_SAMPLE_TIMES;

  return rs;  
}

int MQ135GetGasPercentage(float rs_ro_ratio, int gas_id)
{ 
  if ( accuracy == 0 ) {
  if ( gas_id == GAS_CARBON_DIOXIDE ) {
    return (pow(10,((-2.890*(log10(rs_ro_ratio))) + 2.055)));
  } else if ( gas_id == GAS_AMMONIUM ) {
    return (pow(10,((-2.469*(log10(rs_ro_ratio))) + 2.005)));
  } else if ( gas_id == GAS_TOLUENE ) {
    return (pow(10,((-3.479*(log10(rs_ro_ratio))) + 1.658)));
  } else if ( gas_id == GAS_ACETONE ) {
    return (pow(10,((-3.452*(log10(rs_ro_ratio))) + 1.542)));
  }   
} 

  else if ( accuracy == 1 ) {
    if ( gas_id == GAS_CARBON_DIOXIDE ) {
    return (pow(10,((-2.890*(log10(rs_ro_ratio))) + 2.055)));
  } else if ( gas_id == GAS_AMMONIUM ) {
    return (pow(10,((-2.469*(log10(rs_ro_ratio))) + 2.005)));
  } else if ( gas_id == GAS_TOLUENE ) {
    return (pow(10,((-3.479*(log10(rs_ro_ratio))) + 1.658)));
  } else if ( gas_id == GAS_ACETONE ) {
    return (pow(10,(-1.004*pow((log10(rs_ro_ratio)), 2) - 3.525*(log10(rs_ro_ratio)) + 1.553)));
  }
}    
  return 0;
}

void read_mq135() 
{

   Serial.print("CARBON_DIOXIDE:"); 
   Serial.print(MQ135GetGasPercentage(MQ135Read(MQ135PIN)/Ro2,GAS_CARBON_DIOXIDE) );
   Serial.print( "ppm" );
   Serial.print("    ");   
   Serial.print("AMMONIUM:"); 
   Serial.print(MQ135GetGasPercentage(MQ135Read(MQ135PIN)/Ro2,GAS_AMMONIUM) );
   Serial.print( "ppm" );
   Serial.print("    ");   
   Serial.print("TOLUENE:"); 
   Serial.print(MQ135GetGasPercentage(MQ135Read(MQ135PIN)/Ro2,GAS_TOLUENE) );
   Serial.print( "ppm" );
   Serial.print("    ");   
   Serial.print("ACETONE:"); 
   Serial.print(MQ135GetGasPercentage(MQ135Read(MQ135PIN)/Ro2,GAS_ACETONE) );
   Serial.print( "ppm" );
   Serial.print("\n");
   delay(200);
}
