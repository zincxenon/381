/* Demo of unique_ptr
In summary: 
A unique_ptr has sole ownership of the pointed-to object. It has no
copy constructor or copy assignment. It does have a move constructor
and move assignment. This means that rvalue unique_ptrs can have their
ownership moved implicitly, but not lvalue unique_ptrs. 
This means that a unique_ptr can be assigned to the unique_ptr returned
from a function, but you can't assign one declared unique_ptr to another.

But if you invoke a move assignment (with std::move) you can assign them, 
but the lhs unique_ptr now owns the object and the rhs now owns nothing.

The standard container insert functions will move a rvalue unique_ptr in;
You have to explicitly move an lvalue in otherwise with std::move.
but their accessor functions will not move a unique_ptr out. But you
can use the accessor as a way to use the pointer.

By explicitly invoking a move (with std::move) you can use a container
accessor to move ownership out into another unique_ptr.  The unique_ptr 
remains in the container, but it now owns nothing.


*/

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <string>

using namespace std;


class Thing {
public:
	Thing() : i (++count) {cout << "Thing " << i << " creation" << endl;}
	~Thing () {cout << "Thing " << i << " destruction" << endl;}
	int get_i() const {return i;}
private:
	int i;
	static int count;
};

int Thing::count = 0;

// create a Thing, but return a unique_ptr to it - transfer of ownership is the concept
unique_ptr<Thing> create_Thing()
{
	unique_ptr<Thing> p (new Thing);
	
	cout << "in create_Thing: p points to Thing " << p->get_i() << endl;
    // unique_ptr<Thing> p2(p); // error: copy construction not allowed
    unique_ptr<Thing> p3;
    // p3 = p;  // error: copy assignment not allowed.

	return p;
}

/*
void take_it(unique_ptr<Thing> p)
{
	cout << "in take_it: p points to Thing " << p->get_i() << endl;
    cout << "leaving take_it" << endl;
}
*/

void refer_to_it(unique_ptr<Thing>& p)
{
	cout << "in refer_to_it: p points to Thing " << p->get_i() << endl;
    cout << "leaving refer_to_it" << endl;
}
    
void take_it(unique_ptr<Thing> p)
{
	cout << "in take_it: p points to Thing " << p->get_i() << endl;
    cout << "leaving take_it" << endl;
}
    

int main()
{
    // Scope 1: in a scope, let's create a Thing owned by a unique ptr, then leave the scope.
    {
        cout << "\nEntering main scope 1" << endl;
        unique_ptr<Thing> p = create_Thing();
	
        cout << "in main scope 1: p points to Thing " << p->get_i() << endl;
        unique_ptr<Thing> p2;

        cout << "Leaving main scope 1" << endl;
    }
    
    // Scope 2: create another Thing, give it to function that refers to it - seems odd.
    {
        cout << "\nEntering main scope 2" << endl;
        unique_ptr<Thing> p = create_Thing();
        cout << "in main scope 2: p points to Thing " << p->get_i() << endl;
    
        refer_to_it(p);
 
        // does p still own anything?
        if(p)
            cout << "in main scope 2: p points to Thing " << p->get_i() << endl;
        else
            cout << "in main scope 2: p points to nothing" << endl;
        cout << "Leaving main scope 2" << endl;
    }
    
    // Scope 3: create another Thing, give it (and ownership to a function, which "keeps" it.
    {
        cout << "\nEntering main scope 3" << endl;
        unique_ptr<Thing> p = create_Thing();
        cout << "in main scope 3: p points to Thing " << p->get_i() << endl;
    
        // take_it(p); // error - can't copy it as function argument
        take_it(std::move(p)); // move ownership to take_it function
 
        // does p still own anything?
        if(p)
            cout << "in main scope 3: p points to Thing " << p->get_i() << endl;
        else
            cout << "in main scope 3: p points to nothing" << endl;
         cout << "Leaving main scope 3" << endl;
   }
    
    // Scope 4: create some Things, pointed to with unique_ptr, and store them in a vector
    {
        cout << "\nEntering main scope 4" << endl;
        vector<unique_ptr<Thing>> v;
  //      for(int i = 0; i < 4; i++)
  //          v.push_back(create_Thing());
        for(int i = 0; i < 4; i++) {
            unique_ptr<Thing> p (new Thing);
  //          v.push_back(p);
            v.push_back(std::move(p));  // apparently is moved in ...
   //         v.push_back(new Thing);  // compile error  - odd won't construct the unique_ptr ...
            }
        // use it while still in the container
        cout << "in main scope 4: v[1] points to Thing " << v[1]->get_i() << endl;
        
        // get it out?
        // unique_ptr<Thing> p = v[1]; // error - can't copy assign it
        unique_ptr<Thing> p = std::move(v[1]); // transfer ownership
        cout << "in main scope 4: p points to Thing " << p->get_i() << endl;
        // let's discard p
        p.reset();
         // does v[1] still own anything?
        cout << "in main scope 4: contents of v" << endl;
       for(int i = 0; i < v.size(); i++) {
            if(v[i])
                cout << "v[" << i << "] points to Thing " << v[i]->get_i() << endl;
            else
                cout << "v[" << i << "] points to nothing" << endl;
           }
        // do again with iterators instead
        cout << "in main scope 4: contents of v" << endl;
        for(auto it = v.begin(); it != v.end(); ++it) {
            if(*it)
                cout << "Thing " << (*it)->get_i() << endl;
            else
                cout << "nothing" << endl;
           }
        
        // if we want to get the unique_ptr, we have a problem
        cout << "in main scope 4: contents of v" << endl;
        for(auto it = v.begin(); it != v.end(); ++it) {
        // unique_ptr<Thing> p = *it; // not allowed, no copy assignment;
            unique_ptr<Thing>& p = *it;
        //    unique_ptr<Thing> p = std::move(*it);   // uh - correct, but leaves nothing in the container ....
            if(p)
                cout << "Thing " << p->get_i() << endl;
            else
                cout << "nothing" << endl;
           }
        
        // let's erase the empty unique_ptr from the container - see lecture notes on this idiom
        auto it = v.begin();
        while(it != v.end()) {
            if(!*it)
                it = v.erase(it);
            else
                ++it;
            }
        
        // now what is in the container?
         cout << "in main scope 4: contents of v" << endl;
      for(int i = 0; i < v.size(); i++) {
            if(v[i])
                cout << "v[" << i << "] points to Thing " << v[i]->get_i() << endl;
            else
                cout << "v[" << i << "] points to nothing" << endl;
            }
        


         cout << "Leaving main scope 4" << endl;
    }
    
    // Scope 5 put unique_ptrs in a map
    {
        cout << "\nEntering main scope 5" << endl;
        map<string, unique_ptr<Thing>> m;
        m["Adam"] = create_Thing();
        m["Bob"] = create_Thing();
        m["Carl"] = create_Thing();
        m["Dave"] = create_Thing();
        unique_ptr<Thing> p_load (new Thing);
//        m["Edward"] = p_load;  // error no copy-assign
        m.insert(make_pair("Edward", std::move(p_load)));
         m.insert(make_pair("Edward", unique_ptr<Thing>(new Thing)));
       m["Fred"] = unique_ptr<Thing>(new Thing);  // apparently does a move here.
       
        for(auto it = m.begin(); it != m.end(); ++it) {
            if(it->second)
                cout << it->first << " has pointer to Thing " << it->second->get_i() << endl;
            else
                cout << it->first << " has pointer to nothing" << endl;
            }
        // get rid of one
        m.erase("Carl");
        // empty the pointer at Dave
        m.find("Dave")->second.reset();
        for(auto it = m.begin(); it != m.end(); ++it) {
            if(it->second)
                cout << it->first << " has pointer to Thing " << it->second->get_i() << endl;
            else
                cout << it->first << " has pointer to nothing" << endl;
            }
        // move one out:
        // unique_ptr<Thing> p = m["Bob"]; // error - no copy/assignment
         unique_ptr<Thing> p = move(m["Bob"]);
        // discard it
        p.reset();
        // cout << p->get_i() << endl; // just like a built-in pointer, attempt to use it when null causes crash
        for(auto it = m.begin(); it != m.end(); ++it) {
            if(it->second)
                cout << it->first << " has pointer to Thing " << it->second->get_i() << endl;
            else
                cout << it->first << " has pointer to nothing" << endl;
            }
         cout << "Leaving main scope 5" << endl;
    }
  
	cout << "Done" << endl;
	return 0;
}

