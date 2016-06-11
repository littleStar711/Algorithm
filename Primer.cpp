//
//  Primer.cpp
//  LearnCpp
//
//  Created by Wang on 3/29/16.
//  Copyright © 2016 Wang. All rights reserved.
//

#include "Primer.hpp"
int
Item_base::totalprice(int unit_sold){
    return unit_sold * price;
}

Item_base&
Item_base::operator+=(const Item_base & obj){
    isbn += obj.isbn;
    price += obj.price;
    return *this;
}

int
Bulk_item::totalprice(int unit_sold){
    return Item_base::totalprice(unit_sold) * (1 - discount);
}

Date&
Date::operator=(const Date &obj){
    this -> year = obj.year;
    this -> month = obj.month;
    this -> day = obj.day;
    return *this;
}

const pair<string, string>&
CheckoutRecord::operator[](const size_type& i) const{
    cout << "const []" << endl;
    return *wait_list[i];
}

pair<string, string>&
CheckoutRecord::operator[](size_type& i){
    cout << "non const []" << endl;
    return *wait_list[i];
}

CheckedPtr& CheckedPtr::operator--(){
    if (curr == beg) {
        throw out_of_range("decrement past begin of CheckedPtr");
    }
    --curr;
    return *this;
}

CheckedPtr& CheckedPtr::operator++(){
    if (curr == end) {
        throw out_of_range("increment past end of CheckedPtr");
    }
    ++curr;
    return *this;
}

CheckedPtr CheckedPtr::operator++(int){
    CheckedPtr res(*this);
    ++*this;
    return  res;
}

CheckedPtr CheckedPtr::operator--(int){
    CheckedPtr res(*this);
    --*this;
    return res;
}

bool operator==(const CheckedPtr& obj1, const CheckedPtr& obj2){
    return obj1.curr == obj2.curr;
}

bool operator<(const CheckedPtr& obj1, const CheckedPtr& obj2){
    if (obj1.curr < obj2.curr) {
        return true;
    }
    return false;
}

const int& CheckedPtr::operator[](const size_t& i) const{
    if (! ((curr + i < end)||
           (curr + i >= beg))) {
        throw out_of_range("[] out of range");
    }
    return *(this->curr + i);
}

int& CheckedPtr::operator[](const size_t& i){
    if (! ((curr + i < end)||
           (curr + i >= beg))) {
        throw out_of_range("[] out of range");
    }
    return *(this->curr + i);
}

int& CheckedPtr::operator*() const{
    if (curr >= end) {
        throw out_of_range("curr must less than end");
    }
    return *curr;
}



ostream& operator<<(ostream& os, const Item_base& obj){
    os << obj.isbn << "," << obj.price;
    return os;
}

ostream& operator<<(ostream& os, const Bulk_item& obj){
    os << (Item_base)obj << "," << obj.discount;
    return os;
}

ostream& operator<<(ostream& os, const HasPtr& obj){
    os << "HasPtr:" << *(obj.ptr) << ", Val " << obj.val;
    return os;
}

ostream& operator<<(ostream& os, const U_Ptr& obj){
    os << "Val:" << *(obj.ip) << ", Use:" << obj.use;
    return os;
}

ostream& operator<<(ostream& os, const Date& obj){
    os << obj.year << "-" << obj.month << "-" << obj.day;
    return os;
}

ostream& operator<<(ostream& os, const CheckoutRecord& obj){
    os << "book_id:" << obj.book_id <<
    " title:" << obj.title << ", " <<
     obj.date_borrowed << ", " << obj.date_due <<
    ", " << obj.borrower.first << " " << obj.borrower.second << endl;
    for (auto i = obj.wait_list.begin(); i != obj.wait_list.end(); i++) {
        os << (*i) -> first << ", " << (*i) -> second << endl;
    }
    return os;
}

istream& operator>>(istream& is, Date& obj){
    is >> obj.year >> obj.month >> obj.day;
    if (!is) {
        obj = Date();
    }
    return is;
}

