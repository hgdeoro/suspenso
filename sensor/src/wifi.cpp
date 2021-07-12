#include <Arduino.h>
#include <WiFiNINA.h>

#include "commons.h"
#include "arduino_secrets.h"

// Connects to Wifi. Write messages to Serial. Blocks if no wifi module is detected.
void connect_to_wifi() {
    int status = WL_IDLE_STATUS;

    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println("Communication with WiFi module failed!");
        fatal_error();
    }

    String fv = WiFi.firmwareVersion();

    Serial.print("WiFi.firmwareVersion()=");
    Serial.println(fv);

    Serial.print("WIFI_FIRMWARE_LATEST_VERSION=");
    Serial.println(WIFI_FIRMWARE_LATEST_VERSION);

    if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
        Serial.println("Please upgrade the firmware");
        // https://forum.arduino.cc/t/how-to-update-firmware-of-arduino-nano-33-iot/685363
        // https://www.arduino.cc/en/Tutorial/WiFiNINAFirmwareUpdater
    }


    // print your MAC address:
    byte mac[6];
    WiFi.macAddress(mac);
    Serial.print("MAC address: ");
    printMacAddress(mac);

    // attempt to connect to Wifi network:

    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network:
        status = WiFi.begin(ssid, pass);

        // wait 10 seconds for connection:
        for (int i = 0; i < 10 && status != WL_CONNECTED; i++) {
            Serial.println("Still waiting for attempting to connect...");
            delay(500);
        }

        if (status != WL_CONNECTED) {
            listNetworks();
        }

    }

    // you're connected now, so print out the data:
    Serial.print("You're connected to the network");
    printCurrentNet();
    printWifiData();
}
