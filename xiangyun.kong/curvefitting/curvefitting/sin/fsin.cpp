//
//  fsin.cpp
//  curvefitting
//
//  Created by 孔祥云 on 1/28/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#include "fsin.hpp"
#include <cmath>

using namespace std;

fsin::fsin() {
    a = 0;
    b = 0;
    c = 0;
    d = 0;
}

fsin::fsin(double a, double b, double c, double d) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

double fsin::f(double x) {
    return a * sin(b * x + c) + d;
}

void fsin::print() {
    printf("%.6lf * sin(%.6lfx + %.6lf) + %.6lf", a, b, c, d);
}
