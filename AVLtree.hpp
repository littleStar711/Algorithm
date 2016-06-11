//
//  AVLtree.hpp
//  LearnCpp
//
//  Created by Wang on 4/8/16.
//  Copyright © 2016 Wang. All rights reserved.
//

#ifndef AVLtree_hpp
#define AVLtree_hpp

#include <stdio.h>
#include "Common.hpp"

struct AVLnode{
    AVLnode(int v):val(v), height(0), lchild(nullptr), rchild(nullptr){};
    int val;
    int height;
    AVLnode* lchild, *rchild;
};

int getHeight(AVLnode* p);

AVLnode* insert(int i, AVLnode*& p);

int find(int i, AVLnode* p);

AVLnode* singleLL(AVLnode*& p);

AVLnode* singleRR(AVLnode*& p);

AVLnode* doubleLR(AVLnode*& p);

AVLnode* doubleRL(AVLnode*& p);

void printAVL(AVLnode* p);

class AVLtree{
public:
    AVLtree():root(nullptr){};
    AVLnode* insert(AVLnode*&, int i);
    AVLnode* find(AVLnode* p, int i);
    AVLnode* singleLL(AVLnode* p);
    AVLnode* singleRR(AVLnode* p);
    AVLnode* doubleLR(AVLnode* p);
    AVLnode* doubleRL(AVLnode* p);
    void remove(AVLnode* p, int i);
    AVLnode* root;
};

#endif /* AVLtree_hpp */
