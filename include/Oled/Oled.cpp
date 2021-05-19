// -*- lsst-c++ -*-
/**
 * @file Oled.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Oled.h"
#include <Wire.h>

/**
 * @brief Construct a new Oled:: Oled object
 * 
 * @param spec constructor specification
 */
Oled::Oled(Spec spec) {
    display = new Adafruit_SSD1306(spec.width, spec.height, &Wire, spec.reset_pin);
    // Start the OLED display
	display->begin(SSD1306_SWITCHCAPVCC, spec.addr);
	display->display();
    Serial.println("OLED Display initialized.");
}

/**
 * @brief Destroy the Oled:: Oled object
 * 
 */
Oled::~Oled() {
    delete display;
    Serial.println("Dereferenced Oled display driver");
}

/**
 * @brief OLED display function for writing telemetry data
 * 
 * @param payload sensor telemetry struct
 */
void Oled::write(Sensorframe telemetry){
	display->clearDisplay();
    display->setTextSize(1);
	display->setTextColor(WHITE);

    display->setCursor(0,0);
    display->println("SOIL");
    display->setCursor(0,10);
    display->println(telemetry.sm);
    display->setCursor(0,20);
    display->println("%");

    display->setCursor(27,0);
    display->println("PRES");
    display->setCursor(27,10);
    display->println(telemetry.pa);
    display->setCursor(27,20);
    display->println("kPa");

    display->setCursor(54,0);
    display->println("TEMP");
    display->setCursor(54,10);
    display->println(telemetry.tp);
    display->setCursor(54,20);
    display->print(static_cast<char>(247));
    display->println("C");

    display->setCursor(81,0);
    display->println("LUX");
    display->setCursor(81,10);
    display->println(telemetry.lx);
    display->setCursor(81,20);
    display->println("Lux");

    display->setCursor(109,0);
    display->println("RH");
    display->setCursor(109,10);
    display->println(telemetry.rh);
    display->setCursor(109,20);
    display->println("%");
	// write to display
	display->display();
}

