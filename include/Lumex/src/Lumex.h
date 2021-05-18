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
#include <Arduino.h>
#include <CyclicBuffer.h>

/**
 * @brief Luminous Flux Sensor Interface
 * 
 */
class Lumex {
    public:
        // Lumex constructor specification
        struct Spec {
            uint8_t lx_pin;                 // lumex sense pin
            uint8_t buffer_size;            // buffer size
            uint8_t vin;                    // voltage on pullup
            uint16_t sr;                    // resistor grounded on sense pin
        };
        explicit Lumex(Spec spec);
        ~Lumex();
        uint16_t read();
    
    private:
        CyclicBuffer<uint16_t>* buffer;
        uint8_t pin;                        // lumex pin
        uint8_t vin;                        // voltage on pullup 
        uint16_t sr;                        // resistor grounded on sense pin
        uint16_t spv = 0;                   // analog sense pin voltage reading
};
#endif  // INCLUDE_LUMEX_SRC_LUMEX_H_