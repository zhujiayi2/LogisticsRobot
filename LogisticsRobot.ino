#include <Arduino.h>
#include "ArduinoLog/ArduinoLog.h"

#define BAUD_RATE 9600

void setup() {
    Serial.begin(BAUD_RATE);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);
    Log.infoln("Baud rate: %d", BAUD_RATE);
}

void loop() {
}
