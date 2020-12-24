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
        uint16_t read();
    
    private:
        uint16_t adc;
};
#endif  // INCLUDE_CSS_SRC_CSS_H_
