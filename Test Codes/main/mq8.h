/************************MQ8sensor************************************/
/************************Hardware Related Macros************************************/
#define         MQ8PIN                       (32)     //define which analog input channel you are going to use
#define         RL_VALUE_MQ8                 (1)     //define the load resistance on the board, in kilo ohms
#define         RO_CLEAN_AIR_FACTOR_MQ8      (1)     //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
                                                     //which is derived from the chart in datasheet

/***********************Software Related Macros************************************/
#define         CALIBARAION_SAMPLE_TIMES     (50)    //define how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (500)   //define the time interal(in milisecond) between each samples in the
                                                     //cablibration phase
#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interal(in milisecond) between each samples in 
                                                     //normal operation

/**********************Application Related Macros**********************************/
#define         GAS_HYDROGEN                 (0)
#define         GAS_ALCOHOL                  (4)
#define         accuracy                     (0)   //for linearcurves
//#define         accuracy                   (1)   //for nonlinearcurves, un comment this line and comment the above line if calculations 
                                                    //are to be done using non linear curve equations
/*****************************Globals***********************************************/
float           Ro1 = 10;                            //Ro is initialized to 10 kilo ohms


float MQ8ResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE_MQ8*(4096-raw_adc)/raw_adc));
}

float MQ8Calibration(int mq_pin)
{
  int i;
  float RS_AIR_val=0,r0;

  for (i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {                     //take multiple samples
    RS_AIR_val += MQ8ResistanceCalculation(map(analogRead(mq_pin),0,4096,0,1024));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  RS_AIR_val = RS_AIR_val/CALIBARAION_SAMPLE_TIMES;              //calculate the average value

  r0 = RS_AIR_val/RO_CLEAN_AIR_FACTOR_MQ8;                      //RS_AIR_val divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                                 //according to the chart in the datasheet 

  return r0; 
}
float MQ8Read(int mq_pin)
{
  int i;
  float rs=0;

  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQ8ResistanceCalculation(map(analogRead(mq_pin),0,4096,0,1024));
    delay(READ_SAMPLE_INTERVAL);
  }

  rs = rs/READ_SAMPLE_TIMES;

  return rs;  
}
int MQ8GetGasPercentage(float rs_ro_ratio, int gas_id)
{ 
  if ( accuracy == 0 ) {
  if ( gas_id == GAS_HYDROGEN ) {
    return (pow(10,((-2.568*(log10(rs_ro_ratio))) + 0.360)));
  } else if ( gas_id == GAS_ALCOHOL ) {
    return (pow(10,((-14.45*(log10(rs_ro_ratio))) + 2.001)));
  }   
} 

  else if ( accuracy == 1 ) {
    if ( gas_id == GAS_HYDROGEN ) {
    return (pow(10,((-2.568*(log10(rs_ro_ratio))) + 0.360)));
  } else if ( gas_id == GAS_ALCOHOL ) {
    return (pow(10,(-16078*pow((log10(rs_ro_ratio)), 4) - 5066*pow((log10(rs_ro_ratio)), 3) - 541.7*pow((log10(rs_ro_ratio)), 2) - 36.87*(log10(rs_ro_ratio)) + 1.717)));
  } 
}    
  return 0;
}

void read_mq8()
{

   Serial.print("HYDROGEN:"); 
   Serial.print(MQ8GetGasPercentage(MQ8Read(MQ8PIN)/Ro1,GAS_HYDROGEN) );
   Serial.print( "ppm" );
   Serial.print("    ");   
   Serial.print("ALCOHOL:"); 
   Serial.print(MQ8GetGasPercentage(MQ8Read(MQ8PIN)/Ro1,GAS_ALCOHOL) );
   Serial.print( "ppm" );
   Serial.print("\n");
   delay(200);
}
