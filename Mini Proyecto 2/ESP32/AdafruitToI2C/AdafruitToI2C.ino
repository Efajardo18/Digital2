// Adafruit IO Publish & Subscribe Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

#include "config.h"

/************************ Example Starts Here *******************************/

int count = 0;
int ledR  = 0;
int ledB  = 0;
int wea   = 0;
String qq = "";
float x;
float y;
float z;

#define IO_LOOP_DELAY 8000
unsigned long lastUpdate = 0;

AdafruitIO_Feed *feedx = io.feed("x");
AdafruitIO_Feed *feedy = io.feed("y");
AdafruitIO_Feed *feedz = io.feed("z");
AdafruitIO_Feed *LedR = io.feed("LedR");
AdafruitIO_Feed *LedB = io.feed("LedB");

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  //while(! Serial);
  //Serial.print("Connecting to Adafruit IO");
  io.connect();
  LedR->onMessage(handleLed1);
  LedB->onMessage(handleLed2);
  while(io.status() < AIO_CONNECTED) {
    //Serial.print(".");
    delay(500);
  }
  //Serial.println();
  //Serial.println(io.statusText());
  LedR->get();
  LedB->get();
  feedx->get();
  feedy->get();
  feedz->get();
}

void loop() {

  io.run();
  Serial2.write(wea);
  while(Serial2.available()){
    char ww = Serial2.read();
    if(ww!= '\n'){
      qq.concat(ww);
    }
    else{
      x=(qq.substring(0,7)).toFloat();
      y=(qq.substring(7,14)).toFloat();
      z=(qq.substring(14,21)).toFloat();
      Serial.println(qq);
      qq="";
      break;
    }
    }

  if (millis() > (lastUpdate + IO_LOOP_DELAY)) {
   // Serial.print("sending -> ");
    //Serial.println(count);
    feedx->save(x);
    feedy->save(y);
    feedz->save(z);
    lastUpdate = millis();
  }

}

void handleLed1(AdafruitIO_Data *data) {

  //Serial.print("receivedLedR <- ");
  if(data->toPinLevel()==HIGH){
    ledR=2;
  }
  else{
    ledR=0;
  }
  wea=ledR+ledB;
  //Serial.println(data->value());

}

void handleLed2(AdafruitIO_Data *data) {

  //Serial.print("receivedLedB <- ");
  if(data->toPinLevel()==HIGH){
    ledB=1;
  }
  else{
    ledB=0;
  }
  wea=ledR+ledB;
  //Serial.println(data->value());

}
