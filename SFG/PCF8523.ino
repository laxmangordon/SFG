#include "RTClib.h"
RTC_PCF8523 PCF8523;


String get_PCF8523_datetime(){
  char dt_buffer[32];
  DateTime now = PCF8523.now();
  sprintf(dt_buffer,"%04u-%02u-%02uT%02u:%02u:%02u",now.year(),now.month(),now.day(),now.hour(),now.minute(),now.second());
  return String(dt_buffer);
}

int get_unixtime(){
  DateTime now = PCF8523.now();
  int unix =  now.unixtime();
  return unix;
}


void initialize_PCF8523(){
  if (PCF8523.begin()){
    delay(100);
    DateTime now = PCF8523.now();
    if (!PCF8523.initialized()){ //If the RTC lost power and there is a serial connection...
      if (Serial){
        Serial.println("Datetime is not valid. Resetting the clock.");
        PCF8523.adjust(DateTime(F(__DATE__), F(__TIME__)));         
      }
      else if (NEOM8U_datetime_valid()==true){
        set_PCF8523_from_NEOM8U();
      }
      else{
        Serial.println("Datetime is not valid. Please make a serial connection to reset the clock.");
        while(1){
          bad_error_led_cycle();          
        }
      }
    }
    delay(1000);
    Serial.println("PCF8523 initialized!");
  }
  else{
    Serial.println("PCF8523 did not initialize."); 
    while(1){
      bad_error_led_cycle();      
    }
  }
}


void set_PCF8523_from_NEOM8U(){
  int yyyy = get_NEOM8U_year();
  int mm = get_NEOM8U_month();
  int dd = get_NEOM8U_day();
  int HH = get_NEOM8U_hour();
  int MM = get_NEOM8U_minute();
  int SS = get_NEOM8U_second();
  PCF8523.adjust(DateTime(yyyy,mm,dd,HH,MM,SS));
}
