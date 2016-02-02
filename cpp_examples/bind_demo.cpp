/*
    Ran with Xcode 4.4.1 with Clang c++11 and libc++
    and with CAEN gcc 4.7.0 -std=C++11, identical outputs 9/14/2012
*/

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <utility>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

class Thing {
public:
    Thing(int in_i = 0) : i(in_i) {}    // need  default ctor for map container
    void print() const                  // a const member function
        {cout << "Thing " << i << endl;}
    void write(ostream& os) const   // write to a supplied ostream
        {os << "Thing" << i << " written to stream" << endl;}
    void print1arg(int j) const         // a const member function with 1 argument
        {cout << "Thing " << i << " with arg " << j << endl;}
    void print2arg(int j, int k) const  // a const member function with 2 arguments
        {cout << "Thing " << i << " with args " << j << ' ' << k << endl;}
    void update()                       // a modifying function with no arguments
        {i++; cout << "Thing updated to " << i << endl;}
    void set_value(int in_i)            // a modifying function with one arguments
        {i = in_i; cout << "Thing value set to " << i << endl;}
    int get_value() const
        {return i;}
private:
    int i;
};

ostream& operator<< (ostream& os, const Thing& t)
{
    os << "Thing: " << t.get_value();
    return os;
}

// Non-member functions that have a Thing parameter
void print_Thing(Thing t)
{
    t.print();
}

void print_Thing_ref(Thing& t)
{
    t.print();
}

void update_Thing(Thing& t)
{
    t.update();
}
void set_Thing(Thing& t, int i)
{
    t.set_value(i);
}

void print_Thing_const_ref(const Thing& t)
{
    t.print();
}

void print_int_Thing(int i, Thing t)
{
    cout << "print_int_Thing " << i << ' ' << t << endl;
}

void print_Thing_int(Thing t, int i)
{
    cout << "print_Thing_int " << t << ' ' << i << endl;
}

void print_Thing_int_int(Thing t, int i, int j)
{
    cout << "print_Thing_int_int " << t << ' ' << i << ' ' << j << endl;
}

void print_Thing_ptr(Thing* t)
{
    t->print();
}

struct print_Thing_FOC {
    void operator() (Thing * t)
        {t->print();}
};

void print_Thing_ptr_const(const Thing* t)
{
    t->print();
}

void print_int_Thing_ptr(int i, Thing* t)
{
    cout << "print_int_Thing_ptr " << i << ' ' << *t << endl;
}

void print_Thing_ptr_int_int(Thing* t, int i, int j)
{
    cout << "print_Thing_ptr_int " << *t << ' ' << i << ' ' << j << endl;
}

// simple integer demo functions
int sum3(int x, int y, int z) 
{
    int sum = x+y+z;
    cout << x << '+' << y << '+' << z << '=' << sum << endl;
    return sum;
}

void mod23(int x, int & y, int & z)
{
    cout << "mod23 input: " << x << ' ' << y << ' ' << z << endl;
    y = y + x;
    z = z + y;
    cout << "mod23 output: "<< x << ' ' << y << ' ' << z << endl;
}
    
void print_int(int x)
{
    cout << x << endl;
}

void write_int(ostream& os, int x)
{
    os << x << endl;
}

void modify_int(int & i)
{
    i += 5;
    cout << "i modified to " << i << endl;
}

int return_an_int()
{
    static int i = 1;
    return i++;
}

    
void demo_examples();
void demo_with_int();
void demo_with_obj();
void demo_with_ptr();
void demo_with_int_list();
void demo_with_obj_list();
void demo_with_ptr_list();
void demo_with_obj_map();
void demo_with_ptr_map();


int main()
{
    demo_examples();
    demo_with_int();
    demo_with_obj();
    demo_with_ptr();
    demo_with_int_list();
    demo_with_obj_list();
    demo_with_ptr_list();
    demo_with_obj_map();
    demo_with_ptr_map();
    cout << "done!" << endl;
}

