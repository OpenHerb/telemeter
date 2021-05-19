// -*- lsst-c++ -*-
/**
 * @file Oled.h
 * @author Christian Sargusingh (christian@leapsystems.online)
 * @brief Adafruit SSD1306 wrapper for displaying telemetry data. 
 * @version 0.1
 * @date 2021-05-19
 * 
 * @copyright Copyright (c) 2021 OpenHerb
 * 
 */

#ifndef INCLUDE_OLED_OLED_H_
#define INCLUDE_OLED_OLED_H_
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Types.h>

/**
 * @brief Adafruit SSD1306 wrapper for displaying telemetry data.
 * 
 */
class Oled {
    public:
        struct Spec {
            uint8_t width;      // display width in pixels
            uint8_t height;     // display height in pixels
            uint8_t reset_pin;  // reset pin # (-1 if sharing arduino reset pin)
            uint8_t addr;       // display i2c bus address
        };
        explicit Oled(Spec spec);
        ~Oled();
        void write(Sensorframe telemetry);

    private:
        Adafruit_SSD1306* display;
};

#endif // INCLUDE_OLED_OLED_H_