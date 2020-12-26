#include <SD.h>
#include <stdio.h>
#include <stdarg.h>



void initialize_SD(int cs){
  pinMode(cs,OUTPUT);
  if (SD.begin(cs)){
    make_data_directory();
    Serial.println("SD module initialized!");
  }
  else if(!SD.begin(cs)){
    Serial.println("SD module did not initialize!");
    while(1){
      bad_error_led_cycle();
    }
  }
}


void set_file_creation_datetime(uint16_t* date, uint16_t* time){
  DateTime now = PCF8523.now();
  *date = FAT_DATE(now.year(), now.month(), now.day());
  *time = FAT_TIME(now.hour(), now.minute(), now.second());
}


void make_data_directory(){
    DateTime now = PCF8523.now();
    String yyyy = String(now.year());
    SD.mkdir(yyyy);  
    Serial.println("Moving to root/" + yyyy + ".");  
}

String make_datetime_filename(){
  DateTime now = PCF8523.now();  
  char name_buffer[32];
  sprintf(name_buffer,"%02u%02u%02u%02u",now.month(),now.day(),now.hour(),now.minute());  
  String filename = String(name_buffer);
  return filename;
}


String make_file(String filename, String extension){
  DateTime now = PCF8523.now();
  String fullname = filename + extension;
  String filepath = String(now.year()) + "/" + fullname;
  File file = SD.open(filepath,FILE_WRITE);
  if (file){
    SdFile::dateTimeCallback(set_file_creation_datetime);    
    Serial.println("File successfully created at " + filepath + ".");
    file.close();  
  }
  return filepath;
}
