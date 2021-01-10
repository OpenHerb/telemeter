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
    smv = analogRead(CSS_PIN);
    smp = map(smv, av, wv, 0, 100);
    // set bounds to percentage limits
    if (smp >= 100) {
        smp = 100;
    } else if (smp <=0) {
        smp = 0;
    }
    return smp;
}
