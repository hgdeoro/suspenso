#include <Arduino.h>
#include <WiFiNINA.h>

#include "commons.h"

// Send ping to `pingHostName`, wait for response. Writes messages to Serial.
void ping(String pingHostName) {
    int pingResult;

    Serial.println("");
    Serial.print("Pinging ");
    Serial.print(pingHostName);
    Serial.print("... ");

    pingResult = WiFi.ping(pingHostName);

    if (pingResult >= 0) {
        Serial.print("SUCCESS! RTT = ");
        Serial.print(pingResult);
        Serial.println(" ms");
    } else {
        Serial.print("FAILED! Error code: ");
        Serial.println(pingResult);
    }
}
