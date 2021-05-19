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
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_BME280.h>
#include <Lumex.h>
#include <Css.h>
#include <Oled.h>
#include <Types.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_ADDR 0x3C
#define BME_ADDR 0x76
#define H20_PIN 7

// sensor values
const uint16_t loop_delay = 500;

// init sensor interfaces
Css* css;
Lumex* lumex;
Oled* oled;
Adafruit_BME280 bme;

void setup() {
    // setup serial interface
    Serial.begin(9600);
    const Css::Spec css_spec = {
        .css_pin = A6,
        .buffer_size = 5,
        .av = 620,
        .sv = 310
    };
    const Lumex::Spec lumex_spec = {
        .lx_pin = A7,
        .buffer_size = 10,
        .vin = 5,
        .sr = 10000
    };
    const Oled::Spec oled_spec = {
        .width = 128,
        .height = 32,
        .reset_pin = -1,
        .addr = 0x3C
    };
    css = new Css(css_spec);
    lumex = new Lumex(lumex_spec);
    oled = new Oled(oled_spec);
    // relay module output (active high)
    pinMode(H20_PIN, OUTPUT);
    digitalWrite(H20_PIN,HIGH);
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    if (!bme.begin(BME_ADDR)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
}

void loop() {
    // create a new telemetry instance
    Sensorframe telemetry;
    // if ( idx == SAMPLE_SIZE ) {
    //     idx = 0;
    //     digitalWrite(H20_PIN,LOW);
    //     delay(2000);
    //     digitalWrite(H20_PIN,HIGH);
    // }
    // poll sensors (updates internal buffers)
    telemetry.sm = css->read();
    telemetry.lx = lumex->read();
    telemetry.tp = bme.readTemperature();
    telemetry.pa = bme.readPressure()/1000; //kPa
    telemetry.rh = bme.readHumidity();
    // write to OLED display
    oled->write(telemetry);
    publish_sensorframe(telemetry);
    delay(loop_delay);
}

void publish_sensorframe(Sensorframe telemetry) {
    // Construct sensorframe
    String sensorframe = String("TP&") + String(telemetry.tp) + "|" + "RH&" + String(telemetry.rh) + "|" + "PA&" + String(telemetry.pa) + "|" + "SM&" + String(telemetry.sm) + "|" + "LX&" + String(telemetry.lx) + "|";
    // Publish through serial for digest
    Serial.println(sensorframe);
}