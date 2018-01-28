//
//  fsin.hpp
//  curvefitting
//
//  Created by 孔祥云 on 1/28/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef fsin_hpp
#define fsin_hpp

#include <stdio.h>

class fsin {
private:
    /**
     * fsin = a sin(bx+c) + d
     */
    double a, b, c, d;
    
public:
    fsin(double a, double b, double c, double d);
    fsin();
    
public:
    double f(double x);
    
    void print();
    
public:
    double get_a() const {
        return a;
    }
    
    double get_b() const {
        return b;
    }
    
    double get_c() const {
        return c;
    }
    
    double get_d() const {
        return d;
    }
    
    void set_a(double a) {
        this->a = a;
    }
    
    void set_b(double b) {
        this->b = b;
    }
    void set_c(double c) {
        this->c = c;
    }
    void set_d(double d) {
        this->d = d;
    }
};

#endif /* fsin_hpp */
