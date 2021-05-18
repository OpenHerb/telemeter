// -*- lsst-c++ -*-
/**
 * Cyclic Buffer Management Interface
 * 
 * See COPYRIGHT file at the top of the source tree.
 * Copyright © 2020 OpenHerb.
 * 
 * @file CyclicBuffer.h
 *
 * @brief Memory allocation and buffer computation management
 *
 * @ingroup Registers 
 *
 * @author Christian Sargusingh
 * Contact: christian@leapsystems.online
 */

#ifndef INCLUDE_CYCLICBUFFER_SRC_CYCLICBUFFER_H_
#define INCLUDE_CYCLICBUFFER_SRC_CYCLICBUFFER_H_
#include <Arduino.h>

/**
 * @brief Cyclic Buffer
 * 
 * @tparam T 
 */
template <typename T>
class CyclicBuffer {
    public:
        struct Spec {
            String name;                    // name of buffer for logging
            uint8_t buffer_size;            // size of the buffer (used to compute end of buffer)
        };
        explicit CyclicBuffer<T>(Spec spec);
        ~CyclicBuffer<T>();
        T average();
        void push(T value);

    private:
        T *cbuf;                            // generic cyclic buffer mem pointer 
        T *cbuf_start;                      // buffer start address
        String name;                        // name of buffer for logging
        uint8_t buffer_size;                // size of the buffer (used to compute end of buffer)
};
#endif // INCLUDE_CYCLICBUFFER_SRC_CYCLICBUFFER_H_