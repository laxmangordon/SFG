#include <SparkFunBME280.h>
BME280 atm76;  //BME280 at address 0x76.
BME280 atm77;  //BME280 at address 0x77.

float get_internal_humidity(int sensor_address){
  float internal_humidity;
  if (sensor_address == 0x76){
    internal_humidity = atm76.readFloatHumidity();
  }
  else if (sensor_address == 0x77){
    internal_humidity = atm77.readFloatHumidity();   
  }     
  return internal_humidity;  
}

float get_internal_pressure(int sensor_address){
  float internal_pressure;
  if (sensor_address == 0x76){
    internal_pressure = atm76.readFloatPressure();
  }
  else if (sensor_address == 0x77){
    internal_pressure = atm77.readFloatPressure();   
  }     
  return internal_pressure;  
}


float get_internal_temperature(int sensor_address){
  float internal_temperature;
  if (sensor_address == 0x76){
    internal_temperature = atm76.readFloatPressure();
  }
  else if (sensor_address == 0x77){
    internal_temperature = atm77.readFloatPressure();   
  }     
  return internal_temperature;  
}


void initialize_BME280(int sensor_address){
  if (sensor_address == 0x76){
    atm76.setI2CAddress(0x76);
    if (atm76.begin()){
      Serial.println("BME280 at address 0x76 initialized!");
    }
  }
  else if (sensor_address == 0x77){
    atm77.setI2CAddress(0x77);
    if (atm77.begin()){
      Serial.println("BME280 at address 0x77 initialized!");
    }    
  }
  else{
    Serial.print("Unable to initialize sensor at address ");
    Serial.println(sensor_address);
    while(1){
      bad_error_led_cycle();
    }
  }
}


void initialize_BME280s(){
  initialize_BME280(0x76);
  initialize_BME280(0x77);
  set_oversample_BME280(0x76,16);
  set_oversample_BME280(0x77,16);
}


void set_oversample_BME280(int sensor_address,int val){
  if (val < 1 | val > 16){
    Serial.println("ERROR: BME280 oversample value must be between 1-16.");
    while(1){
      bad_error_led_cycle();
    }
  }
  if (sensor_address == 0x76){
    atm76.setTempOverSample(val); 
    atm76.setPressureOverSample(val); 
    atm76.setHumidityOverSample(val); 
  }
  else if (sensor_address == 0x77){
    atm77.setTempOverSample(val); 
    atm77.setPressureOverSample(val); 
    atm77.setHumidityOverSample(val);     
  }   
}