istream& operator>>(istream& is, CheckoutRecord& obj){
    is >> obj.book_id >> obj.title >>
    obj.date_borrowed >> obj.date_due >>
    obj.borrower.first >> obj.borrower.second;
    if (!is) {
        obj = CheckoutRecord();
        return is;
    }
    obj.wait_list.clear();
    while (is.peek() != EOF) {
        pair<string, string>* temp = new pair<string, string>;
        is >> temp -> first >> temp -> second;
        if (!is) {
            return is;
        }
        obj.wait_list.push_back(temp);
    }
    return is;
}


template <typename T>
void primerprintVector(const vector<T>& vec){
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << ",";
    }
    cout << endl;
}


void
readFile(CheckoutRecord& obj){
    const string dirPath = "/Users/wang/Code/Cpp/LearnCpp/";
    const string fileName = "Checkrecord.txt";
    ifstream fin(dirPath + fileName);
    do{
        fin >> obj;
    }while (fin.peek() != EOF);
    fin.close();
}

vector<string>
readFile(const string& filePath){
    vector<string>  res;
//    try{
        ifstream fin(filePath);
        if (!fin){
            cout << "readFile !fin" << endl;
            throw overflow_error("hi err");
        }
        string temp = "";
//        vector<string>  res;
        while (getline(fin, temp)) {
            cout << temp << endl;
        }
        fin.close();
//    }catch(exception e){
//        cout << "readFile catch" << endl;
//        throw string("ERROR");
//    }
    return res;
}

void test_exception() throw (logic_error, runtime_error){
    cout << "test_exception" << endl;
}
    
void
test_autoptr(){
    int i = 22;
    int* ip = new int(11);
    cout << "ip: " << ip << ", " << *ip << endl;
    auto_ptr<int> i_ap(ip);
    cout << "ip: " << ip << ", " << *ip << endl;
    cout << &ip << "," << &i << endl;
    auto_ptr<int> i_ap2(i_ap);
    cout << "i_ap: " << i_ap2.get() << ", "<< endl;
}

void
test_cast(){
    Item_base base1("001", 20);
    Bulk_item derived1("002", 20, 0.2);
   
    Item_base* base_ptr1 = &derived1;
    Bulk_item* derived_ptr1 = dynamic_cast<Bulk_item*>(base_ptr1);
    cout << base_ptr1->totalprice(30) << endl;
    cout << derived1.totalprice(30) << endl;
    cout << derived_ptr1 -> totalprice(30) << endl;
    
    Item_base* base_ptr2 = &base1;
    Bulk_item* derived_ptr2 = dynamic_cast<Bulk_item*>(base_ptr2);
    cout << boolalpha << derived_ptr2 << endl;
    
    if (typeid(*base_ptr1) == typeid(Bulk_item))
        cout << "*base_ptr1 == Bulk_item" << endl;
    else
        cout << "*base_ptr1 != Bulk_item" << endl;
    
    if (typeid(*base_ptr2) == typeid(Bulk_item))
        cout << "*base_ptr2 == Bulk_item" << endl;
    else
        cout << "*base_ptr2 != Bulk_item" << endl;
    
    Bulk_item& ref_ptr1 = derived1;
    cout << sizeof(ref_ptr1) << endl;
}
    using namespace name1::name2;
void Matrix::toString(){
    cout << name << endl;
}
    
Matrix
name1::name2::operator*(name1::name2::Matrix&ref1,
          name1::name2::Matrix& ref2){
    cout << ref1.name << "*" << ref2.name << endl;
    return ref1;
}

singleton::base* singleton::base::ptr = nullptr;
void
singleton::test_singleton(){
    singleton::base* ptr1 = base::getInstance();
    ptr1 -> show();
    singleton::base* ptr2 = base::getInstance();
    ptr2 -> show();
}

void*
    singleton::wrap(void* args){
        base* res = base::getInstance();
        printf("%lx, addr = %lx\n", pthread_self(), res);
        pthread_exit((void*)res);
    }
    
void
    singleton::test_thread(){
        static int cnt = 3;
        pthread_t pth[cnt];
        for(int i = 0; i < cnt; i++){
            int ret = pthread_create(&pth[i], nullptr, wrap, nullptr);
        }
        for(int i = 0; i < cnt; i++){
            pthread_join(pth[i], nullptr);
        }
        cout << base::getInstance() << endl;
        pthread_exit(nullptr);
        
    }
const string stat::PRICE = "hello";
    