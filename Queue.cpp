//
//  Queue.cpp
//  LearnCpp
//
//  Created by Wang on 4/8/16.
//  Copyright © 2016 Wang. All rights reserved.
//

#include "Queue.hpp"

bool operator<(const Patient&p1,
                const Patient&p2){
    if (p1.level < p2.level) {
        return true;
    }
    else{
        return false;
    }
}

bool operator>(const Patient&p1,
               const Patient&p2){
    return p2 > p1;
}

string Patient::getName(){
    return name;
}