//
// Created by oleh on 4/15/18.
//

#ifndef KMA_OOP_10LAB_SEQUENCE_H
#define KMA_OOP_10LAB_SEQUENCE_H

//Реалізувати параметризований клас необмежених послідовностей на базі масиву. Операції над послідовностями:
//
//Створити порожню послідовність
//        Долучити елемент до кінця послідовності
//Вилучити елемент з початку послідовності
//        Встановити належність елемента до послідовності
//
//
//Корисно користуватися сигнатурою.:
//class Sequence{
//public:
//    class BadSeq;
//
//private:
//    size_t _size;
//    static const size_t _default=0;
//    Array<Elem> * _allocator;
//    void tryToReduce(const size_t times=2);
//    void enlarge(const size_t times=2);
//    Sequence& doinsert(const Elem& elem,const size_t index);
//    Sequence& doremove();
//    Sequence (const Sequence&);
//    Sequence& operator=(const Sequence&);
//};

#include <cstddef>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

template <class T>
class Sequence {
public:
    class BadIndex;

    explicit Sequence(const size_t capacity=defaultCapacity);

    ~Sequence();

    size_t requiredCapacity() const { return _requiredCapacity; }

    size_t size() const { return _lastElement - _firstElement; }

    bool empty() const { return _firstElement == _lastElement; }

    void clear();

    const T &operator[](const size_t index) const;

    T &operator[]( const  size_t index);

    void pushBack(const T &t);

    void removeFront();

    void push(const T &t, const size_t index);

    void remove(const size_t index);

    bool contains(const T &t);

    void setMinCapacity(const size_t minCapacity);

private:
    size_t _size;
    static const size_t defaultCapacity = 1;
    size_t _requiredCapacity;
    size_t _lastElement;
    size_t _firstElement;
    T* _allocator;

    void resize(const size_t size);

    void tryReduce();
};

//  BadIndex

template <class T>
class Sequence<T>::BadIndex {
public:
    BadIndex(const string &exceptionText = "error"):
            _exceptionText(exceptionText) { }
    string _exceptionText;
    //static const string defaultExceptionText = "error";
};

//template <class T>
//ostream& operator<<(ostream& os, const typename Sequence<T>::BadIndex &badIndex) {
//    os << "Sequence: BadIndex: " << badIndex._exceptionText;
//    return os;
//}

//  class Sequence: definitions

template <class T>
Sequence<T>::Sequence(const size_t capacity):
    _size(0),
    _requiredCapacity(capacity),
    _lastElement(0),
    _firstElement(0),
    _allocator(new T[capacity])
{
    if (_requiredCapacity == defaultCapacity)
        _requiredCapacity = 0;
}

template <class T>
Sequence<T>::~Sequence() {
    delete[] _allocator;
}

template<class T>
void Sequence<T>::clear() {
    _firstElement = 0;
    _lastElement = 0;
    if (_requiredCapacity) {
        if (_size != _requiredCapacity)
            resize(_requiredCapacity);
    } else {
        resize(defaultCapacity);
    }

}

template<class T>
const T& Sequence<T>::operator[](const size_t index) const {
    if (index + _firstElement >= _lastElement)
        throw BadIndex("wrong index: " + to_string(index));
    return _allocator[index + _firstElement];
}

template<class T>
T& Sequence<T>::operator[](const size_t index) {
    if (index + _firstElement >= _lastElement)
        throw BadIndex("wrong index: " + to_string(index));
    return _allocator[index + _firstElement];
}

template<class T>
void Sequence<T>::pushBack(const T &t) {
    if (_lastElement == _size)
        resize((_lastElement - _firstElement) * 2 + 3);
    _allocator[_lastElement++] = t;
}

template<class T>
void Sequence<T>::removeFront() {
    ++_firstElement;
    tryReduce();
}

template<class T>
void Sequence<T>::push(const T &t, const size_t index) {
    if (index > (_lastElement - _firstElement))
        throw BadIndex("wrong index: " + to_string(index));
    if (_lastElement == _size)
        resize((_lastElement - _firstElement) * 2 + 3);
    for (size_t i(_lastElement); i > index; --i)
        _allocator[i] = _allocator[i - 1];
    _allocator[index] = t;
    ++_lastElement;
}

template<class T>
void Sequence<T>::remove(const size_t index) {
    if (index >= (_lastElement - _firstElement))
        throw BadIndex("wrong index: " + to_string(index));
    for (size_t i(index); i < _lastElement; ++i)
        _allocator[i] = _allocator[i + 1];
    --_lastElement;
    tryReduce();
}

template<class T>
bool Sequence<T>::contains(const T &t) {
    for (size_t i(_firstElement); i < _lastElement; ++i)
        if (_allocator[i] == t)
            return true;
    return false;
}

template<class T>
void Sequence<T>::setMinCapacity(const size_t minCapacity) {
    _requiredCapacity = minCapacity;
    tryReduce();
    if (minCapacity > _size)
        resize(minCapacity);
}

//  class Sequence: private definitions

template<class T>
void Sequence<T>::tryReduce() {
    if (_size > _requiredCapacity && _size / 2 > _lastElement - _firstElement)
        resize((_requiredCapacity) ? min(((_lastElement - _firstElement) * 2 + 1), _requiredCapacity)
                                   : ((_lastElement - _firstElement) * 2 + 1));
}

template<class T>
void Sequence<T>::resize(const size_t size) {
    T *const newAllocator(new T[size]);
    size_t i(_firstElement), j(0);
    for (; i < _lastElement; ++i, ++j) {
        newAllocator[j] = _allocator[i];
    }
    delete[] _allocator;
    _allocator = newAllocator;
    _firstElement = 0;
    _lastElement = j;
    _size = size;
}

#endif //KMA_OOP_10LAB_SEQUENCE_H
