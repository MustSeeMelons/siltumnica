#include "temp.h"

#include <DallasTemperature.h>
#include <OneWire.h>

#define TEMP_BUS 4

static OneWire oneWire(TEMP_BUS);

static DallasTemperature sensors(&oneWire);

void temp_init() {
    pinMode(TEMP_BUS, INPUT_PULLUP);
    sensors.begin();
}

float temp_get() {
    sensors.requestTemperatures();

    float t = sensors.getTempCByIndex(0);

    return t;
}