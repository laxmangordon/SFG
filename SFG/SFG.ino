String ID="GLIDER NAME HERE";

void setup() {
  initialize_board(115200,400000);
  wait_for_serial(30);
  initialize_PCF8523(); //RTC
  initialize_SD(10);
  //initialize_HMC6343(); //Compass
  //initialize_BME280s(); //Internal atmo sensors.
  //initialize_NEOM8U();  //GPS-Dead Reckoning
  //initialize_VL6180();
  delay(1000);
}

void loop() {
  delay(100);
}
