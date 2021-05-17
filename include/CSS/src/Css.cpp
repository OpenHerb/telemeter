// -*- lsst-c++ -*-
/**
 * Capacitive Soil Sensor Interface
 * 
 * See COPYRIGHT file at the top of the source tree.
 * Copyright © 2020 OpenHerb.
*/

#include <Arduino.h>
#include "Css.h"

/**
 * @brief Css Constructor
 * 
 * @param spec struct schema
 */
Css::Css(Spec spec) {
    pin = spec.css_pin;
    // initialize cyclic buffer at specified size
    sm_buffer = new uint8_t[spec.buffer_size];
    av = spec.av;
    sv = spec.sv;
    Serial.println("Css interface initialized");
}

/**
 * @brief Css destructor.
 */
Css::~Css(){
    delete sm_buffer;
    Serial.println("Css interface dereferenced");
}

uint8_t Css::read() {
    // read the value from the sensor through the 328p ADC
    smv = analogRead(pin);
    smp = map(smv, av, sv, 0, 100);
    // set bounds to percentage limits
    if (smp >= 100) {
        smp = 100;
    } else if (smp <=0) {
        smp = 0;
    }
    return smp;
}
