#include "SFE_HMC6343.h"
SFE_HMC6343 HMC6343;

void initialize_HMC6343(){
  if (HMC6343.init()){
    HMC6343.setOrientation(LEVEL);
    Serial.println("HMC6343 initialized!");
    }
  else if (!HMC6343.init()){
    Serial.println("HMC6343 failed to initialize!");
    while(1){
      bad_error_led_cycle();
      }
    }
}

float get_heading(){
  HMC6343.readHeading();
  float heading = HMC6343.heading/10.0;

  return heading;
}

float get_pitch(){
  HMC6343.readHeading();
  float pitch = HMC6343.pitch/10.0;
  return pitch;
}

float get_roll(){
  HMC6343.readHeading();
  float roll = HMC6343.roll;
  return roll;
}

void HMC6343_sleep(String state){
  if (state == "ON"){
    HMC6343.enterSleep();    
  }
  else if (state == "OFF"){
    HMC6343.exitSleep();    
  }
}

void reset_HMC6343(){
  HMC6343.reset();
  delay(500);
  initialize_HMC6343();
}

int sn_HMC6343(){
  int sn = HMC6343.readEEPROM(SN_LSB);
  delay(10);
  sn |= (HMC6343.readEEPROM(SN_MSB) << 8);
  delay(10);
  return sn;
}
