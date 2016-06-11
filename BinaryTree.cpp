//
//  BinaryTree.cpp
//  LearnCpp
//
//  Created by Wang on 4/7/16.
//  Copyright © 2016 Wang. All rights reserved.
//

#include "BinaryTree.hpp"
namespace traverse{
    TreeNode* specificTree(){
        /*
         *              1
         *            /   \
         *           2      3
         *          / \    / \
         *         4   5  6   7
         *            / \    /
         *           8   9  10
         *                    \
         *                    11
         */
        TreeNode *root = new TreeNode(1);
        root -> lchild = new TreeNode(2);
        root -> rchild = new TreeNode(3);
        root -> lchild -> lchild = new TreeNode(4);
        root -> lchild -> rchild = new TreeNode(5);
        root -> rchild -> lchild = new TreeNode(6);
        root -> rchild -> rchild = new TreeNode(7);
        root -> lchild -> rchild -> lchild = new TreeNode(8);
        root -> lchild -> rchild -> rchild = new TreeNode(9);
        root -> rchild -> rchild -> lchild = new TreeNode(10);
        root -> rchild -> rchild -> lchild -> rchild = new TreeNode(11);
        return root;
    }

    vector<int> preOrder(TreeNode* p){
        vector<int> res;
        if (p == nullptr) {
            return res;
        }
        stack<TreeNode*> buf;
        while (p != nullptr || !buf.empty()) {
            if (p != nullptr) {
                buf.push(p);
                res.push_back(p -> val);
                p = p -> lchild;
            }
            else{
                p = buf.top();
                buf.pop();
                p = p -> rchild;
            }
        }
        return res;
    }

    vector<int> inOrder(TreeNode* p){
        vector<int> res;
        if (p == nullptr) {
            return res;
        }
        stack<TreeNode*> buf;
        while (p != nullptr || !buf.empty()) {
            if (p != nullptr) {
                buf.push(p);
                p = p -> lchild;
            }
            else{
                p = buf.top();
                buf.pop();
                res.push_back(p -> val);
                p = p -> rchild;
            }
        }
        return res;
    }
    vector<int> postOrder(TreeNode* p);
    vector<int> BFS(TreeNode* p);
    vector<int> DFS(TreeNode* p);
}

namespace BST {
    void insert(TreeNode *& p, int v){
        if (p == nullptr) {
            p = new TreeNode(v);
        }
        else if (v < p -> val) {
            insert(p -> lchild, v);
        }
        else if (v > p -> val) {
            insert(p -> rchild, v);
        }
        else{
            throw logic_error("Error: No Duplicate Number in Binary Search Tree");
        }
    }
    TreeNode* search(TreeNode*p, int v){
        if (p == nullptr) {
            return p;
        }
        else if (p -> val == v) {
            return p;
        }
        else if (v < p -> val){
            return search(p -> lchild, v);
        }
        else{
            return search(p -> rchild, v);
        }
    }
    
    TreeNode* remove(TreeNode *root, int v){
        TreeNode* temp;
        if (root == nullptr) {
            return root;
        }
        root = search(root, v);
        if (root -> lchild && root -> rchild){
            temp = findMin(root -> rchild);
            root -> val = temp -> val;
            root -> rchild = remove(root -> rchild, root -> val);
        }
        else{
            temp = root;
            if (root -> lchild == nullptr) {
                root = root -> rchild;
            }
            else{
                root = root -> lchild;
            }
            delete temp;
        }
        return root;
    }
    
    TreeNode* findMin(TreeNode* p){
        if (p -> lchild != nullptr) {
            return findMin(p -> lchild);
        }
        else{
            return p;
        }
    }
}

