// -*- lsst-c++ -*-
/**
 * Luminous Flux Sensor Interface
 * 
 * See LICENSE file at the top of the source tree.
 * Copyright © 2020 OpenHerb.
*/

#include <Arduino.h>
#include "Lumex.h"

Lumex::Lumex(Spec spec) {
    pin = spec.lx_pin;
    vin = spec.vin;
    sr = spec.sr;
    const CyclicBuffer<uint16_t>::Spec buf_spec = { .name="Lumex Buffer", .buffer_size = spec.buffer_size };
    buffer = new CyclicBuffer<uint16_t>(buf_spec);
    Serial.println("Lumex interface and buffer initialized");
}

Lumex::~Lumex() {
    delete buffer;
    Serial.println("Lumex interface and buffer dereferenced");
}

uint16_t Lumex::read() {
    // read lumex pin
    spv = analogRead(pin);
    // Conversion analog to voltage
    float Vout = static_cast<float>(spv) * (vin / static_cast<float>(1023));
    // Conversion voltage to resistance via voltage dividers
    float RLDR = (RC * (vin - Vout))/Vout;
    // Convert resitance to lumens and push to the buffer
    buffer->push(500/(RLDR/1000));
    return buffer->average();;
}
