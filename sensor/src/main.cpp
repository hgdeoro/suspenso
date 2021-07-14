// https://www.arduino.cc/en/Reference/WiFiNINA

#include <Arduino.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <Arduino_LSM6DS3.h>

#include "commons.h"

void setup() {
    // wait_for_console();
    // listNetworks();
    connect_to_wifi();
    udp_begin();
}

void loop() {
    int incomingByte = 0; // for incoming serial data
    Serial.println("----------------------------------------");
    Serial.println("a. network info");
    Serial.println("b. ping");

    Serial.println("c. flood_single_datapoint_string() x 10k");
    Serial.println("d. flood_single_datapoint_string() x 200k");
    Serial.println("e. flood_single_datapoint_string() x 1.8m");

    Serial.println("f. flood_single_datapoint_two_writes() x 10k");
    Serial.println("g. flood_single_datapoint_two_writes() x 200k");
    Serial.println("h. flood_single_datapoint_two_writes() x 1.8m");

    Serial.println("i. flood_multiple_datapoint_struct() - multiple sizes x 10");
    Serial.println("j. flood_multiple_datapoint_struct() - multiple sizes x 100");
    Serial.println("k. flood_multiple_datapoint_struct() - multiple sizes x 1k");

    Serial.println("l. flood_fixed_len_datapoint_struct(124)");
    Serial.println("m. flood_fixed_len_datapoint_struct(125)");
    Serial.println("n. flood_fixed_len_datapoint_struct(126)");
    Serial.println("o. flood_fixed_len_datapoint_struct(127)");

    Serial.println("t. LSM6DS3 x 100");
    Serial.println("u. LSM6DS3 x 10_000");
    Serial.println("v. Receive 1 UDP packet");
    Serial.println("----------------------------------------");

    while (true) {
        incomingByte = Serial.peek();
        if (incomingByte == -1) {
            delay(100);
        } else if (incomingByte == '\n') {
            Serial.read();
        } else {
            break;
        }

    }

    incomingByte = Serial.read();

    if (incomingByte == 'a') {
        const long message_id = start_message();
        printWifiData();
        printCurrentNet();
        end_message(message_id);

    } else if (incomingByte == 'b') {
        const long message_id = start_message();
        for (int i = 0; i < 5; i++) {
            ping(serverHostname);
        }
        end_message(message_id);

    } else if (incomingByte == 'c') {
        const long message_id = start_message();
        Serial.println("c. flood_single_datapoint_string() x 10k");
        flood_single_datapoint_string(10000);
        end_message(message_id);

    } else if (incomingByte == 'd') {
        const long message_id = start_message();
        Serial.println("d. flood_single_datapoint_string() x 200k");
        flood_single_datapoint_string(200 * 1000);
        end_message(message_id);

    } else if (incomingByte == 'e') {
        const long message_id = start_message();
        Serial.println("e. flood_single_datapoint_string() x 1.8m");
        flood_single_datapoint_string(1800 * 1000);
        end_message(message_id);

    } else if (incomingByte == 'f') {
        const long message_id = start_message();
        Serial.println("f. flood_single_datapoint_two_writes() x 10k");
        flood_single_datapoint_two_writes(10000);
        end_message(message_id);

    } else if (incomingByte == 'g') {
        const long message_id = start_message();
        Serial.println("g. flood_single_datapoint_two_writes() x 200k");
        flood_single_datapoint_two_writes(200 * 1000);
        end_message(message_id);

    } else if (incomingByte == 'h') {
        const long message_id = start_message();
        Serial.println("h. flood_single_datapoint_two_writes() x 1.8m");
        flood_single_datapoint_two_writes(1800 * 1000);
        end_message(message_id);

    } else if (incomingByte == 'i') {
        const long message_id = start_message();
        Serial.println("i. flood_multiple_datapoint_struct() - multiple sizes x 10");
        flood_multiple_datapoint_struct(10);
        end_message(message_id);

    } else if (incomingByte == 'j') {
        const long message_id = start_message();
        Serial.println("j. flood_multiple_datapoint_struct() - multiple sizes x 100");
        flood_multiple_datapoint_struct(100);
        end_message(message_id);

    } else if (incomingByte == 'k') {
        const long message_id = start_message();
        Serial.println("k. flood_multiple_datapoint_struct() - multiple sizes x 1k");
        flood_multiple_datapoint_struct(1000);
        end_message(message_id);

    } else if (incomingByte == 'l') {
        const long message_id = start_message();
        Serial.println("m. flood_fixed_len_datapoint_struct(124) - x 1");
        flood_fixed_len_datapoint_struct(124, 1);
        end_message(message_id);

    } else if (incomingByte == 'm') {
        const long message_id = start_message();
        Serial.println("m. flood_fixed_len_datapoint_struct(125) - x 1");
        flood_fixed_len_datapoint_struct(125, 1);
        end_message(message_id);

    } else if (incomingByte == 'n') {
        const long message_id = start_message();
        Serial.println("n. flood_fixed_len_datapoint_struct(126) - x 1");
        flood_fixed_len_datapoint_struct(126, 1);
        end_message(message_id);

    } else if (incomingByte == 'o') {
        const long message_id = start_message();
        Serial.println("o. flood_fixed_len_datapoint_struct(127) - x 1");
        flood_fixed_len_datapoint_struct(127, 1);
        end_message(message_id);

    } else if (incomingByte == 't') {
        const long message_id = start_message();
        LSM6DS3_run(100);
        end_message(message_id);

    } else if (incomingByte == 'u') {
        const long message_id = start_message();
        LSM6DS3_run(10000);
        end_message(message_id);

    } else if (incomingByte == 'v') {
        const long message_id = start_message();
        dump_received_udp();
        end_message(message_id);

    } else {
        const long message_id = start_message();
        Serial.println("Invalid option");
        end_message(message_id);
    }
}
