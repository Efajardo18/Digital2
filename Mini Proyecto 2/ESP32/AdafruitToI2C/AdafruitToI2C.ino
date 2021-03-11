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

#define IO_LOOP_DELAY 5000
unsigned long lastUpdate = 0;

AdafruitIO_Feed *counter = io.feed("counter");
AdafruitIO_Feed *LedR = io.feed("LedR");
AdafruitIO_Feed *LedB = io.feed("LedB");

void setup() {
  Serial2.begin(9600);
  //while(! Serial);
  //Serial.print("Connecting to Adafruit IO");
  io.connect();
  counter->onMessage(handleMessage);
  LedR->onMessage(handleLed1);
  LedB->onMessage(handleLed2);
  while(io.status() < AIO_CONNECTED) {
    //Serial.print(".");
    delay(500);
  }
  //Serial.println();
  //Serial.println(io.statusText());
  counter->get();
  LedR->get();
  LedB->get();
}

void loop() {

  io.run();
  while(Serial2.available()){
    char ww = Serial2.read();
    if(char != '\n'){
      qq.concat(ww);
    }
    else{
      Serial.println(qq);
      break;
    }
    Serial2.write(wea);
    }

  if (millis() > (lastUpdate + IO_LOOP_DELAY)) {
   // Serial.print("sending -> ");
    //Serial.println(count);
    counter->save(qq);
    lastUpdate = millis();
  }

}

void handleMessage(AdafruitIO_Data *data) {

  //Serial.print("received <- ");
  //Serial.println(data->value());

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
