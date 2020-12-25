/*
Developer: Surya Kumar V
Email: surya.kumar@madblocks.tech
Contact No: 91-7799204041

Hardware Used:

1. ESP32
2. Air Quality Sensor [Mq135]
3. DHT11
4. MQ8
5. MQ9
6. LED Display
7. PM2.5 Dust Sensor

Pin Connections

Sensor        ESP32

MQ135[A0]   ----> 34
MQ8[A0]     ----> 32
MQ9[A0]     ----> 35
DHT11[Data] ----> 23
Dust LED[O] ----> 22
Dust A0[Y]  ----> 4

*/

Project Flow

1. Sensor Calibration for MQ8,9,135
2. Waits Untill Its Connects to WiFi Network 
3. Read Data From sensors
4. Format Data of Led Display
5. Updates Sensor Data to Led Display
6. Update thingspeak cloud with new sensor data
7. Wait for  minute for new data

Schematic layout

Colour Code is mention Do wiring According to the Colour Mentioned 
