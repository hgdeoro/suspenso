#include <Arduino.h>
#include <WiFiNINA.h>

#include "commons.h"

void dump_received_udp() {
    int packetSize = Udp.parsePacket();

    if (packetSize) {
        Serial.println("There is already a packet!");
    } else {
        Serial.println("Waiting for an UDP packet...");
    }
    while (!packetSize)
        packetSize = Udp.parsePacket();

    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    //    // read the packet into packetBufffer
    //    int len = Udp.read(packetBuffer, 255);
    //    if (len > 0) {
    //        packetBuffer[len] = 0;
    //    }
    //    Serial.println("Contents:");
    //    Serial.println(packetBuffer);
    //
    //    // send a reply, to the IP address and port that sent us the packet we received
    //    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    //    Udp.write(ReplyBuffer);
    //    Udp.endPacket();

}
