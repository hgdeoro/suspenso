#include <WiFiNINA.h>

#ifndef SENSOR_01_COMMONS_H
#define SENSOR_01_COMMONS_H

void fatal_error();

void flood_single_datapoint_string(unsigned int);

void flood_multiple_datapoint_struct(unsigned int);

void flood_single_datapoint_two_writes(unsigned int iters);

void dump_received_udp();

void LSM6DS3_run(int);

void LSM6DS3_setup();

void LSM6DS3_read();

void ping(String);

void printCurrentNet();

void printWifiData();

void udp_begin();

void wait_for_console();

void connect_to_wifi();

void printMacAddress(byte[]);

void printWifiData();

void printCurrentNet();

void listNetworks();

long start_message();

void end_message(long random_value);

extern char ssid[];
extern char pass[];
extern char serverHostname[];

extern WiFiUDP Udp;

#endif //SENSOR_01_COMMONS_H
