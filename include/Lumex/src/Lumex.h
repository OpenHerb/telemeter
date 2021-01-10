// -*- lsst-c++ -*-
/**
 * Lumex : Luminosity Sensor Inteface
 * 
 * See LICENSE file at the top of the source tree.
 * Copyright © 2020 OpenHerb.
 * 
 * @file Lumex.h
 *
 * @brief Luminous Flux sensor interface
 *
 * @ingroup Lumex
 *
 * @author Christian Sargusingh
 * Contact: christian@leapsystems.online
 */

#ifndef INCLUDE_LUMEX_SRC_LUMEX_H_
#define INCLUDE_LUMEX_SRC_LUMEX_H_
#define VIN 5 // V power voltage
#define RC 10000 // constant resistor for voltage divider
#define LX_PIN A7 // A0-A7 are ADC pins on the 328p
#include <Arduino.h>

class Lumex {
    public:
        uint16_t read();
    
    private:
        // voltage levels calibrated by sensor
        uint16_t lxv = 0; // analog voltage reading
        uint16_t lux = 0; // soil moisture as a percentage
};
#endif  // INCLUDE_LUMEX_SRC_LUMEX_H_