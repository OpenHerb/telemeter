// -*- lsst-c++ -*-
/**
 * OpenHerb Telemeter Main
 * 
 * @file src.ino
 *
 * @brief Main event loop for telemetry collection and serial publishing
 *
 * @author Christian Sargusingh
 * 
 * Copyright © 2020 OpenHerb.
 */
#include <SoftwareSerial.h>
#include <Css.h>

uint16_t value;

Css Css;

void setup() {
    // setup serial interface
    Serial.begin(9600);
}


void loop() {
    Serial.print("");
    // Poll sensors
    smp = Css.read();
    // Construct sensorframe
    sensorframe = "SM:" + String(smp) + "|"
    // Publish through serial for digest
    Serial.println(sensorframe);
    delay(1000);
}
