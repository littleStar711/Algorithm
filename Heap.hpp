//
//  Heap.hpp
//  LearnCpp
//
//  Created by Wang on 4/7/16.
//  Copyright © 2016 Wang. All rights reserved.
//

#ifndef Heap_hpp
#define Heap_hpp

#include <stdio.h>
#include "vector"
#include "iostream"
#include "Common.hpp"
using namespace std;
template <typename T>
class Heap{
public:
    Heap();
    Heap(const vector<T>&);
    T remove() throw(runtime_error);
    void add(const T&);
    size_t getSize();
private:
    vector<T> vec;
};

template <typename T>
Heap<T>::Heap(){
    
}

template <typename T>
Heap<T>::Heap(const vector<T>& cvec){
    for (size_t i = 0; i < cvec.size(); i++) {
        add(cvec[i]);
    }
}

template <typename T>
T Heap<T>::remove() throw (runtime_error){
    if (vec.empty()) {
        throw runtime_error("Heap is empty");
    }
    T res = vec[0];
    vec[0] = vec.back();
    vec.pop_back();
    size_t len = vec.size();
    size_t parentIdx = 0;
    while (parentIdx < vec.size()) {
        size_t childIdx = parentIdx * 2 + 1;
        if (childIdx >= len) {
            break;
        }
        if (childIdx + 1 < len && vec[childIdx] < vec[childIdx + 1]) {
            ++childIdx;
        }
        if (vec[parentIdx] < vec[childIdx]) {
            swap(vec[parentIdx], vec[childIdx]);
            parentIdx = childIdx;
        }
        else{
            break;
        }
    }
    return res;
}

template <typename T>
void Heap<T>::add(const T & val){
    vec.push_back(val);
    int currentIdx = static_cast<int>(getSize()) - 1;
    while (currentIdx > 0) {
        int parentIdx = (currentIdx - 1) / 2;
        if (vec[parentIdx] < vec[currentIdx]) {
            swap(vec[parentIdx], vec[currentIdx]);
        }
        else{
            break;
        }
        currentIdx = parentIdx;
    }
}

template <typename T>
size_t Heap<T>::getSize(){
    return vec.size();
}
#endif /* Heap_hpp */
