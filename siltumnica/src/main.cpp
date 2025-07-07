#include <Arduino.h>

#include <avr/sleep.h>
#include <avr/wdt.h>

#include "motor.h"
#include "temp.h"

#define SLEEP_LOOPS 1

volatile bool is_awake = false;

ISR(WDT_vect) {
    is_awake = true;
}

void sleep() {
    for (int i = 0; i < SLEEP_LOOPS; i++) {
        is_awake = false;

        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();

        // Enable watchdog events, we need to set `Watchdog System Reset Enable` temporarily
        WDTCSR = (1 << WDCE) | (1 << WDE);
        // Enable interrupt, set timeout to 8s (WDP are prescaler bits)
        WDTCSR = (1 << WDIE) | (1 << WDP3) | (1 << WDP0);

        sleep_cpu();

        // Need to disable, otherwise we shall go back to sleep
        sleep_disable();

        while (!is_awake)
            ; // Wait for WDT
    }
}

void setup() {
    temp_init();

    Serial.begin(9600);
}

// TODO de-solder PWR led
void loop() {
    float t = temp_get();

    Serial.print("Celsius temperature: ");
    Serial.println(t);

    sleep();
}
