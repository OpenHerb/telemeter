// -*- lsst-c++ -*-
/**
 * Luminous Flux Sensor Interface
 * 
 * See LICENSE file at the top of the source tree.
 * Copyright © 2020 OpenHerb.
*/

#include <Arduino.h>
#include "Lumex.h"

uint16_t Lumex::read() {
    // read lumex pin
    lxv = analogRead(LX_PIN);
    // Conversion analog to voltage
    float Vout = static_cast<float>(lxv) * (VIN / static_cast<float>(1023));
    // Conversion voltage to resistance via voltage dividers
    float RLDR = (RC * (VIN - Vout))/Vout;
    lux = 500/(RLDR/1000); // Conversion resitance to lumen
    return lux;
}
