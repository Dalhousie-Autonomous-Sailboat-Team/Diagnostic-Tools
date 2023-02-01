#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#include "Adafruit_INA219.h"

#define VERBOSE

#define SD_PIN 10 // Whatever pin the SD need to be connected to
#define VOLT_AMP_PRECISION 0
#define AMP_ONLY_PRECISION 0

typedef struct SensorData{
  float shunt_v;  // mV
  float bus_v;    // V
  float load_v;   // Calculated
  float current;  // mA
  float power;    // mW
}SensorData_t;

void updateData(void);
void SDLog(void);

File myFile;
Adafruit_INA219 INA;
SensorData_t sensorData = {0};
const long interval = 1000; // 1 s
long lastWriteTime = 0;

void setup() {
  
  Serial.begin(9600);
  while(!Serial);

  Serial.println("Debug Port Intialzed");

  Serial.println("Initializing SD Card");

  if(!SD.begin(SD_PIN)){
    Serial.println("Failed to initialize SD Card \nCheck Pin Config");
    while(1);
  }else{
  
  }

  if(myFile = SD.open("SolarPanelData.txt", FILE_WRITE)){
    Serial.println("Failed to open SD File");
    while(1);
  }

  myFile.println("Time (ms),Shunt Voltage (mV),Bus Voltage (V),Load Voltage (V),Current (mA),Power (mW)");
  myFile.close();
  if(!INA.begin()){
    Serial.println("Failed to Initialize INA219 Sensor");
  }
  // To use a lower 16V, 400mA range (higher precision on volts and amps)
  #ifdef VOLT_AMP_PRECISION 
  Serial.println("ina219 using 16V, 400mA configuration"); 
  INA.setCalibration_16V_400mA();
  #endif
  // To use a slightly lower 32V, 1A range (higher precision on amps)
  #ifdef AMP_ONLY_PRECISION //
  Serial.println("ina219 using 32V, 1A configuration"); 
  INA.setCalibration_32V_1A();
  #endif

  #if !defined(VOLT_AMP_PRECISON) && !defined(AMP_ONLY_PRECISON)
  Serial.println("Using ina219 default configuration");
  #endif
  
  sensorData.shunt_v  = 0;
  sensorData.bus_v    = 0;
  sensorData.load_v   = 0;
  sensorData.current  = 0;
  sensorData.power    = 0;
  
  Serial.println("Setup succesfully complete");
  Serial.println("Starting data acqusistion");
}


void loop() {

  // Using Mega's RTC to log every second
  if((millis() - lastWriteTime) > interval){ 
    updateData();
    SDLog();
    lastWriteTime = millis();
  }
  // Check for the exit command
  if(Serial.available() > 0){
    String temp = Serial.readString();
    temp.trim();
    if(temp = "quit"){
      Serial.println("Quit Command ACK");
      myFile.close();
      Serial.println("Data File Closed\nOk to power off ...");
      while(1);
    }else Serial.println("Invalid Command >>" + temp + "<<");
  }
}


void updateData(void){
  
  sensorData.shunt_v  = INA.getShuntVoltage_mV();
  sensorData.bus_v    = INA.getBusVoltage_V();
  sensorData.power    = INA.getPower_mW();
  sensorData.current  = INA.getCurrent_mA();
  sensorData.load_v   = sensorData.bus_v + (sensorData.shunt_v / 1000);

  return;
}

void SDLog(void){
  String buffer;
  
  //SensorData_t * tmp;
  //tmp = &sensorData;
  
  //buffer = String(millis()) + "," + String(sensorData.shunt_v) + "," + String(sensorData.bus_v) + "," + String(sensorData.load_v) + "," + String(sensorData.current) + "," + String(sensorData.power)); 
  
  #ifdef VERBOSE
 
  Serial.print(sensorData.shunt_v);
  Serial.print(",");
  Serial.print(sensorData.bus_v);
  Serial.print(",");
  Serial.print(sensorData.power);
  Serial.print(",");
  Serial.print(sensorData.current);
  Serial.print(",");
  Serial.println(sensorData.load_v);
   
     
  
  #endif
  if(myFile = SD.open("SolarPanelData.txt", FILE_WRITE)){
    myFile.print(sensorData.shunt_v);
    myFile.print(",");
    myFile.print(sensorData.bus_v);
    myFile.print(",");
    myFile.print(sensorData.power);
    myFile.print(",");
    myFile.print(sensorData.current);
    myFile.print(",");
    myFile.print(sensorData.load_v); 
    myFile.close();
  }
  return;
}
