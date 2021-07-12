#include <Arduino.h>
#include <Arduino_LSM6DS3.h>

#include "commons.h"

void LSM6DS3_run(int iters) {
    LSM6DS3_setup();
    for (int i = 0; i < iters; i++) {
        LSM6DS3_read();
    }
}

void LSM6DS3_setup() {

    if (!IMU.begin()) {
        Serial.println("Failed to initialize IMU! - STOP");
        while (1) {
            delay(1000);
        };
    }

    Serial.print("Accelerometer sample rate = ");
    Serial.print(IMU.accelerationSampleRate());
    Serial.println(" Hz");

    Serial.print("Gyroscope sample rate = ");
    Serial.print(IMU.gyroscopeSampleRate());
    Serial.println(" Hz");

    Serial.println();
    Serial.println("Acceleration in G's / Gyroscope in degrees/second");
    Serial.println("X\tY\tZ");
}

float xacc, yacc, zacc, xgyr, ygyr, zgyr;

void LSM6DS3_read() {
    while (!IMU.accelerationAvailable()) {}
    IMU.readAcceleration(xacc, yacc, zacc);

    while (!IMU.gyroscopeAvailable()) {}
    IMU.readGyroscope(xgyr, ygyr, zgyr);

    Serial.print(xacc);
    Serial.print('\t');
    Serial.print(yacc);
    Serial.print('\t');
    Serial.print(zacc);

    Serial.print('\t');

    Serial.print(xgyr);
    Serial.print('\t');
    Serial.print(ygyr);
    Serial.print('\t');
    Serial.println(zgyr);
}
