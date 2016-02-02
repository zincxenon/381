/*
 *  VMI_demo.cpp
 *  Test
 *
 *  Created by David Kieras on 11/4/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include <iostream>
using namespace std;

class B {
public:
	B() : i(0)
		{cout << "B " << i << " default ctor" << endl;}
	B(int i_) : i(i_)
		{cout << "B ctor arg is " << i << endl;}
	void print() {cout << "B has " << i << endl;}
    virtual void avf() {cout << "B avf called" << endl;}
private:
	int i;
};

class D1 : virtual public B {
public:
	D1() : j(-1) {}
	D1(int i_, int j_) : B(i_), j(j_)
		{cout << "D1 ctor args are " << i_ << " for B, and " << j_ << endl;}
	void print() {cout << "D1 has " << j << endl;}
    void avf() override {cout << "D1 avf called" << endl;}
private:
	int j;
};

class D2 : virtual public B {
public:
    D2() : j(-2) {}
	D2(int i_, int j_) : B(i_), j(j_)
		{cout << "D2 ctor args are " << i_ << " for B, and " << j_ << endl;}
	void print() {cout << "D2 has " << j << endl;}
    void avf() override {cout << "D2 avf called" << endl;}  // causes error at declaration of DD
private:
	int j;
};

class DD : public D1, public D2 {
public:
    DD() : m(-3) {}
	DD(int i_, int j_, int k_, int m_) : B(99), D1(i_, j_), D2(i_, k_), m(m_)
		{cout << "DD ctor args are " << i_ << ", " <<  j_ << " for D1, and "<< i_ << ", "<< k_ << " for D2, and "<< m_ << endl;}
	void print() {cout << "DD has " << m << endl;}
    void avf() override {cout << "DD avf called" << endl;}  // causes error at declaration of DD
private:
	int m;
};

class DDD : public DD {
public:
    DDD() : n(-4) {}
	DDD(int i_, int j_, int k_, int m_, int n_) : B(999), DD(i_, j_, k_, m_), n(n_)
		{cout << "DDD ctor args are " << i_ << ", " << j_ << ", " << k_ << ", " << m_ << " for DD, and " << n_ << endl;}
	void print() {cout << "DDD has " << n << endl;}
    void avf() override {cout << "DDD avf called" << endl;}  // causes error at declaration of DD
private:
	int n;
};


int main()
{
    // default construction
{
    cout << "Demo of default construction" << endl;
    cout << "\nB b;" << endl;
	B  b;
	b.print();
    
	cout << "\nD1 d1;" << endl;
	D1 d1;
	d1.B::print();
	d1.print();
    
	cout << "\nD2 d2;" << endl;
	D2 d2;
	d2.B::print();
	d2.print();
    
	cout << "\nDD dd;" << endl;
	DD dd;
	dd.B::print();
	dd.D1::print();
	dd.D2::print();
	dd.print();
    
}

{
    cout << "\nDemo of non-default construction" << endl;
    cout << "\nB  b(0);" << endl;
	B  b(0);
	b.print();

	cout << "\nD1 d1(10, 11);" << endl;
	D1 d1(10, 11);
	d1.B::print();
	d1.print();

	cout << "\nD2 d2(20, 22);" << endl;
	D2 d2(20, 22);
	d2.B::print();
	d2.print();

	cout << "\nDD dd(30, 32, 33, 333);" << endl;
	DD dd(30, 32, 33, 333);
	dd.B::print();
	dd.D1::print();
	dd.D2::print();
	dd.print();
	
	cout << "\nDDD ddd(40, 42, 43, 444, 4444)" << endl;
	DDD ddd(40, 42, 43, 444, 4444);
	ddd.B::print();
	ddd.D1::print();
	ddd.D2::print();
	ddd.DD::print();
	ddd.print();

    cout << "\nDemo of virtual function calls" << endl;
    B* p = &b;
    p->avf();
    p = &d1;
    p->avf();
    p = &d2;
    p->avf();
    p = &dd;
    p->avf();
    p = &ddd;
    p->avf();


}
	cout << "done" << endl;
}
/*
B  b(0);
B ctor arg is 0
B has 0

D1 d1(10, 11);
B ctor arg is 10
D1 ctor args are 10 for B, and 11
B has 10
D1 has 11

D2 d2(20, 22);
B ctor arg is 20
D2 ctor args are 20 for B, and 22
B has 20
D2 has 22

DD dd(30, 32, 33, 333);
B ctor arg is 99
D1 ctor args are 30 for B, and 32
D2 ctor args are 30 for B, and 33
DD ctor args are 30, 32 for D1, and 30, 33 for D2, and 333
B has 99
D1 has 32
D2 has 33
DD has 333

DDD ddd(40, 42, 43, 444, 4444)
B ctor arg is 999
D1 ctor args are 40 for B, and 42
D2 ctor args are 40 for B, and 43
DD ctor args are 40, 42 for D1, and 40, 43 for D2, and 444
DDD ctor args are 40, 42, 43, 444 for DD, and 4444
B has 999
D1 has 42
D2 has 43
DD has 444
DDD has 4444

Demo of virtual function calls
B avf called
D1 avf called
D2 avf called
DD avf called
DDD avf called
done
*/

