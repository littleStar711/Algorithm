//
//  Primer.hpp
//  LearnCpp
//
//  Created by Wang on 3/29/16.
//  Copyright © 2016 Wang. All rights reserved.
//

#ifndef Primer_hpp
#define Primer_hpp

#include <stdio.h>
#include "string"
#include "iostream"
#include "vector"
#include "fstream"
#include "Common.hpp"
#include <memory>
#include "pthread.h"
using namespace std;
class Item_base{
    friend ostream& operator<<(ostream&, const Item_base&);
public:
    Item_base(string str = "",
              int p = 0):
    isbn(str), price(p){}
    virtual int totalprice(int unit_sold);
    Item_base& operator+=(const Item_base& );
private:
    string isbn;
    int price;
};

class Bulk_item: public Item_base{
    friend ostream& operator<<(ostream&, const Bulk_item&);
public:
    Bulk_item(string str = "",
              int p = 0,
              double d = 0.0):
    Item_base(str, p), discount(d){};
    int totalprice(int unit_sold);
private:
    double discount;
};

class U_Ptr{
    friend class HasPtr;
    friend ostream& operator<<(ostream&, const U_Ptr&);
    int *ip;
    size_t use;
    U_Ptr(int *p): ip(p), use(1){}
    ~U_Ptr(){delete ip;}
};

class HasPtr{
    friend ostream& operator<<(ostream& os, const HasPtr&);
public:
    HasPtr(int *p, int v):ptr(new U_Ptr(p)), val(v){}
    HasPtr(const HasPtr& obj): ptr(obj.ptr), val(obj.val){
        ++ptr -> use;
    }
    HasPtr& operator=(const HasPtr& obj){
        ++obj.ptr->use;
        if (--ptr->use == 0) {
            delete ptr;
        }
        ptr = obj.ptr;
        val = obj.val;
        return *this;
    }
    ~HasPtr(){
        if (--ptr->use == 0) {
            delete ptr;
        }
    }
private:
    U_Ptr *ptr;
    int val;
};

class Date{
    friend ostream& operator<<(ostream&, const Date&);
    friend istream& operator>>(istream&, Date&);
public:
    Date(int y = 1900, int m = 1, int d = 1):
    year(y), month(m), day(d){}
    Date& operator=(const Date&);
private:
    int year;
    int month;
    int day;
};

class CheckoutRecord{
    friend ostream& operator<<(ostream&, const CheckoutRecord&);
    friend istream& operator>>(istream&, CheckoutRecord&);
public:
    typedef vector<pair<string, string>*>::size_type size_type;
    CheckoutRecord(double d = 0,
                   string t = "NULL",
                   Date d1 = Date(),
                   Date d2 = Date()):
    book_id(d), title(t), date_borrowed(d1), date_due(d2){}
    pair<string, string>& operator[](size_type& i);
    const pair<string, string>& operator[](const size_type& i) const;
private:
    double book_id;
    string title;
    Date date_borrowed;
    Date date_due;
    pair<string, string> borrower;
    vector<pair<string, string>*> wait_list;
};

class CheckedPtr{
    friend bool operator==(const CheckedPtr&, const CheckedPtr&);
    friend bool operator<(const CheckedPtr&, const CheckedPtr&);
    friend const CheckedPtr operator+(const CheckedPtr&, const CheckedPtr&);
    friend const CheckedPtr operator-(const CheckedPtr&, const CheckedPtr&);
public:
    CheckedPtr(int* b, int* e): beg(b), end(e), curr(b){}
    CheckedPtr& operator++();
    CheckedPtr& operator--();
    CheckedPtr operator++(int);
    CheckedPtr operator--(int);
    int& operator[](const size_t& i);
    const int& operator[](const size_t& i) const;
    int& operator*() const;
private:
    int* beg;
    int* end;
    int* curr;
};

template<typename T>
class myStack{
public:
    myStack();
    void push(const T&);
    void pop();
    T& top();
    bool empty();
    size_t size();
    size_t capacity();
private:
    void allocate();
    T* ptr;
    size_t num;
    size_t cap;
};

template <typename T>
myStack<T>::myStack() {
    num = 1;
    cap = num;
    ptr = new T[num];
}

