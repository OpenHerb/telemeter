// -*- lsst-c++ -*-
/**
 * Lib2
 * 
 * See COPYRIGHT file at the top of the source tree.
 * Copyright © [year] <Copyright Owner>.
*/

#include <Arduino.h>
#include "Lib2.h"

Lib2::Lib2(String msg) {
    this->msg = msg;
}

String Lib2::echo() {
    return this->msg;
}
