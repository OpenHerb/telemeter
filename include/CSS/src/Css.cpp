// -*- lsst-c++ -*-
/**
 * Capacitive Soil Sensor Interface
 * 
 * See COPYRIGHT file at the top of the source tree.
 * Copyright © 2020 OpenHerb.
*/

#include <CyclicBuffer.h>
#include <Arduino.h>
#include "Css.h"

/**
 * @brief Construct a new Css:: Css object
 * 
 * @param spec constructor spec
 */
Css::Css(Spec spec) {
    pin = spec.css_pin;
    // initialize cyclic buffer at specified size
    av = spec.av;
    sv = spec.sv;
    const CyclicBuffer<uint8_t>::Spec buf_spec = { .name="Css Buffer", .buffer_size = spec.buffer_size };
    buffer = new CyclicBuffer<uint8_t>(buf_spec);
    Serial.println("Css interface and buffer initialized");
}

/**
 * @brief Destroy the Css:: Css object
 * 
 */
Css::~Css(){
    delete buffer;
    Serial.println("Css interface and buffer dereferenced");
}

/**
 * @brief Convert analog voltage at the sense pin to moisture percentage push and read buffer avg
 * 
 * @return uint8_t 
 */
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
    buffer->push(smp);
    return buffer->average(); 
}