void demo_examples()
{
    int int1 = 1;
    int int2 = 2;
    int int3 = 3;
    int result;
    cout << "\n\ndemo of bind with read-only integer variables and constants" << endl;
    result = bind(sum3, 10, 20, 30)();
    cout << "result is " << result << endl;
    result = bind(sum3, int1, int2, int3)();
    cout << "result is " << result << endl;
//  result = bind(sum3)(int1, int2, int3);      // error: no. of bound arguments must == no. of function arguments
    result = bind(sum3, _1, _2, _3)(100, 200, 300);
    cout << "result is " << result << endl;
    result = bind(sum3, _1, _2, _3)(int1, int2, int3);
    cout << "result is " << result << endl;
    cout << int1 << ' ' << int2 << ' ' << int3 << endl;
    int x = 6;
    result = bind(sum3, int1, bind(sum3, _1, int2, int3), int3)(x);
    cout << "result from nested bind is " << result << endl;    
    
    /* concept here is that bound arguments are copied into internal variables in the function object, 
    but call arguments are forwarded! */
    
    cout << "\n\ndemo of bind with function that modifies parameters" << endl;
    // below tries to modify constants - error!
//  bind(mod23, int1, _1, _2)(100, 200);
//  bind(mod23, 10, 20, ref(30))();
    cout << int1 << ' ' << int2 << ' ' << int3 << endl;
    bind(mod23, int1, int2, int3)();
    cout << int1 << ' ' << int2 << ' ' << int3 << endl;
    bind(mod23, int1, int2, ref(int3))();
    cout << int1 << ' ' << int2 << ' ' << int3 << endl;
    // call parameters were passed in by reference
    bind(mod23, int1, _1, _2)(int2, int3);
    cout << int1 << ' ' << int2 << ' ' << int3 << endl;
    bind(mod23, _3, _1, _2)(int2, int3, int1);
    cout << int1 << ' ' << int2 << ' ' << int3 << endl;
    // modifications are made to the stored values, so no problem here
    bind(mod23, 10, 20, 30)(); // copies the values in!
  
    cout << "\n\ndemo of bind with ref bound argument to hand in cout argument" << endl;
//    bind(write_int, cout, _1)(int1);  // why isn't this forwarded? - because it is copied!
    bind(write_int, ref(cout), _1)(int1);
    cout << "demo of bind with cout call argument" << endl;
    bind(write_int, _1, int1)(cout);
    cout << "demo of bind with cout and int literal call argument" << endl;
    bind(write_int, _1, _2)(cout, 6);
    
    cout << "\n\ndemo with rvalues for call argument" << endl;
    bind(write_int, ref(cout), _1) (int1 + 3);
    bind(write_int, ref(cout), _1) (return_an_int());
    bind(write_int, ref(cout), _1) (return_an_int());
    //  bind(mod23, int1, _1, _2)(return_an_int(), int3); // can't store in an rvalue
    //  bind(mod23, int1, _1, _2)((int2+3), int3); // can't store in an rvalue
    bind(mod23, _1, int2, _2)(return_an_int(), int3);
    cout << "\n\ndemo with rvalues for bound argument" << endl;
    bind(write_int, ref(cout), (int1 + 3)) ();
//    bind(write_int, ref(cout), ref(int1 + 3))) ();  // cana't do a reference to rvalue here
    bind(write_int, ref(cout), return_an_int()) ();


}

void demo_with_int()
{
    cout << "\n\ndemo of bind with modifying single-parameter function" << endl;
    int int1 = 42;
    int int2 = 76;
//  int int3 = 88;
    
    // copy of value is stored in the function object
    bind(modify_int, int1)();
    cout << "int1 is now " << int1 << endl;

    // a reference to the variable is stored in the function object
    bind(modify_int, ref(int1))();
    cout << "int1 is now " << int1 << endl;
    
    // the function object takes the call arguments by reference
    bind(modify_int, _1)(int2);
    cout << "int2 is now " << int2 << endl;
    
    // constants can be used for the bound arguments, but not the call arguments
    // following is OK
    bind(modify_int, 12)();
    // following produces error
//  bind(modify_int, ref(12))();
    // following produces error
//  bind(modify_int, _1)(12);

}

