#pragma once

#include <iostream>

template <typename T>
class Tombstone {
public:
    T* ptr;
    int refCount;
    bool RIP;

    Tombstone<T>() : RIP(false), refCount(1), ptr(NULL) {}
    Tombstone<T>(T* param) : ptr(param), refCount(1), RIP(false) {}
    ~Tombstone<T>() {
        if (ptr != NULL) {
            delete ptr;
            ptr = NULL;
        }
    }
};

template <typename T>
class MyPointer {
private:
    Tombstone<T>* ts;
public:
    // default constructor
    MyPointer<T>() {
        ts = new Tombstone<T>();
    }

    // copy constructor
    MyPointer<T>(MyPointer<T>& param) {
        if (param.ts->RIP) {
            std::cout << "Dangling reference error\n";
            exit(1);
        }
        ts = param.ts;
        ts->refCount++;
    }

    // bootstrapping constructor
    // The parameter for the bootstrapping constructor should always be
    // a call to operator new.
    MyPointer<T>(T* param) {
        ts = new Tombstone<T>(param);
    }

    // destructor
    ~MyPointer<T>() {
        ts->refCount--;
    }

    // dereferencing
    T& operator*() const {
        if (ts->RIP) {
            std::cout << "Dangling reference error\n";
            exit(1);
        }
        return *(ts->ptr);
    }

    // field dereferencing
    T* operator->() const {
        if (ts->RIP) {
            std::cout << "Dangling reference error\n";
            exit(1);
        }
        return ts->ptr;
    }

    // assignment
    MyPointer<T>& operator=(const MyPointer<T>& param) {
        ts = param.ts;
        ts->refCount++;
        return *this;
    }

    // delete pointed-at object
    // This is essentially the inverse of the new inside the call to
    // the bootstrapping constructor. It should delete the pointed-to
    // object (which should in turn call its destructor).
    friend void free(MyPointer<T>& param) {
        if (param.ts != NULL) {
            if (param.ts->ptr != NULL)
            {
                delete param.ts->ptr;
                param.ts->ptr = NULL;
            }
            param.ts->refCount--;
            param.ts->RIP = true;
        }
    }

    // equality comparisons:
    bool operator==(const MyPointer<T>& param) const {
        return ts->ptr == param.ts->ptr;
    }
    bool operator!=(const MyPointer<T>& param) const {
        return ts->ptr != param.ts->ptr;
    }

    // true iff MyPointer is null and int is zero
    bool operator==(const int param) const {
        return  (ts->ptr == NULL && param == 0);
    }

    // false iff MyPointer is null and int is zero
    bool operator!=(const int param) const {
        return (ts->ptr != NULL || param != 0);
    }
};

template <typename T>
bool operator==(const int n, const MyPointer<T>& t) { return t == n; }

template <typename T>
bool operator!=(const int n, const MyPointer<T>& t) { return t != n; }
