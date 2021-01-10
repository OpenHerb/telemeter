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
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_SSD1306.h>
#include <Lumex.h>
#include <Css.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

//Declaring the display name (display)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// sensor values
uint16_t sm = 0;
uint16_t lx = 0;

// init sensor interfaces
Css Css;
Lumex Lumex;

void write_oled(uint16_t sm, uint16_t lx){
	// frame setup 
	display.clearDisplay();
    display.setTextSize(1);
	display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Soil:");
    display.setTextSize(2);
    display.setCursor(0,18);
    display.println(sm);
    display.setCursor(50,0);
    display.setTextSize(1);
    display.println("Lux:");
    display.setCursor(50,18);
    display.setTextSize(2);
    display.println(lx);
	// write to display
	display.display();
}


void setup() {
    // setup serial interface
    Serial.begin(9600);
    // Start the OLED display
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.display();
}


void loop() {
    // Poll sensors
    sm = Css.read();
    lx = Lumex.read();

    // write to OLED
    write_oled(sm, lx);

    // Construct sensorframe
    String sensorframe = String("SM&") + String(sm) + "|" + "LX&" + String(lx) + "|";
    // Publish through serial for digest
    Serial.println(sensorframe);
    delay(1000);
}
