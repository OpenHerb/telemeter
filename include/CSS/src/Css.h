// -*- lsst-c++ -*-
/**
 * Capacitive Soil Sensor
 * 
 * See COPYRIGHT file at the top of the source tree.
 * Copyright © 2020 OpenHerb.
 * 
 * @file css.h
 *
 * @brief This is a sample library
 *
 * @ingroup css
 *
 * @author Christian Sargusingh
 * Contact: christian@leapsystems.online
 */

#ifndef INCLUDE_CSS_SRC_CSS_H_
#define INCLUDE_CSS_SRC_CSS_H_
#define CSS_PIN A6 // A0-A7 are ADC pins on the 328p
#include <Arduino.h>


class Css {
    public:
        // CSS constructor specification
        struct Spec {
            uint8_t css_pin;        // analog pin for css sensor
            uint8_t buffer_size;    // size of cyclic buffer for averaging
            uint16_t av;            // voltage reading in air
            uint16_t sv;            // voltage reading H20 submerged
        };
        explicit Css(Spec spec);
        ~Css();
        uint8_t read();
    
    private:
        static uint8_t *sm_buffer;  // soil moisture cyclic buffer
        uint16_t av = 620;          // voltage calibrated to air
        uint16_t sv = 310;          // voltage calibrated submerged
        uint8_t pin;                // css pin
        uint16_t smv = 0; // analog voltage reading
        uint8_t smp = 0; // soil moisture as a percentage
};
#endif  // INCLUDE_CSS_SRC_CSS_H_