void demo_with_obj()
{
    int int1 = 42;
    int int2 = 76;
    int int3 = 88;
    Thing t1(1);
    cout << "\n\n\nUsing a single Thing object" << endl;
    cout << "Output from print const member functions before and after applying update and set_value modifying member functions" << endl;
    bind(&Thing::print, t1)();  // t1 is operated on by reference, and so gets modified
    bind(&Thing::print, _1)(t1);    // t1 is operated on by reference, and so gets modified
    bind(&Thing::update, t1)();     // modify a copy of t1
    bind(&Thing::print, _1)(t1);    // t1 is operated on by reference, and so gets modified
    bind(&Thing::update, ref(t1))();// t1 is operated on by reference, and so gets modified
    bind(&Thing::print, _1)(t1);    // t1 is operated on by reference, and so gets modified
    bind(&Thing::update, _1)(t1);   // t1 is operated on by reference, and so gets modified
    bind(&Thing::print, _1)(t1);
    bind(&Thing::set_value, _1, int1)(t1);
    bind(&Thing::print, _1)(t1);
    bind(&Thing::set_value, _1, int2)(t1);
    bind(&Thing::print, _1)(t1);
    bind(&Thing::set_value, _1, int1)(t1);
    bind(&Thing::print1arg, _1, _2)(t1, int2);
    bind(&Thing::print2arg, _2, _1, _3)(int3, t1, int2);
    
//  bind(&Thing::write, _1, cout)(t1);  // tries to copy cout, which isn't allowed
    bind(&Thing::write, _1, ref(cout))(t1);

    
    bind(&print_Thing, t1)();       // call non-member functions
    bind(&print_Thing_ref, t1)();
    bind(&print_Thing_const_ref, t1)();
    bind(&print_int_Thing, int3, t1)();
    
    
    bind(&print_Thing, _1)(t1);     // call non-member functions
    bind(&print_Thing_ref, _1)(t1);
    bind(&print_Thing_const_ref, _1)(t1);
    bind(&print_int_Thing, _1, _2)(int3, t1);
    
    bind(&update_Thing, t1)();  // modify a copy of t1
    bind(&update_Thing, ref(t1))(); // modify original t1
    bind(&update_Thing, _1)(t1); // modify original t1

    bind(&set_Thing, t1, int2)();   // modify a copy of t1
    bind(&set_Thing, ref(t1), int2)(); // modify original t1
    bind(&set_Thing, _1, _2)(t1, int2); // modify original t1

}

void demo_with_ptr()
{
    int int1 = 42;
    int int2 = 76;
    int int3 = 88;
    Thing t1(1);
    Thing * ptr = &t1;
    cout << "\n\n\nUsing a single pointer to Thing" << endl;
    cout << "Output from print const member functions before and after applying update and set_value modifying member functions" << endl;
    bind(&Thing::print, _1)(ptr);
    bind(&Thing::update, _1)(ptr);
    bind(&Thing::set_value, _1, int1)(ptr);
    bind(&Thing::print, _1)(ptr);
    bind(&Thing::set_value, _1, int2)(ptr);
    bind(&Thing::print, _1)(ptr);
    bind(&Thing::set_value, _1, int1)(ptr);
    bind(&Thing::print1arg, _1, _2)(ptr, int2);
    bind(&Thing::print2arg, _2, _1, _3)(int3, ptr, int2);
}

void demo_with_int_list()
{
    list<int> int_list = {1, 2, 3};
/*  int_list.push_back(1);
    int_list.push_back(2);
    int_list.push_back(3);
*/  
    for_each(int_list.begin(), int_list.end(), bind(sum3, _1, 5, 9) );
    for_each(int_list.begin(), int_list.end(), print_int);
    for_each(int_list.begin(), int_list.end(), bind(mod23, 1, 2, _1) );
    for_each(int_list.begin(), int_list.end(), print_int );
    
    cout << "Using bind on list<int> to call write_int with cout argument" << endl;
    for_each(int_list.begin(), int_list.end(), bind(&write_int, ref(cout), _1) );

}

