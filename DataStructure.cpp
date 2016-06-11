////
////  DataStructure.cpp
////  LearnCpp
////
////  Created by Wang on 3/28/16.
////  Copyright © 2016 Wang. All rights reserved.
////
//
//#include "DataStructure.hpp"
//vector<int> KMPnext(string str){
//    vector<int> res(str.size() + 1, 0);
//    int i = 1, j = 0;
//    while (i < res.size()) {
//        if (j == 0 || str[i - 1] == str[j - 1]) {
//            i++;
//            j++;
//            res[i] = j;
//        }
//        else{
//            j = res[j];
//        }
//    }
//    return res;
//}
//
//int KMP(string obj, string src){
//    int i = 1, j = 1;
//    vector<int> next = KMPnext(src);
//    while (i <= obj.size() && j <= src.size()) {
//        printf("obj[%d]=%c, src[%d]=%c\n",
//               i-1, obj[i-1], j-1, src[j-1]);
//        if (j == 0 || obj[i - 1] == src[j - 1]) {
//            j++;
//            i++;
//        }
//        else{
//            j = next[j];
//        }
//    }
//    if (j > src.size()) {
//        return i - j + 1;
//    }
//    else{
//        return -1;
//    }
//}
//
//TreeNode<int>* treeTraverse::createTree1(){
//    /*
//     *              1
//     *            /   \
//     *           2      3
//     *          / \    / \
//     *         4   5  6   7
//     *            / \    /
//     *           8   9  10
//     *                    \
//     *                    11
//     */
//    TreeNode<int> *root = new TreeNode<int>(1);
//    root -> lchild = new TreeNode<int>(2);
//    root -> rchild = new TreeNode<int>(3);
//    root -> lchild -> lchild = new TreeNode<int>(4);
//    root -> lchild -> rchild = new TreeNode<int>(5);
//    root -> rchild -> lchild = new TreeNode<int>(6);
//    root -> rchild -> rchild = new TreeNode<int>(7);
//    root -> lchild -> rchild -> lchild = new TreeNode<int>(8);
//    root -> lchild -> rchild -> rchild = new TreeNode<int>(9);
//    root -> rchild -> rchild -> lchild = new TreeNode<int>(10);
//    root -> rchild -> rchild -> lchild -> rchild = new TreeNode<int>(11);
//    return root;
//}
//
//vector<int>
//treeTraverse::DFS(TreeNode<int>* root){
//    vector<int> res;
//    stack<TreeNode<int>*> buf;
//    buf.push(root);
//    while (!buf.empty()) {
//        TreeNode<int>* p = buf.top();
//        buf.pop();
//        if (p -> rchild != nullptr) {
//            buf.push(p -> rchild);
//        }
//        if (p -> lchild != nullptr) {
//            buf.push(p -> lchild);
//        }
//        res.push_back(p -> val);
//    }
//    return res;
//}
//
//vector<int>
//treeTraverse::DFSr(TreeNode<int>* root){
//    vector<int> res;
//    DFSr_help(root, res);
//    return res;
//}
//
//void
//treeTraverse::DFSr_help(TreeNode<int>* p,
//                        vector<int>& vec){
//    vec.push_back(p -> val);
//    if (p -> lchild != nullptr) {
//        DFSr_help(p -> lchild, vec);
//    }
//    if (p -> rchild != nullptr) {
//        DFSr_help(p -> rchild, vec);
//    }
//}
//
//vector<vector<int>>
//treeTraverse::DFSway(TreeNode<int> *root){
//    vector<vector<int>> res;
//    vector<int> way;
//    DFSway_help(root, way, res);
//    return res;
//}
//
//void
//treeTraverse::DFSway_help(TreeNode<int>* p,
//                          vector<int> cur,
//                          vector<vector<int>>& vec){
//    cur.push_back(p -> val);
//    if (p -> lchild == nullptr &&
//        p -> rchild == nullptr) {
//        vec.push_back(cur);
//    }
//    else{
//        if (p -> lchild != nullptr) {
//            DFSway_help(p -> lchild, cur, vec);
//        }
//        if (p -> rchild != nullptr) {
//            DFSway_help(p -> rchild, cur, vec);
//        }
//    }
//}
//
//vector<vector<unsigned long long>>
//splitNum::operator()(unsigned long long n){
//   // assert(n>1);
//    vector< vector<unsigned long long> > results;
//    vector<unsigned long long> count(n-1);  // 计数器，记录每个数字的数量
//    unsigned long long remain=n,            // 剩余未选值的和
//    cur=n-1;                  // 当前操作的数值
//    for(;;)
//    {
//        if(!remain)
//        {
//            vector<unsigned long long> res;
//            for(unsigned long long i=0;i<n-1;++i)
//                for(unsigned long long j=0;j<count[i];++j)
//                    res.push_back(i+1);
//            results.push_back(res);
//            if(!cur)
//            {
//                if(count[0]==n)break;
//                remain=count[0];
//                count[0]=0;
//                while(!count[++cur]);
//            }
//            remain+=cur+1;
//            --count[cur];
//        }
//        else if(cur==1)
//        {
//            count[0]=remain;
//            remain=0;
//            cur=0;
//        }
//        else
//        {
//            count[cur-1]=remain/cur;
//            remain%=cur--;
//        }
//    }
//    return results;
//}
//
//vector<vector<string>>
//nQueens::operator()(int n){
//    vector<vector<string>> res;
//    vector<string> cur;
////    res.push_back(vector<string>(n, string(n, '-')));
//    getQueen(string(n, '-'), cur, res);
//    return res;
//}
//
//void
//nQueens::getQueen(string pos,
//                  vector<string> cur,
//                  vector<vector<string>> &res){
//    if(cur.size() == pos.size()){
//        res.push_back(cur);
//        return;
//    }
//    else{
//        //pos = validPos(pos.size(), cur);
//        cur.push_back(string(pos.size(), '-'));
//        for (int i = 0; i < pos.size(); i++) {
//            if (pos[i] == '-') {
//                vector<string> next = cur;
//                next.back()[i] = 'Q';
//                getQueen(validPos(int(pos.size()), next), next, res);
//            }
//        }
//        return;
//    }
//    
//}
//
//string
//nQueens::validPos(int n,
//                  vector<string> obj){
//    // If res[i] == 'Q' cannot put queen on i
//    // If res[i] == '-' can put queen on i
//    string res = string(n, '-');
//    string lcs = res, rcs = res;
//    for (int i = 0; i < obj.size(); i++) {
//        string temp = obj[i];
//        for (int j = 0; j < n; j++) {
//            if (temp[j] == 'Q') {
//                res[j] = 'Q';
//                lcs[j] = 'Q';
//                rcs[j] = 'Q';
//            }
//        }
//        for (int j = 0; j < n; j++) {
//            if ((j + 1 < n) && (lcs[j + 1] == 'Q'))
//                lcs[j] = 'Q';
//            else
//                lcs[j] = '-';
//        }
//        for (int j = n - 1; j >= 0; j--) {
//            if ((j - 1 >= 0) && (rcs[j - 1] == 'Q'))
//                rcs[j] = 'Q';
//            else
//                rcs[j] = '-';
//        }
//    }
//    for (int i = 0; i < n; i++) {
//        if (lcs[i] == 'Q' ||
//            rcs[i] == 'Q') {
//            res[i] = 'Q';
//        }
//    }
//    return res;
//}
//
////double calPostfix(string expression){
////    double res = 0;
////    stack<double> buf;
////    for (string::iterator i = expression.begin(); i != expression.end(); i++) {
////        if () {
////            <#statements#>
////        }
////    }
////    return res;
////}
//
//vector<int> Sorting::radix_sort(vector<int> vec){
//    int maxBit = 2;
//    int i = 0;
//    int num = 0;
//    int len = (int)vec.size();
//    while (num = 0, ++i) {
//        vector<vector<int>> buf(10);
//        for (auto j: vec) {
//            num = 0;
//            if (i == 1) {
//                num = j % 10;
//                buf[num].push_back(j);
//            }
//            else{
//                num = (j / (10 * (i - 1))) % 10;
//                buf[num].push_back(j);
//            }
//        }
//        for (auto j: buf) {
//            if (j.size() == len) {
//                return j;
//            }
//            vec.insert(vec.end(), j.begin(), j.end());
//        }
//        vec.erase(vec.begin(), vec.begin() + len);
//    }
//    return vec;
//}
//
//vector<int>
//Sorting::quick_sort(vector<int> vec){
//    if (vec.size() <= 0) {
//        return vec;
//    }
//    quick_sort_help(vec, 0, (int)vec.size() - 1);
//    return vec;
//}
//
//void
//Sorting::quick_sort_help(vector<int> & vec,
//                         int low,
//                         int high){
//    if (low >= high) {
//        return;
//    }
//    int l = low;
//    int h = high;
//    int mid = vec[low];
//    while (low < high) {
//        while (low < high && mid <= vec[high]) {
//            --high;
//        }
//        vec[low] = vec[high];
//        while (low < high && vec[low] <= mid) {
//            ++low;
//        }
//        vec[high] = vec[low];
//    }
//    vec[low] = mid;
////    cout << low << "|" << high << endl;
//    quick_sort_help(vec, l, low - 1);
//    quick_sort_help(vec, low + 1, h);
//}