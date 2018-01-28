//
//  sinfit_training.hpp
//  curvefitting
//
//  Created by 孔祥云 on 1/28/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#ifndef sinfit_training_hpp
#define sinfit_training_hpp

#include <stdio.h>
#include <map>

#include "sinfit.hpp"

using namespace std;

static const long MAX_TRY_CHANGE = 10000;
static const long ADD_FUNC_BOUNDARY = 1000;

class sinfit_training {
public:
    sinfit get_sinfit() const;
    
    double train(map<double, double>& data, long max_round);
    
private:
    bool accept(double dm1, double dm2);
    void change_func(map<double, double>& data, double dm, double df, double dt);
    void rand_change_func(double df, double dt);
    
    void init_param();
    void adjust_param(bool accepted, double da, double db, double dc, double dd);
    
    double mean_square(map<double, double>& data, list<fsin*> func);
    double diff_sum(map<double, double>& data, list<fsin*> func);
    double dist_sum(map<double, double>& data, list<fsin*> func);
    
private:
    list<fsin*> m_func;
    
    double ch, ca, cb, cc, cd;
    double da, db, dc, dd;
    double jump;
};

#endif /* sinfit_training_hpp */
