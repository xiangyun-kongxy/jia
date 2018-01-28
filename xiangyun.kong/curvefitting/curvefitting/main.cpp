//
//  main.cpp
//  curvefitting
//
//  Created by 孔祥云 on 1/28/18.
//  Copyright © 2018 孔祥云. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <time.h>

#include "sin/sinfit_training.hpp"

using namespace std;

void train(map<double, double>& data, sinfit tested) {
    sinfit_training training;
    training.train(data, 10000);
    sinfit fit = training.get_sinfit();
    tested.print();
    printf("----------------\n");
    fit.print();
    printf("^^^^^^^^^^^^^^^^\n");
    
    
    for (long i = 0; i < 100; ++i) {
        double key = i / 3.0;
        double value1 = tested.apply(key);
        double value2 = fit.apply(key);
        printf("%05.6lf %05.6lf %05.6lf %05.6lf\n", value1, value2,
                           (value2 - value1), fabs((value2 - value1) / value1));
    }
}

int main(int argc, const char * argv[]) {
    srand((unsigned)time(nullptr));
    
    fsin* f1 = new fsin(1.0, 1.0, 0.0, 0.0);
    fsin* f2 = new fsin(5.6, 3.2, 0.4, 2.1);
    fsin* f3 = new fsin(1.2, 1.0, 0.0, 0.0);
    fsin* f4 = new fsin(1.0, 2.1, 0.0, 0.0);
    fsin* f5 = new fsin(1.0, 1.0, 3.2, 0.0);
    fsin* f6 = new fsin(1.0, 1.0, 0.0, 4.3);

    list<fsin*> ff;
    map<double, double> data;
    
    ff.clear();
    ff.push_back(f1);
    sinfit test1(ff);
    data.clear();
    for (long i = 0; i < 100; ++i) {
        double key = i / 3.0;
        double value = test1.apply(key);
        data[key] = value;
    }
    printf("test case 1:\n");
    train(data, test1);
    
    ff.clear();
    ff.push_back(f2);
    sinfit test2(ff);
    data.clear();
    for (long i = 0; i < 100; ++i) {
        double key = i / 3.0;
        double value = test2.apply(key);
        data[key] = value;
    }
    printf("test case 2:\n");
    train(data, test2);
 
    ff.clear();
    ff.push_back(f3);
    ff.push_back(f4);
    ff.push_back(f5);
    ff.push_back(f6);
    sinfit test3(ff);
    data.clear();
    for (long i = 0; i < 100; ++i) {
        double key = i / 3.0;
        double value = test3.apply(key);
        data[key] = value;
    }
    printf("test case 3:\n");
    train(data, test3);
    
    delete f6;
    delete f5;
    delete f4;
    delete f3;
    delete f2;
    delete f1;
    
    return 0;
}
