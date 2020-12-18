// -*- lsst-c++ -*-
/**
 * Lib1
 * 
 * See COPYRIGHT file at the top of the source tree.
 * Copyright © [year] <Copyright Owner>.
*/

#include <Arduino.h>
#include "Lib1.h"

Lib1::Lib1(String msg) {
    this->msg = msg;
}

String Lib1::echo() {
    return this->msg;
}
