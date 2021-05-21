/**
 * @file Pid.h
 * @author Christian Sargusingh (christian@leapsystems.online)
 * @brief 
 * @version 0.1
 * @date 2021-05-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef INCLUDE_PID_PID_H_
#define INCLUDE_PID_PID_H_

template <typename T>
class Pid {
    public:
        struct Spec {
            uint8_t kp;     // proportional component weight
            uint8_t kd;     // derivative component weight
            uint8_t ki;     // integral component weight
            T setpoint;     // default setpoint value
            T min;          // max setpoint value
            T max;          // min setpoint value
        };
        explicit Pid(Spec spec);
        ~Pid();
        T compute(T pv);
        void set_target(T target);

    private:
        T setpoint;         // setpoint
        T min;              // max setpoint value
        T max;              // min setpoint value
        uint32_t cts;       // cached timestamp
        uint16_t cerr;      // cached error
        uint16_t iet;       // cumulative error
        uint8_t kp;         // proportional component weight
        uint8_t kd;         // derivative component weight
        uint8_t ki;         // integral component weight
};

#endif // INCLUDE_PID_PID_H_