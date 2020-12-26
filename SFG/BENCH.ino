void bench_mode(){
  neopixel_color('B');
  power_board_led("OFF");
  while(Serial){
    char cmd = Serial.read();
    switch(cmd){
      case 'W':{
        where();
        break;
      }
      case '\\':{
        Serial.println("Engine moving aft.");
        break;
      }
      case '/':{
        Serial.println("Engine moving forward.");
        break;
      }
      case '|':{
        Serial.println("Engine moving to neutral.");
        break;
      }
    }
  }
}


void where(){
  Serial.println("Gathering summary data...");
  String gps_flag;
  double lat = get_latitude();
  double lon = get_longitude();
  float hdg = get_NEOM8U_heading();
  float vbatt = get_battery_voltage();
  int siv = get_siv();
  String dt = get_PCF8523_datetime();
  if (NEOM8U_datetime_valid()==true){
    gps_flag = "VALID";
    }
  else if (NEOM8U_datetime_valid()==false){
    gps_flag = "INVALID";
    }
  Serial.println("Glider: " + ID);
  Serial.println("RTC Time: " + dt);
  Serial.println("GPS: " + gps_flag);
  Serial.println("Latitude: " + String(lat) + "  |  Longitude: " + String(lon) + "  |  Heading: " +  String(hdg));
  Serial.println("Satellite In View: " + String(siv));
  Serial.println("Voltage At Battery Pin: " + String(vbatt));
}
