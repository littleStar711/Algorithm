//
//  Common.hpp
//  LearnCpp
//
//  Created by Wang on 4/7/16.
//  Copyright © 2016 Wang. All rights reserved.
//

#ifndef Common_hpp
#define Common_hpp

#include <stdio.h>
#include "vector"
#include "stack"
#include "iostream"
using namespace std;
struct TreeNode{
    int val;
    TreeNode *lchild, *rchild;
    int height;
    TreeNode(int i): val(i), lchild(nullptr), rchild(nullptr), height(0){};
};

vector<int> 
getRand(size_t len, int max = 100, unsigned int seed = 0);

void
printVector(const vector<int>& vec, const string& msg = "vector");

#endif /* Common_hpp */
