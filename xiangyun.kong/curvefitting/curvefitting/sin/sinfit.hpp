//
//  sinfit.hpp
//  curvefitting
//
//  Created by 孔祥云 on 1/28/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef sinfit_hpp
#define sinfit_hpp

#include <stdio.h>
#include <list>
#include "fsin.hpp"

using namespace std;

class sinfit {
private:
    list<fsin*> m_func;
    
public:
    sinfit(list<fsin*> func);
    ~sinfit();
    
public:
    double apply(double x);
    void print() const;
    
public:
    list<fsin*> get_function() const {
        return m_func;
    }
    
    void set_function(list<fsin*> func) {
        m_func = func;
    }
};

#endif /* sinfit_hpp */
