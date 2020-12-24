// -*- lsst-c++ -*-
/**
 * Sample src.ino file (entry point)
 * 
 * @file src.ino
 *
 * @brief Sample source file entry point demonstrating local include calls.
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
    Serial.print("Analog readout: ");
    value = Css.read();
    Serial.println(value);
    delay(1000);
}
