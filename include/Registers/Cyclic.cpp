// -*- lsst-c++ -*-
/**
 * Cyclic Buffer Management 
 * 
 * See COPYRIGHT file at the top of the source tree.
 * Copyright © 2020 OpenHerb.
*/

#include <Arduino.h>
#include "Cyclic.h"

template <typename T>
CyclicBuffer<T>::CyclicBuffer(Spec spec) {
    name = spec.name;
    buffer_size = spec.buffer_size;
    cbuf = new T[buffer_size]();
    cbuf_start = cbuf;
    Serial.print("Allocated cyclic buffer registry for ");
    Serial.println(name);
}

template <typename T>
CyclicBuffer<T>::~CyclicBuffer() {
    delete cbuf;
    Serial.print("Dereferenced cyclic buffer registry for ");
    Serial.println(name);
}

template <typename T>
void CyclicBuffer<T>::push(T value) {
    // check for rollover
    if (cbuf > cbuf_start + buffer_size) cbuf = cbuf_start;
    // push to buffer and increment pointer
    *cbuf = value;
    ++cbuf;
}

template <typename T>
T CyclicBuffer<T>::average() {
    String buffer_log = "Buffer :";
    uint8_t size = buffer_size;
    uint32_t cumulative = 0;
    T avg = 0;
    // check for rollover
    if (sm_buffer > buf_start + buffer_size) {
        sm_buffer = buf_start;
    }
    
    // compute average from non-zero buffer readings
    for (uint8_t *p = buf_start; p != buf_start + buffer_size; ++p) {
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
        Serial.println("Not enough measurments for accurate soil reading");
    } else {
        avg = cumulative / size;
    }
    return avg;
}