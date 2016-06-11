//
//  BeautyProgram.cpp
//  LearnCpp
//
//  Created by Wang on 16/6/11.
//  Copyright © 2016年 Wang. All rights reserved.
//

#include "BeautyProgram.hpp"

vector<int> Beauty::chap2_3(vector<int> vec){
    vector<int> count(3, 0);
    vector<int> cand(3, -1);
    for (int i = 0; i < vec.size(); i++) {
        bool isNext = false;
        for (int j = 0; j < 3; j++) {
            if (cand[j] == vec[i]) {
                count[j]++;
                isNext = true;
                break;
            }
        }
        if (isNext) {
            continue;
        }
        for (int j = 0; j < 3; j++) {
            if (count[j] == 0) {
                count[j]++;
                cand[j] = vec[i];
                isNext = true;
                break;
            }
        }
        if (isNext) {
            continue;
        }
        for (int j = 0; j < 3; j++) {
            count[j]--;
        }
        
    }
    return cand;
}

vector<int> Beauty::chap2_3(){
    int id[] = {2, 3, 4};
    int num[] = {25, 25, 25, 24};
    vector<int> vec;
    for (int i = 0; i < 3; i++) {
        while (num[i] > 0) {
            num[i]--;
            vec.push_back(id[i]);
        }
    }
    for (int i = 0; i < num[3]; i++) {
        vec.push_back(rand()%100);
    }
    random_shuffle(vec.begin(), vec.end());
    vector<int> res = chap2_3(vec);
    printVector(res);
    return res;
}