//
//  Common.cpp
//  LearnCpp
//
//  Created by Wang on 4/7/16.
//  Copyright © 2016 Wang. All rights reserved.
//

#include "Common.hpp"
vector<int>
getRand(size_t len, int max, unsigned int seed){
    
    srand(seed);
    vector<int> res(len, 0);
    for (size_t i = 0; i < len; i++) {
        res[i] = rand() % max;
    }
    return res;
}

void
printVector(const vector<int>& vec, const string& msg) {
    cout << msg << ": ";
    for (auto i: vec) {
        cout << i << " ";
    }
    cout << endl;
}