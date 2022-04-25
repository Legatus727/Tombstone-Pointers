template <typename T>
class MyPointer {
public:
    // default constructor
    MyPointer<T>(); 
    
    // copy constructor
    MyPointer<T>(MyPointer<T>& param) { 
        data = new T;
        *data = param.*data;
    }
    
    // bootstrapping constructor
    // The parameter for the bootstrapping constructor should always be
    // a call to operator new.
    MyPointer<T>(T* param){
        data = new T;
        *data = param; 
    }
    
    // destructor
    ~MyPointer<T>() {
        delete *data;
    } 

    // dereferencing
    T& operator*() const {
        return &data;
    } 

    // field dereferencing
    T* operator->() const {
        return *data;
    } 

    // assignment
    MyPointer<T>& operator=(const MyPointer<T>& param) {
        free this.data;
        this.data = new T;
        this.data = param.*data;
    } 
    
    // delete pointed-at object
    // This is essentially the inverse of the new inside the call to
    // the bootstrapping constructor. It should delete the pointed-to
    // object (which should in turn call its destructor).
    friend void free(MyPointer<T>& param) {
        delete param.data;
    } 
    
    // equality comparisons:
    // true iff MyPointer is null and int is zero
    bool operator==(const MyPointer<T>& param) const {
        return param.*data == NULL;
    }
    bool operator==(const int param) const {
        return param == 0;
    }
    
    // false iff MyPointer is null and int is zero
    bool operator!=(const MyPointer<T>& param) const {
        return param.*data != NULL;
    }
    bool operator!=(const int param) const {
        return param != 0;
    }
    

private:
    T data;
};

template <typename T>
bool operator==(const int n, const MyPointer<T>& t) { return t == n; }

template <typename T>
bool operator!=(const int n, const MyPointer<T>& t) { return t != n; }