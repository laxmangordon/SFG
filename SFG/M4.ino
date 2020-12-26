
 
#include <Wire.h>
#include <SPI.h>
#include "Adafruit_NeoPixel.h"
Adafruit_NeoPixel neopixel(1,8,NEO_GRB + NEO_KHZ800);

void initialize_neopixel(){
  neopixel.begin();
  neopixel.setBrightness(16);
  neopixel.clear();
  neopixel.show();
}

void neopixel_color(char color){
  neopixel.clear();
  switch (color){
    case 'R':{ //Red
      neopixel.setPixelColor(0,255,0,0);  
      break;    
    }
    case 'G':{ //Green
      neopixel.setPixelColor(0,0,255,0);  
      break;     
    }
    case 'B':{ //Blue
      neopixel.setPixelColor(0,0,0,255);   
      break;    
    }
    case 'Y':{ //Yellow
      neopixel.setPixelColor(0,255,255,0);  
      break;     
    }
    case 'O':{ //Orange
      neopixel.setPixelColor(0,255,165,0);   
      break;    
    }
    case 'M':{ //Magenta
      neopixel.setPixelColor(0,255,0,255); 
      break;     
    }
    case 'C':{ //Cyan
      neopixel.setPixelColor(0,0,255,255);    
      break;   
    }
    case 'S':{ //Silver
      neopixel.setPixelColor(0,192,192,192); 
      break;      
    }    
  }
  neopixel.show();
}

void neopixel_off(){
  neopixel.clear();
  neopixel.show();
}

void power_board_led(String state){
  pinMode(LED_BUILTIN, OUTPUT);
  if (state == "ON"){
    digitalWrite(LED_BUILTIN, HIGH);   
  }
  else if (state == "OFF"){
    digitalWrite(LED_BUILTIN,LOW);
  }
}

float get_battery_voltage(){
  float v = analogRead(A6);
  v *= 2;
  v *= 3.3;
  v /= 1024;
  return v;
}


void bad_error_led_cycle(){
  neopixel_color('R');
  power_board_led("OFF");
  delay(1000);
  neopixel_off();
  power_board_led("ON");
  delay(1000);
}


void wait_led_cycle(){
  power_board_led("OFF");
  neopixel_color('M');
  delay(1000);
  neopixel_off();
  delay(1000);
}


void initialize_board(int bps, int i2c_clock){
  Serial.begin(bps);
  Wire.begin();  
  initialize_neopixel();
  neopixel_color('C');
  delay(1000);
  Wire.setClock(i2c_clock); 
  neopixel_off();
  Serial.println("Board initialized!");
}


void wait_for_serial(int seconds){
  while(!Serial){
    wait_led_cycle();
    if (millis() > seconds*1000){
      break;
    }
  }
  neopixel_off();
  power_board_led("OFF");
  Serial.println("------------------------------------------------------------");
}
