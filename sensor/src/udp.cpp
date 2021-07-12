#include <Arduino.h>
#include <WiFiNINA.h>

#include "commons.h"

WiFiUDP Udp;

char buf[100];
char nl[] = "\n";
char sep[] = ",";
String str = "";

unsigned long errors = 0;
unsigned long counter = 0;
unsigned long udpStart;

// Setup Udp object. Required to send packages.
void udp_begin() {
    Udp.begin(4343);
}

void start_stats() {
    counter = 1;
    errors = 0;
    udpStart = millis();
}

void print_progress_stat_line() {
    Serial.println(str + "PROGRESS_STAT | iter=" + counter + " | err=" + errors + " | time="
                   + (millis() - udpStart) + "| msg/sec=" + (counter / ((millis() - udpStart) / 1000.0)));
}

void print_final_stat_line(unsigned int len) {
    Serial.println(str + "ENDED | stats len=" + (len) + " | iter=" + (counter) + " | err=" + errors + " | time="
                   + (millis() - udpStart) + "| msg/sec=" + (counter / ((millis() - udpStart) / 1000.0)));
}

void print_csv_stat_line(unsigned int len) {
    Serial.println(str + "CSV," + len + "," + counter + "," + errors + "," + (millis() - udpStart) + "," +
                   (counter / ((millis() - udpStart) / 1000.0)));
}

struct message {
    unsigned int msg_type;
    unsigned int value;
    unsigned int timestamp;
};

// ==============================================================================================================

// Send one packet to server. Returns `1` for OK.
int send_udp_to_server_single_datapoint_string(char *ip) {

    if (Udp.beginPacket(ip, 4545) != 1) {
        Serial.println("[UDP] Udp.beginPacket() failed");
        return -1;
    }

    String(counter).toCharArray(buf, 100);
    Udp.write(buf);

    Udp.write(sep);

    String(micros()).toCharArray(buf, 100);
    Udp.write(buf);

    Udp.write(nl);

    if (Udp.endPacket() != 1) {
        errors++;
        return -1;
    }

    return 1;
}

void flood_single_datapoint_string(unsigned int iters) {
    start_stats();
    for (; iters == 0 || counter <= iters; counter++) {
        if (counter % 1000 == 0) {
            print_progress_stat_line();
        }
        send_udp_to_server_single_datapoint_string(serverHostname);
    }

    counter--;
    print_final_stat_line(1);
    print_csv_stat_line(1);

}

// ==============================================================================================================

unsigned int timestamp;

int send_udp_to_server_single_datapoint_two_writes(char *ip) {

    if (Udp.beginPacket(ip, 4545) != 1) {
        Serial.println("[UDP] Udp.beginPacket() failed");
        return -1;
    }

    timestamp = micros();

    Udp.write((byte *) &counter, sizeof(unsigned int));
    Udp.write((byte *) &timestamp, sizeof(unsigned int));

    if (Udp.endPacket() != 1) {
        errors++;
        return -1;
    }

    return 1;
}

void flood_single_datapoint_two_writes(unsigned int iters) {
    start_stats();
    for (; iters == 0 || counter <= iters; counter++) {
        if (counter % 1000 == 0) {
            print_progress_stat_line();
        }
        send_udp_to_server_single_datapoint_two_writes(serverHostname);
    }

    counter--;
    print_final_stat_line(1);
    print_csv_stat_line(1);
}

// ==============================================================================================================

//message msg_buff = {1, 0, 0};
//
//
//int send_udp_to_server_single_datapoint_struct(char *ip) {
//
//    if (Udp.beginPacket(ip, 4545) != 1) {
//        Serial.println("[UDP] Udp.beginPacket() failed");
//        return -1;
//    }
//
//    msg_buff.value = counter;
//    msg_buff.timestamp = micros();
//
//    Udp.write((byte *) &msg_buff, sizeof(message));
//
//    if (Udp.endPacket() != 1) {
//        errors++;
//        return -1;
//    }
//
//    return 1;
//}

// ==============================================================================================================

//message msg_buff_array[] = {
//        {0, 0, 0},
//        {0, 0, 0},
//        {0, 0, 0},
//        {1, 0, 0},
//};
//
//int send_udp_to_server_4(char *ip) {
//
//    if (Udp.beginPacket(ip, 4545) != 1) {
//        Serial.println("[UDP] Udp.beginPacket() failed");
//        return -1;
//    }
//
//    msg_buff_array[3].value = counter;
//    msg_buff_array[3].timestamp = micros();
//
//    Udp.write((byte *) &msg_buff_array, sizeof(message) * 4);
//
//    if (Udp.endPacket() != 1) {
//        errors++;
//        return -1;
//    }
//
//    return 1;
//}

// ==============================================================================================================

#define MULTI_ARR_SIZE 128

message msg_buff_multi_array[MULTI_ARR_SIZE];

void msg_buff_multi_array_reset() {
    for (unsigned int i = 0; i < MULTI_ARR_SIZE; i++) {
        msg_buff_multi_array[i].msg_type = (unsigned int) 0;
        msg_buff_multi_array[i].timestamp = (unsigned int) 0;
        msg_buff_multi_array[i].value = (unsigned int) 0;
    }
}

int send_udp_to_server_multiple_datapoint_struct(char *ip, unsigned int len) {
    if (Udp.beginPacket(ip, 4545) != 1) {
        Serial.println("[UDP] Udp.beginPacket() failed");
        return -1;
    }

    msg_buff_multi_array[0].msg_type = len;
    msg_buff_multi_array[0].value = counter;
    msg_buff_multi_array[0].timestamp = micros();

    Udp.write((byte *) &msg_buff_multi_array, sizeof(message) * len);

    if (Udp.endPacket() != 1) {
        errors++;
        return -1;
    }

    return 1;
}

void flood_multiple_datapoint_struct(unsigned int iters) {
    msg_buff_multi_array_reset();

    for (unsigned int len = 1; len <= 140; len++) {
        Serial.print("Flooding with len=");
        Serial.println(len);

        start_stats();

        for (; iters == 0 || counter <= iters; counter++) {
            if (counter % 1000 == 0) {
                print_progress_stat_line();
            }
            send_udp_to_server_multiple_datapoint_struct(serverHostname, len);
        }

        counter--;

        print_final_stat_line(len);
        print_csv_stat_line(len);

    }

}
