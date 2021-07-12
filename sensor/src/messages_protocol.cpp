#include <Arduino.h>

long start_message() {
    long random_value = random(2147483647);
    Serial.print("<part:");
    Serial.print(random_value);
    Serial.println(">");
    return random_value;
}

void end_message(long random_value) {
    Serial.print("</part:");
    Serial.print(random_value);
    Serial.println(">");
}
