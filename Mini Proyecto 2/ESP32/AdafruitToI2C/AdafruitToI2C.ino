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

#define IO_LOOP_DELAY 5000
unsigned long lastUpdate = 0;

AdafruitIO_Feed *counter = io.feed("counter");

void setup() {
  Serial.begin(115200);
  while(! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  counter->onMessage(handleMessage);
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());
  counter->get();
}

void loop() {

  io.run();

  if (millis() > (lastUpdate + IO_LOOP_DELAY)) {
    Serial.print("sending -> ");
    Serial.println(count);
    counter->save(count);
    count++;
    lastUpdate = millis();
  }

}
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->value());

}
