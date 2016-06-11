//
//  Queue.hpp
//  LearnCpp
//
//  Created by Wang on 4/8/16.
//  Copyright © 2016 Wang. All rights reserved.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <stdio.h>
#include "Heap.hpp"

template <typename T>
class PriorityQueue{
public:
    PriorityQueue(){};
    void EnQueue(const T&);
    T DeQueue() throw (runtime_error);
    size_t getSize();
private:
    Heap<T> data;
};

template <typename T>
void PriorityQueue<T>::EnQueue(const T &val){
    data.add(val);
}

template <typename T>
T PriorityQueue<T>::DeQueue() throw (runtime_error){
    T res;
    try{
        res = data.remove();
    }catch(runtime_error e){
        throw;
    }
    return res;
}

template <typename T>
size_t PriorityQueue<T>::getSize(){
    return data.getSize();
}

class Patient{
    friend bool operator<(const Patient&, const Patient&);
public:
    Patient(){}
    Patient(string n, int l):name(n), level(l){}
    string getName();
private:
    string name;
    int level;
};

bool operator>(const Patient&p1,
               const Patient&p2);
#endif /* Queue_hpp */
