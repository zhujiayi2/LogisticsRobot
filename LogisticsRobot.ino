#include <Arduino.h>
#include "ArduinoLog/ArduinoLog.h"

void setup() {
    Serial.begin(9600);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);

    // Log test, will be removed in the future.
    Log.errorln("Log as Error with binary values: %b, %B", 23, 345808);
    Log.warning(F("Log as Warning with integer values from Flash: %d, %d" CR), 34, 799870);
}

void loop() {
}
