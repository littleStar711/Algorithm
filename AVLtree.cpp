//
//  AVLtree.cpp
//  LearnCpp
//
//  Created by Wang on 4/8/16.
//  Copyright © 2016 Wang. All rights reserved.
//

#include "AVLtree.hpp"

int getHeight(AVLnode* p){
    if (p == nullptr) {
        return 0;
    }
    else{
        return p -> height;
    }
}

AVLnode* insert(int i, AVLnode*&p){
    if(p == nullptr){
        p = new AVLnode(i);
    }
    else if(i < p -> val){
        insert(i, (p -> lchild));
        if (getHeight(p -> lchild) - getHeight(p -> rchild) == 2) {
            if (i < p -> lchild -> val) {
                p = singleLL(p);
            }
            else{
                p = doubleLR(p);
            }
        }
    }
    else if(i > p -> val){
        insert(i, (p -> rchild));
        if (getHeight(p -> rchild) - getHeight(p -> lchild) == 2) {
            if (i < p -> rchild -> val) {
                p = doubleRL(p);
            }
            else{
                p = singleRR(p);
            }
        }
    }
    
    p -> height = max(getHeight(p -> lchild), getHeight(p -> rchild)) + 1;
    return p;
}


//int AVLtree::find(int i);
AVLnode* singleLL(AVLnode*& p){
    AVLnode* res = p -> lchild;
    p -> lchild = res -> rchild;
    res -> rchild = p;
    p -> height = max(getHeight(p ->lchild), getHeight(p -> rchild)) + 1;
    res -> height = max(getHeight(res -> lchild), getHeight(res -> rchild)) + 1;
    return res;
}


AVLnode* singleRR(AVLnode*& p){
    AVLnode* res = p -> rchild;
    p -> rchild = res -> lchild;
    res -> lchild = p;
    p -> height = max(getHeight(p ->lchild), getHeight(p -> rchild)) + 1;
    res -> height = max(getHeight(res -> lchild), getHeight(res -> rchild)) + 1;
    return res;
}

AVLnode* doubleLR(AVLnode*& p){
    p -> lchild = singleRR(p -> lchild);
    p = singleLL(p);
    return p;
}

AVLnode* doubleRL(AVLnode*& p){
    p -> rchild = singleLL(p -> rchild);
    p = singleRR(p);
    return p;
}

void printAVL(AVLnode* p){
    if (p == nullptr) {
        return;
    }
    printAVL(p -> lchild);
    cout << p -> val << " ";
    printAVL(p -> rchild);
}

AVLnode* AVLtree::insert(AVLnode*&p, int i){
    if (p == nullptr) {
        p = new AVLnode(i);
    }
    else if(i < p -> val){
        insert(p -> lchild, i);
        if ((getHeight(p -> lchild) - getHeight(p -> rchild)) == 2) {
            if (i < p -> lchild -> val) {
                p = singleLL(p);
            }
            else{
                p = doubleLR(p);
            }
        }
    }
    else if(i > p -> val){
        insert(p -> rchild, i);
        if ((getHeight(p -> rchild) - getHeight(p -> lchild)) == 2) {
            if (i > p -> rchild -> val) {
                p = singleRR(p);
            }
            else{
                p = doubleRL(p);
            }
        }
    }
    p -> height = max(getHeight(p -> lchild), getHeight(p -> rchild)) + 1;
    return p;
}

AVLnode* AVLtree::singleLL(AVLnode *p){
    AVLnode* res = p -> lchild;
    p -> lchild = res -> rchild;
    res -> rchild = p;
    p -> height = max(getHeight(p -> lchild), getHeight(p -> rchild)) + 1;
    res -> height = max(getHeight(res -> lchild), getHeight(res -> rchild)) + 1;
    return res;
}

AVLnode* AVLtree::singleRR(AVLnode *p){
    AVLnode* res = p -> rchild;
    p -> rchild = res -> lchild;
    res -> lchild = p;
    p -> height = max(getHeight(p -> lchild), getHeight(p -> rchild)) + 1;
    res -> height = max(getHeight(res -> lchild), getHeight(res -> rchild)) + 1;
    return res;
}

AVLnode* AVLtree::doubleLR(AVLnode *p){
    p -> lchild = singleRR(p -> lchild);
    p = singleLL(p);
    return p;
}

AVLnode* AVLtree::doubleRL(AVLnode *p){
    p -> rchild = singleLL(p -> rchild);
    p = singleRR(p);
    return p;
}

AVLnode* AVLtree::find(AVLnode* p, int i){
    if (p == nullptr) {
        return nullptr;
    }
    else if (p -> val == i){
        return p;
    }
    else if (i < p -> val){
        return find(p -> lchild, i);
    }
    else{
        return find(p -> rchild, i);
    }
}

void AVLtree::remove(AVLnode* root, int i){
    
}