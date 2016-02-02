#ifndef SMART_POINTER_H
#define SMART_POINTER_H

/* An intrusive reference-counting Smart_Pointer class template
see R.B. Murray, C++ Strategy and Tactics. Addison-Wesley, 1993.
Modified to resemble tr1::shared_ptr<> in important ways.

Usage:

1. Inherit classes from Reference_Counted_Object

	class My_class : public Reference_Counted_Object {
	// rest of declaration as usual
	};

2. Always allocate objects with new as a Smart_Pointer constructor 
argument.

		Smart_Pointer<const My_class> ptr(new My_class);
		
3. Use Smart_Pointers with the same syntax as built-in pointers;
will convert to Smart_Pointers of another type; can be stored in 
Standard Library Containers. Using the casting functions to
perform standard casts. Assignment from a raw pointer is not allowed
to help prevent programming errors.

4. When the last Smart_Pointer pointing to an object is destructed,
or reset, the pointed-to object will be deleted automatically.

5. Don'ts: 
Never explicitly delete the pointed-to object; reset the Smart_Pointer instead. 
Never attempt to point a Smart_Pointer to a stack object.
Don't use the get() accessor unless absolutely necessary.

6. Don't interfere with the reference counting. This very old and simple design 
unfortunately puts the reference counting functions into the public interface.
Only the Smart_Pointers should be calling these functions. If your own code calls
them, you are violating the design concept and can easily produce undefined behavior.
Don't do it.

The effects of breaking any of these rules is undefined.
*/

/*
Reference_Counted_Objects should only be allocated using new, never the stack.
Smart_Pointers should be the only class that calls the increment and decrement functions.
If the use count hits zero as a result of decrement, the object deletes itself.
The reference count is declared mutable to allow increment/decrement_ref_count
to be declared const, so that a Smart_Pointer can point to a const object. 
This is consistent with the conceptual constness of the object - merely referring
to an object with a Smart_Pointer should not force it to be non-const.
*/
class Reference_Counted_Object {
public:
	Reference_Counted_Object () : ref_count(0)
		{}
	Reference_Counted_Object (const Reference_Counted_Object&) : ref_count(0)
		{}
	virtual ~Reference_Counted_Object()
		{}
	void increment_ref_count() const
		{++ref_count;}
	void decrement_ref_count() const
		// suicidal - destroys this object
		{if (--ref_count == 0) delete this;}
	// Available for testing and debugging purposes only; not normally used.
	long get_ref_count() const
		{return ref_count;}
private:
	mutable long ref_count;	
};

/* Template for Smart_Pointer class
Overloads *, ->, =, ==, and < operators.
Simply increments and decrements the reference count when Smart_Pointers
are initialized, copied, assigned, and destructed.
*/
template <class T> class Smart_Pointer {
public:
	// Constructor with pointer argument - copy and increment_ref_count count
	// Explicit to disallow implicit construction from a raw pointer.
	explicit Smart_Pointer(T* arg = 0) : ptr(arg)
		{if (ptr) ptr->increment_ref_count();}
	// Copy constructor - copy and increment_ref_count
	Smart_Pointer(const Smart_Pointer<T>& other): ptr(other.ptr) 
		{if (ptr) ptr->increment_ref_count();}
	// Templated constructor to support implicit conversions to other Smart_Pointer type
	template <class U> Smart_Pointer(const Smart_Pointer<U> other) : ptr(other.get()) 
		{if (ptr) ptr->increment_ref_count();}
	// Destructor - decrement ref count
	~Smart_Pointer()
		{if (ptr) ptr->decrement_ref_count();}
	// Assignment by copy-swap will decrement lhs, increment rhs
	const Smart_Pointer<T>& operator= (const Smart_Pointer<T>& rhs)
		{
			Smart_Pointer<T> temp(rhs);
			swap(temp);
			return *this;
		}
	// Reset this Smart_Pointer to no longer point to the object.
	// Swap with default-constructed Smart_Pointer will decrement the ref count, 
	// and set the internal pointer to zero.
	void reset()
		{
			Smart_Pointer<T> temp;
			swap(temp);
		}
	// The following functions are const because they do not change
	// the state of this Smart_Pointer object.
	// Access the raw pointer - use this with caution! - avoid if possible
	T* get() const {return ptr;}
	// Overloaded operators
	// Dereference
	T& operator* () const {return *ptr;}
	T* operator-> () const {return ptr;}
	// The following operators make accessing the raw pointer less necessary.
	// Conversion to bool to allow test for pointer non-zero.
	operator bool() const {return ptr;}
	// Smart_Pointers are equal if internal pointers are equal.
	bool operator== (const Smart_Pointer<T>& rhs) const {return ptr == rhs.ptr;}
	bool operator!= (const Smart_Pointer<T>& rhs) const {return ptr != rhs.ptr;}
	// Smart_Pointers are < if internal pointers are <.
	bool operator< (const Smart_Pointer<T>& rhs) const {return ptr < rhs.ptr;}
	// Swap contents with another Smart_Pointer of the same type.
	void swap(Smart_Pointer<T>& other)
		{T* temp_ptr = ptr; ptr = other.ptr; other.ptr = temp_ptr;}
private:
	T* ptr;
};

// Casting functions - simulate casts with raw pointers
// Usage: If ptr is a Smart_Pointer<From_type>
// Smart_Pointer<To_type> = static_Smart_Pointer_cast<To_type>(ptr);
// Smart_Pointer<To_type> = dynamic_Smart_Pointer_cast<To_type>(ptr);
template <typename To_type, typename From_type>
Smart_Pointer<To_type> static_Smart_Pointer_cast(Smart_Pointer<From_type> ptr)
	{return Smart_Pointer<To_type>(static_cast<To_type *>(ptr.get()));}

template <typename To_type, typename From_type>
Smart_Pointer<To_type> dynamic_Smart_Pointer_cast(Smart_Pointer<From_type> ptr)
	{return Smart_Pointer<To_type>(dynamic_cast<To_type *>(ptr.get()));}

#endif
