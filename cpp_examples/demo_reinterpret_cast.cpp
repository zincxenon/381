//  demo_reinterpret_cast.cpp
// Compiled and run in Xcode 4.5. with clang 4.1, std=c++11
//

/*
Basically, static_cast can cast between types that the compiler thinks are "related". Numerical types are related; the compiler will actually generate the machine instructions to convert between different number formats that have the same value. Also, void* is related to any pointer-to-object type.

reinterpret_cast tells the compiler to treat a bit pattern for one type as the value for another *unrelated* type. But it doesn't work for things that make no sense at the architecture level with reinterpret_cast. The compiler will disallow it if you tell it simply reinterpret the bit pattern for an int value as a double value. 

However, reinterpret_cast allows you to cast between unrelated pointer types - you tell the compiler to reinterpret the address in the pointer as the address of another type of object altogether, such casting a pointer to an integer as a pointer to a double (even if it doesn't make sense), or a pointer to an S1 type object as a pointer to an S2 type object. In addition, if you want to cast an integer to a pointer value, you have to use reinterpret_cast - they aren't considered as related types.


Finally, function pointers of different types are also "not* related; so if you want to cast a function pointer to another function pointer type, you need to use reinterpret_cast to do it. 

Remember that in C++ we don't need to play these wild casting games anywhere near as often as in C, so using reinterpret_cast is actually pretty rare.
*/

#include <iostream>
using namespace std;

// A couple of structure types
struct S1 {
    int i;
    double d;
};

struct S2 {
    double d;
    int i;
};

// a simple function to call through a pointer
int foo(const char * msg, int i)
{
    cout << msg << ' ' << i << ' ';
    return i * 2;
}

// this version of foo takes and returns void* but casts
// them to/from almost the same types as original foo
void* voidptrfoo(const void* msg_, void* i_)
{
    const char* msg = static_cast<const char*>(msg_); // this is a related pointer type
    // int i = static_cast<int>(i_); // disallowed - void* and int are not related in C++
    // int i = reinterpret_cast<int>(i_); // disallowed because on this machine, int isn't big enough to hold a pointer
    long long i = reinterpret_cast<long long>(i_); // accepted long long is big enough
        cout << msg << ' ' << i << ' ';
    // return static_cast<void*>(i * 2); // disallowed - void* and int are not related in C++
    return reinterpret_cast<void*>(i * 2); // accepted
}

int main()
{
    {
    cout << "\nExperiment with reinterpret_cast with numbers" << endl;
    int i = 42;
    double d = 3.14;
    int* ip = &i;
    double* dp = &d;
    cout << "output the integer through a pointer to integer: " << *ip << endl;
    cout << "output the double through a pointer to double: " << *dp << endl;
    
    // int i2 = reinterpret_cast<int>(d); // not allowed
    int* ip2 = reinterpret_cast<int*>(dp); // accepted
    double* dp2 = reinterpret_cast<double*>(ip); // accepted
    
    cout << "output the double through a pointer to integer: " << *ip2 << endl;
    cout << "output the integer through a pointer to double: " << *dp2 << endl;

   // int* p1 = static_cast<int*> (42); // not allowed
    int* p2 = reinterpret_cast<int*>(42); // accepted
    // cout << "what's at address 42? It is " << *p2 << endl; // run-time error - bad access
    }
    
    {
    cout << "\nExperiment with reinterpret_cast with structure types" << endl;
    S1 s1 = {42, 3.14};
    S1* s1p = &s1;
    S2 s2 = {3.14, 42};
    S2* s2p = &s2;
    
    // S2 s22 = reinterpret_cast<S2>(s1); not allowed
    
    cout << "output s1 through pointer to S1: " << s1p->i << ' ' << s1p->d << endl;
    cout << "output s2 through pointer to S2: " << s2p->d << ' ' << s2p->i << endl;
    
    // S2* s2p2 = static_cast<S2*>(s1p); // not allowed
    S2* s2p2 = reinterpret_cast<S2*>(s1p); // accepted
    cout << "output s1 through pointer to S2: " << s2p2->d << ' ' << s2p2->i << endl;
    
    S1* s1p2 = reinterpret_cast<S1*>(s2p);  // accepted
    cout << "output s2 through pointer to S1: "  << s1p2->i << ' ' << s1p2->d << endl;
    }

    {
    cout << "\nExperiment with reinterpret_cast and pointers to functions" << endl;
    int (*fp1)(const char *, int); // matches signature of foo
    fp1 = foo;
    
    cout << "output result of foo called through matching function pointer type: " << fp1("matching call", 42) << endl;
    
    double (*fp2)(int, int); // does not match signature of foo
    
    // fp2 = foo; // disallowed
    // fp2 = (int(*)(int, int))foo; // C-style cast accepted
    fp2 = reinterpret_cast<double(*)(int, int)>(foo); // accepted
    //cout << "output result of foo called through mismatching function pointer type: " << fp2(6, 42) << endl; // crashes with access error
    
    void* (*fp3)(const void*, void*);  // matches voidptrfoo prototype
    fp3 = voidptrfoo;
    cout << "output result of voidptrfoo called through matching function pointer type: "
        << fp3("matching call", reinterpret_cast<void*>(42)) << endl;
    cout << "output reinterpreted result of voidptrfoo called through matching function pointer type: "
        << reinterpret_cast<long long>(fp3("matching call", reinterpret_cast<void*>(42))) << endl;
    }
}
/* Output

Experiment with reinterpret_cast with numbers
output the integer through a pointer to integer: 42
output the double through a pointer to double: 3.14
output the double through a pointer to integer: 1374389535
output the integer through a pointer to double: 2.07508e-322

Experiment with reinterpret_cast with structure types
output s1 through pointer to S1: 42 3.14
output s2 through pointer to S2: 3.14 42
output s1 through pointer to S2: 2.07508e-322 1374389535
output s2 through pointer to S1: 1374389535 2.07508e-322

Experiment with reinterpret_cast and pointers to functions
output result of foo called through matching function pointer type: matching call 42 84
output result of voidptrfoo called through matching function pointer type: matching call 42 0x54
output reinterpreted result of voidptrfoo called through matching function pointer type: matching call 42 84
*/
