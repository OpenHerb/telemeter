/**
 * @file Pid.cpp
 * @author Christian Sargusingh (christian@leapsystems.online)
 * @brief 
 * @version 0.1
 * @date 2021-05-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include "Pid.h"

/**
 * @brief Construct a new Pid< T>:: Pid object
 * 
 * @tparam T 
 * @param spec constructor specification
 */
template <typename T>
Pid<T>::Pid(Spec spec) {
    kp = spec.kp;
    kd = spec.kd;
    ki = spec.ki;
    setpoint = spec.setpoint;
    min = spec.min;
    max = spec.max;
    Serial.println("PID controller initialized");
}

/**
 * @brief Destroy the Pid< T>:: Pid object
 * 
 * @tparam T 
 */
template <typename T>
Pid<T>::~Pid() {}

/**
 * @brief set the pid controller setpoint
 * 
 * @tparam T 
 * @param target proposed pid setpoint
 */
template <typename T>
void Pid<T>::set_target(T target) {
    if (target < max && target > min) {
        setpoint = target;
        Serial.print("Set setpoint to: ");
        Serial.println(setpoint);
    } else {
        Serial.println("Target rejected for being out of range");
    }
}

/**
 * @brief compute pid actuator response
 * 
 * @tparam T 
 * @param pv sensor process variable from feedback
 * @return T 
 */
template <typename T>
T Pid<T>::compute(T pv) {
    uint32_t t = millis();
    uint32_t elapsed = t - cts;
    uint16_t det;
    T et;
    T yt;
    // compute error margin
    et = setpoint - pv;
    // compute integral e(t) component
    iet += et * elapsed;
    // compute derivative offset smoother
    det = (et - cerr)/elapsed;
    // compute pid actuator output y(t)
    yt = kp*et + ki*iet + kd*det;
    Serial.print("Computed actuation: ");
    Serial.println(yt);
    return yt;
}

template class Pid<uint8_t>;