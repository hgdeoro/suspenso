#include <Arduino.h>

#include "commons.h"

// Endless loop. Blinks led reporting fatal error (2 seconds).
void fatal_error() {
    int ledBuiltInValue = HIGH;
    while (true) {
        ledBuiltInValue = ledBuiltInValue == HIGH ? LOW : HIGH;
        digitalWrite(LED_BUILTIN, ledBuiltInValue);
        delay(2000);
    }
}
