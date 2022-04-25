template <typename T>
class MyPointer {
public:
    MyPointer<T>(); // default constructor
    MyPointer<T>(MyPointer<T>&); // copy constructor
    
    MyPointer<T>(T*); // bootstrapping constructor
    // The parameter for the bootstrapping constructor should always be
    // a call to operator new.
    
    ~MyPointer<T>(); // destructor
    T& operator*() const; // dereferencing
    T* operator->() const; // field dereferencing
    MyPointer<T>& operator=(const MyPointer<T>&); // assignment
    
    friend void free(MyPointer<T>&); // delete pointed-at object
    // This is essentially the inverse of the new inside the call to
    // the bootstrapping constructor. It should delete the pointed-to
    // object (which should in turn call its destructor).
    // equality comparisons:
    
    bool operator==(const MyPointer<T>&) const;
    bool operator!=(const MyPointer<T>&) const;
    bool operator==(const int) const;
    // true iff MyPointer is null and int is zero
    
    bool operator!=(const int) const;
    // false iff MyPointer is null and int is zero
};

template <typename T>
bool operator==(const int n, const MyPointer<T>& t) { return t == n; }

template <typename T>
bool operator!=(const int n, const MyPointer<T>& t) { return t != n; }