void demo_with_obj_list()
{
    int int1 = 42;
    int int2 = 76;
    Thing t1(1), t2(2), t3(3);
    typedef list<Thing> olist_t;
    olist_t obj_list = {t1, t2, t3};
/*  obj_list.push_back(t1);
    obj_list.push_back(t2);
    obj_list.push_back(t3); */
    
    for_each(obj_list.begin(), obj_list.end(), bind(print_Thing, _1) );
    for_each(obj_list.begin(), obj_list.end(), bind(print_Thing_int_int, _1, int1, int2) );
    for_each(obj_list.begin(), obj_list.end(), bind(update_Thing, _1) );
    for_each(obj_list.begin(), obj_list.end(), bind(set_Thing, _1, int1) );
        
    bind(&Thing::print, _1)(t1);

    cout << "\n\n\nUsing list<Thing> container" << endl;
    cout << "Using bind on obj_list to call Thing::print" << endl;
    for_each(obj_list.begin(), obj_list.end(), bind(&Thing::print, _1) );
    cout << "Using bind on obj_list to call Thing::print2arg" << endl;
    for_each(obj_list.begin(), obj_list.end(), bind(&Thing::print2arg, _1, int1, int2) );
    
    cout << "Using bind on obj_list to call Thing::write with cout argument" << endl;
    for_each(obj_list.begin(), obj_list.end(), bind(&Thing::write, _1, ref(cout)) );

    
    cout << "Using mem_fn on obj_list to call Thing::print and update" << endl;
    for_each(obj_list.begin(), obj_list.end(), mem_fn(&Thing::print) );     // use instead of mem_fun and mem_fun_ref
    for_each(obj_list.begin(), obj_list.end(), mem_fn(&Thing::update) );
    for_each(obj_list.begin(), obj_list.end(), mem_fn(&Thing::print) );

    cout << "Using bind on obj_list to call Thing::print and update" << endl;
    for_each(obj_list.begin(), obj_list.end(), bind(&Thing::print, _1) );
    for_each(obj_list.begin(), obj_list.end(), bind(&Thing::update, _1) );
    for_each(obj_list.begin(), obj_list.end(), bind(&Thing::print, _1) );
    
    cout << "Using bind on obj_list to call Thing::print and Thing::set_value" << endl;
    for_each(obj_list.begin(), obj_list.end(), bind(&Thing::print, _1) );
    for_each(obj_list.begin(), obj_list.end(), bind(&Thing::set_value, _1, int1) );
    for_each(obj_list.begin(), obj_list.end(), bind(&Thing::print, _1) );
}
    
void demo_with_ptr_list()
{
    int int1 = 42;
    int int2 = 76;
    Thing t1(1), t2(2), t3(3);
    typedef list<Thing *> plist_t;
    plist_t ptr_list;
    ptr_list.push_back(&t1);
    ptr_list.push_back(&t2);
    ptr_list.push_back(&t3);

    cout << "\n\n\nUsing list<Thing *> container" << endl;
    cout << "Using bind on ptr_list for print" << endl;
    for_each(ptr_list.begin(), ptr_list.end(), bind(&Thing::print, _1) );
    cout << "Using bind on ptr_list to call Thing::print2arg" << endl;
    for_each(ptr_list.begin(), ptr_list.end(), bind(&Thing::print2arg, _1, int1, int2) );

 /*   cout << "Using mem_fn on ptr_list" << endl;
    for_each(ptr_list.begin(), ptr_list.end(), mem_fn(&Thing::print) );     // use instead of mem_fun and mem_fun_ref
    for_each(ptr_list.begin(), ptr_list.end(), mem_fn(&Thing::update) );
    for_each(ptr_list.begin(), ptr_list.end(), mem_fn(&Thing::print) );
*/  
    cout << "Using bind on ptr_list to call Thing::update" << endl;
    for_each(ptr_list.begin(), ptr_list.end(), bind(&Thing::update, _1) );
    cout << "Using bind on ptr_list for set_value" << endl;
    for_each(ptr_list.begin(), ptr_list.end(), bind(&Thing::print, _1) );
    for_each(ptr_list.begin(), ptr_list.end(), bind(&Thing::set_value, _1, int1) );
    for_each(ptr_list.begin(), ptr_list.end(), bind(&Thing::print, _1) );
    
    cout << "Using bind on ptr_list to call Thing::write with cout argument" << endl;
    for_each(ptr_list.begin(), ptr_list.end(), bind(&Thing::write, _1, ref(cout)) );

}