/* output:

Entering main scope 1
Thing 1 creation
in create_Thing: p points to Thing 1
in main scope 1: p points to Thing 1
Leaving main scope 1
Thing 1 destruction

Entering main scope 2
Thing 2 creation
in create_Thing: p points to Thing 2
in main scope 2: p points to Thing 2
in refer_to_it: p points to Thing 2
leaving refer_to_it
in main scope 2: p points to Thing 2
Leaving main scope 2
Thing 2 destruction

Entering main scope 3
Thing 3 creation
in create_Thing: p points to Thing 3
in main scope 3: p points to Thing 3
in take_it: p points to Thing 3
leaving take_it
Thing 3 destruction
in main scope 3: p points to nothing
Leaving main scope 3

Entering main scope 4
Thing 4 creation
Thing 5 creation
Thing 6 creation
Thing 7 creation
in main scope 4: v[1] points to Thing 5
in main scope 4: p points to Thing 5
Thing 5 destruction
in main scope 4: contents of v
v[0] points to Thing 4
v[1] points to nothing
v[2] points to Thing 6
v[3] points to Thing 7
in main scope 4: contents of v
Thing 4
nothing
Thing 6
Thing 7
in main scope 4: contents of v
Thing 4
nothing
Thing 6
Thing 7
in main scope 4: contents of v
v[0] points to Thing 4
v[1] points to Thing 6
v[2] points to Thing 7
Leaving main scope 4
Thing 7 destruction
Thing 6 destruction
Thing 4 destruction

Entering main scope 5
Thing 8 creation
in create_Thing: p points to Thing 8
Thing 9 creation
in create_Thing: p points to Thing 9
Thing 10 creation
in create_Thing: p points to Thing 10
Thing 11 creation
in create_Thing: p points to Thing 11
Thing 12 creation
Thing 13 creation
Thing 13 destruction
Thing 14 creation
Adam has pointer to Thing 8
Bob has pointer to Thing 9
Carl has pointer to Thing 10
Dave has pointer to Thing 11
Edward has pointer to Thing 12
Fred has pointer to Thing 14
Thing 10 destruction
Thing 11 destruction
Adam has pointer to Thing 8
Bob has pointer to Thing 9
Dave has pointer to nothing
Edward has pointer to Thing 12
Fred has pointer to Thing 14
Thing 9 destruction
Adam has pointer to Thing 8
Bob has pointer to nothing
Dave has pointer to nothing
Edward has pointer to Thing 12
Fred has pointer to Thing 14
Leaving main scope 5
Thing 8 destruction
Thing 14 destruction
Thing 12 destruction
Done

*/

