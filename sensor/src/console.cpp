#include <Arduino.h>

#include "commons.h"

// Busy-wait until console is connected. Blink 50ms while waiting.
void wait_for_console() {
    int ledBuiltInValue = HIGH;
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, ledBuiltInValue);

    Serial.begin(9600);

    while (!Serial) {
        ledBuiltInValue = ledBuiltInValue == HIGH ? LOW : HIGH;
        digitalWrite(LED_BUILTIN, ledBuiltInValue);
        delay(50);
    }
    digitalWrite(LED_BUILTIN, HIGH);
}
