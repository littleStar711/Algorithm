////
////  DataStructure.hpp
////  LearnCpp
////
////  Created by Wang on 3/28/16.
////  Copyright © 2016 Wang. All rights reserved.
////
//
//#ifndef DataStructure_hpp
//#define DataStructure_hpp
//
//#include <stdio.h>
//#include "vector"
//#include "Common.hpp"
//#include "iostream"
//#include "stack"
//#include "algorithm"
//using namespace std;
//
//template <typename T>
//void print1DVector(const vector<T>& vec){
//    for (size_t i = 0; i < vec.size(); i++) {
//        cout << vec[i] << " ";
//    }
//    cout << endl;
//}
//
//template <typename T>
//void print2DVector(const vector<vector<T>>& vec) {
//    for (size_t i = 0; i < vec.size(); i++) {
//        print1DVector(vec[i]);
//    }
//}
//
//vector<int> KMPnext(string srcstr);
//
//int KMP(string objstr, string srcstr);
//
//class treeTraverse{
//public:
//    TreeNode<int>* createTree1();
//    vector<int> DFS(TreeNode<int>*);     // non-recrusion
//    vector<int> DFSr(TreeNode<int>*);    // recrusion
//    void DFSr_help(TreeNode<int>*,
//                   vector<int>&);
//    vector<vector<int>> DFSway(TreeNode<int>*);
//    void DFSway_help(TreeNode<int>*,
//                     vector<int>,
//                     vector<vector<int>>&);
//    
//};
//
//class splitNum{
//public:
//    vector<vector<unsigned long long>>
//    operator()(unsigned long long n);
//};
//
//class nQueens{
//public:
//    vector<vector<string>> operator()(int n);
//    string validPos(int n,
//                    vector<string> obj);
//    void getQueen(string pos,
//                  vector<string>,
//                  vector<vector<string>>& obj);
//};
//
//class List_Stack_Queues{
//public:
//    double calPostfix(string expression);
//};
//
//class Sorting{
//public:
//    vector<int> radix_sort(vector<int>);
//    vector<int> quick_sort(vector<int>);
//    void quick_sort_help(vector<int>&,
//                         int low,
//                         int high);
//};
//#endif /* DataStructure_hpp */