template <typename T>
void myStack<T>::allocate() {
    T* res = new T[cap << 1];
    for (int i = 0; i < cap; i++) {
        res[i] = ptr[i];
    }
    delete []ptr;
    ptr = res;
    cap <<= 1;
}

template<typename T>
void myStack<T>::push(const T& obj){
    if (num == cap) {
        allocate();
    }
    ptr[num++] = obj;
}

template<typename T>
void myStack<T>::pop(){
    --num;
}

template<typename T>
T& myStack<T>::top(){
    return ptr[num - 1];
}

template<typename T>
size_t myStack<T>::size(){
    return num;
}

template<typename T>
size_t myStack<T>::capacity(){
    return cap;
}

ostream& operator<<(ostream& os, const Item_base& obj);
ostream& operator<<(ostream& os, const Bulk_item& obj);
ostream& operator<<(ostream& os, const HasPtr& obj);
ostream& operator<<(ostream& os, const U_Ptr& obj);
ostream& operator<<(ostream& os, const Date& obj);
ostream& operator<<(ostream& os, const CheckoutRecord& obj);
istream& operator>>(istream&, const Date&);
istream& operator>>(istream& is, CheckoutRecord& obj);
bool operator==(const CheckedPtr&, const CheckedPtr&);
bool operator<(const CheckedPtr&, const CheckedPtr&);
const CheckedPtr& operator+(CheckedPtr&, const CheckedPtr&);
const CheckedPtr& operator-(CheckedPtr&, const CheckedPtr&);

template <typename T>
void primerprintVector(const vector<T>&);

void
readFile(CheckoutRecord& obj);

vector<string>
readFile(const string& fillePath);

void
test_autoptr();

void
test_cast();

void
test_exception() throw (logic_error, runtime_error);

namespace name1 {
    namespace name2 {
        class Matrix{
        public:
            void toString();
            string name;
        };
        Matrix operator*(Matrix &, Matrix&);
    }
}
namespace multiderive{
    typedef void  (*fp)(void);
    class Base2{
    public:
        Base2(){cout << "Base2()" << endl;}
        virtual ~Base2(){cout << "~Base2()" << endl;}
        void print(){cout << "Base2 print()" << endl;}
    };
    class Base1{
    public:
        Base1(){cout << "Base1()" << endl;}
        virtual ~Base1(){cout << "~Base1()" << endl;}
        virtual void A(){cout << "Base1 A() "<< endl;}
        void B(){cout << "Base B()"<< endl;}
        void C(){cout << "Base C()"<< endl;}
        int ival;
        Base2 obj1;
        class nestClass{
        public:
            nestClass(){cout << "nestClass()" << endl;}
            ~nestClass(){cout << "~nestClass()" << endl;}
        };
    };
    class Derived1: public virtual Base1{
    public:
        Derived1(){cout << "Derived1()" << endl;}
        virtual ~Derived1(){cout << "~Derived1()" << endl;}
        void A(int i){cout << "Derived1 A(int i)" << endl;}
        void A(){cout << "Derived1 A()" << endl;}
        void B(){cout << "Derived1 B()" << endl;}
        void D(){cout << "Derived1 D()" << endl;}
        int ival;
    };

    class Derived2: public Base1{
    public:
        Derived2(){cout << "Derived2()" << endl;}
        virtual ~Derived2(){cout << "~Derived2()" << endl;}
        void print(string str){cout << "Derived2 print()" << endl;}
    };
    class MI: public Derived1, public Derived2{
    public:
        MI(){cout << "MI()" << endl;}
        virtual ~MI(){cout << "~MI()" << endl;}
//        void print(){cout << "MI print()" << endl;}
    };
}

namespace singleton {
    class base{
    public:
        static base* getInstance(){
            if (ptr == nullptr) {
                    ptr = new base();
            }
            return ptr;
        }
        static base* ptr;
        void show(){
            cout << "show() " << this << ", " << name << endl;
        }
    private:
        string name;
        base():name("wang"){cout << "base()" << endl;};
    };
    
    void test_singleton();
    void test_thread();
    void* wrap(void* args);
}

class stat{
public:
    static const string PRICE;
};

//const string stat::PRICE = "hello";

#endif /* Primer_hpp */
