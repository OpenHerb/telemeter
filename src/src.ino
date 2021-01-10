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

uint16_t sm;

Css Css;

void setup() {
    // setup serial interface
    Serial.begin(9600);
}


void loop() {
    // Poll sensors
    sm = Css.read();
    // Construct sensorframe
    String sensorframe = String("SM&") + String(sm) + "|";
    // Publish through serial for digest
    Serial.println(sensorframe);
    delay(1000);
}
