// -*- lsst-c++ -*-
/**
 * Cyclic Buffer Management 
 * 
 * See COPYRIGHT file at the top of the source tree.
 * Copyright © 2020 OpenHerb.
*/

#include <Arduino.h>
#include "Cyclic.h"

/**
 * @brief Construct a new Cyclic Buffer< T>:: Cyclic Buffer object
 * 
 * @tparam T 
 * @param spec constructor specification
 */
template <typename T>
CyclicBuffer<T>::CyclicBuffer(Spec spec) {
    name = spec.name;
    buffer_size = spec.buffer_size;
    cbuf = new T[buffer_size]();
    cbuf_start = cbuf;
    Serial.print("Allocated cyclic buffer registry for ");
    Serial.println(name);
}

/**
 * @brief Destroy the Cyclic Buffer< T>:: Cyclic Buffer object
 * 
 * @tparam T 
 */
template <typename T>
CyclicBuffer<T>::~CyclicBuffer() {
    delete cbuf;
    Serial.print("Dereferenced cyclic buffer registry for ");
    Serial.println(name);
}

/**
 * @brief Push a new value of type <T> to the buffer and increment pointer cyclically
 * 
 * @tparam T 
 * @param value new buffer value
 */
template <typename T>
void CyclicBuffer<T>::push(T value) {
    // check for rollover
    if (cbuf > cbuf_start + buffer_size) cbuf = cbuf_start;
    // push to buffer and increment pointer
    *cbuf = value;
    ++cbuf;
}

/**
 * @brief Compute buffer average filtering all 0 values.
 * 
 * @tparam T 
 * @return T 
 */
template <typename T>
T CyclicBuffer<T>::average() {
    String buffer_log = "Buffer :";
    uint8_t size = buffer_size;
    uint32_t cumulative = 0;
    T avg = 0;
    // check for rollover
    if (cbuf > cbuf_start + buffer_size) cbuf = cbuf_start;
    // compute average from non-zero buffer readings
    for (T *p = cbuf_start; p != cbuf_start + buffer_size; ++p) {
        buffer_log += " [" + String(*p) + "%]";
        if (*p <= 0) {
            size -= 1;
        } else {
            cumulative += *p;
        }
    }
    Serial.println(buffer_log);
    // compute average if sufficient data
    if (size == 0) {
        Serial.println("Not enough measurments for accurate reading");
    } else {
        avg = cumulative / size;
    }
    return avg;
}

template class CyclicBuffer<uint8_t>;
template class CyclicBuffer<uint16_t>;