namespace AVL {
    TreeNode* insert(TreeNode *&p, int v){
        if (p == nullptr) {
            p = new TreeNode(v);
        }
        else if(v < p -> val){
            p -> lchild = insert(p -> lchild, v);
            if (getHeight(p -> lchild) - getHeight(p -> rchild) == 2) {
                if (v < p -> lchild -> val) {
                    p = singleLL(p);
                }
                else{
                    p = doubleLR(p);
                }
            }
        }
        else if(v > p -> val){
            p -> rchild = insert(p -> rchild, v);
            if (getHeight(p -> rchild) - getHeight(p -> lchild) == 2) {
                if (v > p -> rchild -> val) {
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
    
    TreeNode* search(TreeNode* p, int v){
        while (p != nullptr) {
            if (p -> val == v) {
                return p;
            }
            else if(v < p -> val){
                p = p -> lchild;
            }
            else if(v > p -> val){
                p = p -> rchild;
            }
        }
        return nullptr;
    }
    
    /*
     * 删除结点(z)，返回根节点
     *
     * 参数说明：
     *	 tree AVL树的根结点
     *	 z 待删除的结点
     * 返回值：
     *	 根节点
     */
    TreeNode* maximum(TreeNode* p){
        if (p == nullptr) {
            return nullptr;
        }
        while (p -> rchild != nullptr) {
            p = p -> rchild;
        }
        return p;
    }
    
    TreeNode* removeHelp(TreeNode* &tree, TreeNode* z)
    {
        // 根为空 或者 没有要删除的节点，直接返回NULL。
        if (tree == nullptr || z == nullptr)
            return nullptr;
        
        if (z->val < tree -> val)		// 待删除的节点在"tree的左子树"中
        {
            tree -> lchild = removeHelp(tree -> lchild, z);
            // 删除节点后，若AVL树失去平衡，则进行相应的调节。
            if (getHeight(tree -> rchild) - getHeight(tree -> lchild) == 2)
            {
                TreeNode *r =  tree -> rchild;
                if (getHeight( r -> lchild ) > getHeight( r -> rchild))
                    tree = doubleRL(tree);
                else
                    tree = singleRR(tree);
            }
        }
        else if (z -> val > tree -> val)// 待删除的节点在"tree的右子树"中
        {
            tree -> rchild = removeHelp(tree -> rchild, z);
            // 删除节点后，若AVL树失去平衡，则进行相应的调节。
            if (getHeight(tree -> lchild) - getHeight(tree -> rchild) == 2)
            {
                TreeNode *l =  tree -> lchild;
                if (getHeight(l -> rchild) > getHeight(l -> lchild))
                    tree = doubleLR(tree);
                else
                    tree = singleLL(tree);
            }
        }
        else	// tree是对应要删除的节点。
        {
            // tree的左右孩子都非空
            if ((tree -> lchild != NULL) && (tree -> rchild != NULL))
            {
                if (getHeight(tree -> lchild) > getHeight(tree -> rchild))
                {
                    // 如果tree的左子树比右子树高；
                    // 则(01)找出tree的左子树中的最大节点
                    //   (02)将该最大节点的值赋值给tree。
                    //   (03)删除该最大节点。
                    // 这类似于用"tree的左子树中最大节点"做"tree"的替身；
                    // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
                    TreeNode* max = maximum(tree -> lchild);
                    tree->val = max->val;
                    tree->lchild = removeHelp(tree->lchild, max);
                }
                else
                {
                    // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
                    // 则(01)找出tree的右子树中的最小节点
                    //   (02)将该最小节点的值赋值给tree。
                    //   (03)删除该最小节点。
                    // 这类似于用"tree的右子树中最小节点"做"tree"的替身；
                    // 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
                    TreeNode* min = maximum(tree->rchild);
                    tree->val = min->val;
                    tree->rchild = removeHelp(tree->rchild, min);
                }
            }
            else
            {
                TreeNode* tmp = tree;
                tree = (tree->lchild!=NULL) ? tree->lchild : tree->rchild;
                delete tmp;
            }
            if (tree != nullptr) {
                tree -> height = max(getHeight(tree -> lchild), getHeight(tree -> rchild)) + 1;
                cout << tree-> val << ", " << tree -> height << endl;
            }
        }
        
        
        return tree;
    }
    
    void remove(TreeNode* p,int v)
    {
        TreeNode* z = search(p, v);
        if (z != nullptr){
            p = removeHelp(p, z);
        }
    }
    
    TreeNode* singleLL(TreeNode* p){
        TreeNode* res = p -> lchild;
        p -> lchild = res -> rchild;
        res -> rchild = p;
        p -> height = max(getHeight(p -> lchild), getHeight(p -> rchild)) + 1;
        res -> height = max(getHeight(res -> lchild), getHeight(res -> rchild)) + 1;
        return res;
    }
    
    TreeNode* singleRR(TreeNode* p){
        TreeNode* res = p -> rchild;
        p -> rchild = res -> lchild;
        res -> lchild = p;
        p -> height = max(getHeight(p -> lchild), getHeight(p -> rchild)) + 1;
        res -> height = max(getHeight(res -> lchild), getHeight(res -> rchild)) + 1;
        return res;
    }
    TreeNode* doubleLR(TreeNode* p){
        p -> lchild = singleRR(p -> lchild);
        p = singleLL(p);
        return p;
    }
    TreeNode* doubleRL(TreeNode* p){
        p -> rchild = singleLL(p -> rchild);
        p = singleRR(p);
        return p;
    }
    int getHeight(TreeNode* p){
        if (p == nullptr) {
            return 0;
        }
        else{
            return p -> height;
        }
    }
}