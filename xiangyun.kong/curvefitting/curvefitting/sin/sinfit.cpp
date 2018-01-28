//
//  sinfit.cpp
//  curvefitting
//
//  Created by 孔祥云 on 1/28/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#include "sinfit.hpp"

sinfit::sinfit(list<fsin*> func) {
    m_func = func;
}

sinfit::~sinfit() {
    /*
    for (fsin* sin : m_func) {
        delete sin;
    }
     */
}

double sinfit::apply(double x) {
    double r = 0.0;
    for (fsin* sin : m_func) {
        r += sin->f(x);
    }
    return r;
}

void sinfit::print() const {
    for (fsin* sin : m_func) {
        sin->print();
        printf(" + ");
    }
    printf("\b\b\b\n");
}
