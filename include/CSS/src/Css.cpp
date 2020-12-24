// -*- lsst-c++ -*-
/**
 * Capacitive Soil Sensor Interface
 * 
 * See COPYRIGHT file at the top of the source tree.
 * Copyright © 2020 OpenHerb.
*/

#include <Arduino.h>
#include "Css.h"

uint16_t Css::read() {
    // read the value from the sensor through the 328p ADC
    adc = analogRead(CSS_PIN);
    return adc;
}
