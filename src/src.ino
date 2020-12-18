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
#include <Lib1.h>
#include <Lib2.h>

Lib1 lb1("Hello from Lib1!");
Lib2 lb2("Hello from Lib2!");

void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.println("Hello World!");
    Serial.println(lb1.echo());
    Serial.println(lb2.echo());
    delay(1000);
}
