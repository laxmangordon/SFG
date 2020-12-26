#include <SparkFun_VL6180X.h>
VL6180x VL6180(0x29);


void initialize_VL6180(){
  if(VL6180.VL6180xInit()){
    Serial.println("VL6180 initialized!");
  }
  else if(!VL6180.VL6180xInit()){
    Serial.println("VL6180 failed to initialize!");
    while(1){
      bad_error_led_cycle();
      }
  }
}

float get_ambient_light(){
  float lux = VL6180.getAmbientLight(GAIN_20);
  return lux;
}

float get_range(){
  float range = VL6180.getDistance();
  return range;
}
