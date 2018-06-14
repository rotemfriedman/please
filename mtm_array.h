#ifndef HW5_MTM_ARRAY_H
#define HW5_MTM_ARRAY_H

#include <utility>
#include <stdexcept>

template <class T, int SIZE>
class Array {
public:
    // TODO: Need to complete interface of iterator classes (x++,++x, ->, operator==, operator!=), as well
    // as that of array itself (operator [], operator [] const, ctor, copy ctor, dtor, operator=),
    // and implement everything.

    explicit Array();     //לבדוק אם צריך להשאיר את האקספליסיט או לא
    Array(const Array& array);
    ~Array();
    Array& operator=(const Array& a);
    T& operator[](int index);
    const T& operator[](int index) const;


class iterator {
    Array *array;
    int index;

    iterator(Array *array, int index);

    friend class Array;

public:
    T &operator*();
    iterator &operator++();
    iterator operator++(int);
    bool operator==(const iterator &iterator) const;
    bool operator!=(const iterator &iterator) const;
    iterator(const iterator &) = default;     //  check if we need default
    iterator &operator=(const iterator &) = default; //  check if we need default
    const T *operator->() const;

};


    class const_iterator {
        const Array* array;
        int index;
        const_iterator(const Array* array, int index);
        friend class Array;

    public:
        Iterator& operator++();
        Iterator operator++(int);
        bool operator==(const iterator& iterator) const;
        bool operator!=(const iterator& iterator) const;
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;
        const T* operator->() const;
        T const& operator*();
    };

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
};



#endif //HW5_MTM_ARRAY_H
