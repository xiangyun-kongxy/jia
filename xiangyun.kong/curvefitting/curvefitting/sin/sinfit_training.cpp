//
//  sinfit_training.cpp
//  curvefitting
//
//  Created by 孔祥云 on 1/28/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#include "sinfit_training.hpp"
#include <cmath>
#include <stdlib.h>


sinfit sinfit_training::get_sinfit() const{
    return sinfit(m_func);
}

double sinfit_training::train(map<double, double>& data, long max_round) {
    m_func.clear();
    fsin* sin = new fsin(1.0, 1.0, 0.0, 0.0);
    m_func.push_back(sin);
    init_param();
    
    double dm, df, dt;
    dm = mean_square(data, m_func);
    df = diff_sum(data, m_func);
    dt = dist_sum(data, m_func);
    
    long last_accepted = max_round;
    long i = 0;
    while (dm > 1.0e-2) {
        if (++i > max_round) {
            break;
        }
        
        change_func(data, dm, df, dt);
        
        dm = mean_square(data, m_func);
        df = diff_sum(data, m_func);
        dt = dist_sum(data, m_func);
        
        if (jump == 0.0) {
            last_accepted = i;
            
            printf("%06ld %03.6lf ", i, dm);
            sinfit fit(m_func);
            fit.print();
        } else if (i - last_accepted > ADD_FUNC_BOUNDARY) {
            sin = new fsin(0.0, 1.0, 0, 0);
            m_func.push_back(sin);
            init_param();
            last_accepted = i;
        } else {
            jump += i - last_accepted;
            if (i % 100 == 0) {
                printf("%06ld\n", i);
            }
        }
    }
    
    return dm;
}

bool sinfit_training::accept(double dm1, double dm2) {
    return dm2 < dm1 && fabs(dm2 - dm1) > 1.0e-3;
}

void sinfit_training::change_func(map<double, double>& data, double dm,
                                  double df, double dt) {
    fsin* sin = *(--m_func.end());
    
    double dm2 = 0.0;
    
    long n = 0;
    while (++n < MAX_TRY_CHANGE) {
        rand_change_func(df, dt);
        sin->set_a(sin->get_a() + da);
        sin->set_b(sin->get_b() + db);
        sin->set_c(sin->get_c() + dc);
        sin->set_d(sin->get_d() + dd);
        
        dm2 = mean_square(data, m_func);
        if (accept(dm, dm2)) {
            adjust_param(true, da, db, dc, dd);
            break;
        } else {
            sin->set_a(sin->get_a() - da);
            sin->set_b(sin->get_b() - db);
            sin->set_c(sin->get_c() - dc);
            sin->set_d(sin->get_d() - dd);
            
            adjust_param(false, da, db, dc, dd);
        }
    }
    if (n >= MAX_TRY_CHANGE) {
        jump = 10.0;
    } else {
        jump = 0.0;
    }
}

void sinfit_training::rand_change_func(double df, double dt){
    da = 0.0;
    db = 0.0;
    dc = 0.0;
    dd = 0.0;
    
    double ea = 0.0;
    double ed = 0.0;
    double eb = 0.0;
    double ec = 0.0;
    
    if (fabs(dt) > fabs(df) * 10) {
        ea = fabs(dt);
    } else if (fabs(fabs(dt) / fabs(df) - 1.0) < 1.0e-2) {
        ed = fabs(dt) / fabs(df);
    } else {
        eb = 10.0;
        ec = 10.0;
    }
    
    if ((double) rand() / RAND_MAX < ca + ea) {
        da = (ch + jump + ea) * rand() / RAND_MAX;
        if (rand() % 100 < 50) {
            da *= -1;
        }
    }
    if ((double) rand() / RAND_MAX < cb + eb/20) {
        db = (ch + jump + eb) * rand() / RAND_MAX;
        if (rand() % 100 < 50) {
            db *= -1;
        }
    }
    if ((double) rand() / RAND_MAX < cc + ec/20) {
        dc = (ch + jump + ec) * rand() / RAND_MAX;
        if (rand() % 100 < 50) {
            dc *= -1;
        }
    }
    if ((double) rand() / RAND_MAX < cd + ed) {
        dd = (ch + jump + ed) * rand() / RAND_MAX;
        if (rand() % 100 < 50) {
            dd *= -1;
        }
    }
    
    if (da == 0.0 && db == 0.0 && dc == 0.0 && dd == 0.0) {
        da = 1.0;
    }
}

void sinfit_training::init_param(){
    ch = 1.0;
    ca = 1.0;
    cb = 0.0;
    cc = 0.0;
    cd = 0.0;
}

void sinfit_training::adjust_param(bool accepted, double da, double db,
                                   double dc, double dd){
    if (accepted) {
        double dh = da + db + dc + dd;
        ch = (ch + dh / 2.0);
        ca = (ca + da / dh) / 2.0;
        cb = (cb + db / dh) / 2.0;
        cc = (cc + dc / dh) / 2.0;
        cd = (cd + dd / dh) / 2.0;
    } else {
        ch *= 1.0;
        ca = (ca + 0.75) / 4.0;
        cb = (cb + 0.75) / 4.0;
        cc = (cc + 0.75) / 4.0;
        cd = (cd + 0.75) / 4.0;
    }
}

double sinfit_training::mean_square(map<double, double>& data, list<fsin*> func) {
    double s = 0.0;
    for (map<double, double>::iterator i = data.begin(); i != data.end(); ++i) {
        double vr =  i->second;
        double vf = 0.0;
        for (fsin* sin : func) {
            vf += sin->f(i->first);
        }
        s += pow(vr - vf, 2.0);
    }
    return sqrt(s / data.size());
}

double sinfit_training::diff_sum(map<double, double>& data, list<fsin*> func){
    double s = 0.0;
    for (map<double, double>::iterator i = data.begin(); i != data.end(); ++i) {
        double vr =  i->second;
        double vf = 0.0;
        for (fsin* sin : func) {
            vf += sin->f(i->first);
        }
        s += vf - vr;
    }
    return s / data.size();
}

double sinfit_training::dist_sum(map<double, double>& data, list<fsin*> func){
    double s = 0.0;
    for (map<double, double>::iterator i = data.begin(); i != data.end(); ++i) {
        double vr =  i->second;
        double vf = 0.0;
        for (fsin* sin : func) {
            vf += sin->f(i->first);
        }
        s += fabs(vf - vr);
    }
    return s / data.size();
}
