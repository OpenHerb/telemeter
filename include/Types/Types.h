/**
 * @file Types.h
 * @author Christian Sargusingh (christian@leapsystems.online)
 * @brief Telemeter Project typedefs
 * @version 0.1
 * @date 2021-05-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef INCLUDE_TYPES_TYPES_H_
#define INCLUDE_TYPES_TYPES_H_

struct Sensorframe {
    uint8_t sm;         // soil moisture (%)
    uint16_t lx;        // luminous flux (lumens)
    uint8_t tp;         // ambient temperature (˚C)
    uint8_t pa;         // ambient pressure (kPa)
    uint8_t rh;         // relative humidity (%)
};

#endif // INCLUDE_TYPES_TYPES_H_ 