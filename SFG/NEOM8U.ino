#include "SparkFun_Ublox_Arduino_Library.h"
SFE_UBLOX_GPS NEOM8U;

void initialize_NEOM8U(){
  if (NEOM8U.begin()==true){
    NEOM8U.setI2COutput(COM_TYPE_UBX); 
    NEOM8U.setNavigationFrequency(1);
    NEOM8U.saveConfiguration();   
    if (NEOM8U_datetime_valid()==true){
      set_PCF8523_from_NEOM8U();
      Serial.println("Reset PCF8523 time to match NEOM8U GPS Module.");
    }
    Serial.println("NEOM8U initialized!");
  }
  else if (NEOM8U.begin()==false){
    Serial.println("NEOM8U did not initialize!");
    while(1){
      bad_error_led_cycle();
    }
  }
}


bool NEOM8U_datetime_valid(){
  if (NEOM8U.getDateValid()==false| NEOM8U.getTimeValid()==false){
    return false;
  }
  else if (NEOM8U.getDateValid()==true & NEOM8U.getTimeValid()==true){
    return true;
  }
}

int get_NEOM8U_year(){int yyyy = NEOM8U.getYear();return yyyy;}
int get_NEOM8U_month(){int mm = NEOM8U.getMonth();return mm;}
int get_NEOM8U_day(){int dd = NEOM8U.getDay();return dd;}
int get_NEOM8U_hour(){int HH = NEOM8U.getHour();return HH;}
int get_NEOM8U_minute(){int MM = NEOM8U.getMinute();return MM;}
int get_NEOM8U_second(){int SS = NEOM8U.getSecond();return SS;}


void reset_NEOM8U(){
  NEOM8U.factoryReset();
  initialize_NEOM8U();
}

double get_latitude(){
  double latitude = NEOM8U.getLatitude();
  latitude = latitude * pow(10,-7);
  return latitude;
}

double get_longitude(){
  double longitude = NEOM8U.getLongitude();
  longitude = longitude * pow(10,-7);
  return longitude;
}

float get_NEOM8U_heading(){
  float heading = NEOM8U.getHeading();
  heading = heading * pow(10,-5);
  return heading;
}

int get_siv(){
  int SIV = NEOM8U.getSIV();
  return SIV;
}
