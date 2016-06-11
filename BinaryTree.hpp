//
//  BinaryTree.hpp
//  LearnCpp
//
//  Created by Wang on 4/7/16.
//  Copyright © 2016 Wang. All rights reserved.
//

#ifndef BinaryTree_hpp
#define BinaryTree_hpp

#include <stdio.h>
#include "Common.hpp"

using namespace std;
namespace traverse {
    TreeNode* specificTree();
    vector<int> preOrder(TreeNode* p);
    vector<int> inOrder(TreeNode* p);
    vector<int> postOrder(TreeNode* p);
    vector<int> BFS(TreeNode* p);
    vector<int> DFS(TreeNode* p);
}



namespace BST {
    void insert(TreeNode *&, int);
    TreeNode* search(TreeNode*, int);
    TreeNode* remove(TreeNode *, int);
    TreeNode* findMin(TreeNode*);
}

namespace AVL {
    TreeNode* insert(TreeNode *&, int);
    TreeNode* search(TreeNode*, int);
    void remove(TreeNode* p, int v);
    TreeNode* singleLL(TreeNode*);
    TreeNode* singleRR(TreeNode*);
    TreeNode* doubleLR(TreeNode*);
    TreeNode* doubleRL(TreeNode*);
    int getHeight(TreeNode*);
}

#endif /* BinaryTree_hpp */