void demo_with_obj_map()
{
    int int1 = 42;
//  int int2 = 76;
    Thing t1(1), t2(2), t3(3);
    typedef map<int, Thing> omap_t; //typedef for clarity
    omap_t obj_map;
    obj_map[1] = t1;    // a COPY of t1 is in the container!
    obj_map[2] = t2;
    obj_map[3] = t3;
    
    cout << "\n\n\nUsing map<int, Thing> container" << endl;
                
    cout << "Output from using bind of print to bind of second" << endl;
    // The type of the extracted second of the dereferenced iterator must be specified with the template parameter of bind.
    
    // For a const member function, the type of the extracted second can be either const Thing or Thing
    for_each(obj_map.begin(), obj_map.end(), bind(&Thing::print, bind(&omap_t::value_type::second, _1)) );
    cout << "Output from using bind of print1arg and print2arg to bind of second" << endl;
    // the first argument always has to be the "this" from the map container, but additional values can be supplied with bind
    for_each(obj_map.begin(), obj_map.end(), bind(&Thing::print1arg, bind(&omap_t::value_type::second, _1), int1) );
    cout << "Output from using bind of non-modifying ordinary function to bind of second" << endl;
    for_each(obj_map.begin(), obj_map.end(), bind(print_Thing, bind(&omap_t::value_type::second, _1)) );
    for_each(obj_map.begin(), obj_map.end(), bind(print_Thing_const_ref, bind(&omap_t::value_type::second, _1)) );
    cout << "Output from using bind of modifying member function to bind of second" << endl;
    for_each(obj_map.begin(), obj_map.end(), bind(&Thing::update, bind(&omap_t::value_type::second, _1)) );
    for_each(obj_map.begin(), obj_map.end(), bind(&Thing::print, bind(&omap_t::value_type::second, _1)) );
    cout << "Output from using bind of modifying ordinary function to bind of second" << endl;
    for_each(obj_map.begin(), obj_map.end(), bind(&update_Thing, bind(&omap_t::value_type::second, _1)) );
    for_each(obj_map.begin(), obj_map.end(), bind(&Thing::print, bind(&omap_t::value_type::second, _1)) );

    cout << "Output from using bind of Thing::write to bind of second with cout argument" << endl;
    for_each(obj_map.begin(), obj_map.end(), 
        bind(&Thing::write, 
            bind(&omap_t::value_type::second, _1), ref(cout)) );
    
}

void demo_with_ptr_map()
{
    int int1 = 42;
    int int2 = 76;
    Thing t1(1), t2(2), t3(3);
    typedef map<int, Thing *> pmap_t;   //typedef for clarity
    pmap_t ptr_map;
    ptr_map[1] = &t1;
    ptr_map[2] = &t2;
    ptr_map[3] = &t3;
        
    cout << "\n\n\nUsing map<int, Thing *> container" << endl;
    cout << "Output from print const member functions before and after applying update and set_value modifying member functions" << endl;
    for_each(ptr_map.begin(), ptr_map.end(), bind(&Thing::print, bind(&pmap_t::value_type::second, _1)) );
    // the first argument always has to be the "this" from the map container, but additional values can be supplied with bind
    for_each(ptr_map.begin(), ptr_map.end(), bind(&Thing::print1arg, bind(&pmap_t::value_type::second, _1), int1) );
    for_each(ptr_map.begin(), ptr_map.end(), bind(&Thing::print2arg, bind(&pmap_t::value_type::second, _1), int1, int2) );
    for_each(ptr_map.begin(), ptr_map.end(), bind(&Thing::update, bind(&pmap_t::value_type::second, _1)) );
    // show the result
    for_each(ptr_map.begin(), ptr_map.end(), bind(&Thing::print, bind(&pmap_t::value_type::second, _1)) );
    for_each(ptr_map.begin(), ptr_map.end(), bind(&Thing::set_value, bind(&pmap_t::value_type::second, _1), int1) );
    for_each(ptr_map.begin(), ptr_map.end(), bind(&Thing::print, bind(&pmap_t::value_type::second, _1)) );

    // calls to ordinary functions that take different parameter types
    for_each(ptr_map.begin(), ptr_map.end(), bind(&print_Thing_ptr, bind(&pmap_t::value_type::second, _1)) );
    for_each(ptr_map.begin(), ptr_map.end(), bind(&print_Thing_ptr_const, bind(&pmap_t::value_type::second, _1)) );
    for_each(ptr_map.begin(), ptr_map.end(), bind(&print_Thing_ptr_int_int, bind(&pmap_t::value_type::second, _1), int1, int2) );

    // use a Std. typedef for less container-specific code
    for_each(ptr_map.begin(), ptr_map.end(), 
        bind(&Thing::print, 
            bind(&pmap_t::value_type::second, _1)) );
            
    cout << "Output from using bind of Thing::write to bind of second with cout argument" << endl;
    for_each(ptr_map.begin(), ptr_map.end(), 
        bind(&Thing::write, 
            bind(&pmap_t::value_type::second, _1), ref(cout)) );


}
    
