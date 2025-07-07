#include "motor.h"
#include <Arduino.h>

#define M1_EN 8 // Need analogue pin, write 0-255 for speed
#define M1_1  5
#define M1_2  6

void motor_init() {
    pinMode(M1_1, OUTPUT);
    pinMode(M1_2, OUTPUT);
}

// TODO check which is which once we get the motor, document connections
void motor_open() {
    digitalWrite(M1_1, HIGH);
    digitalWrite(M1_2, LOW);
}

void motor_close() {
    digitalWrite(M1_2, LOW);
    digitalWrite(M1_1, HIGH);
}