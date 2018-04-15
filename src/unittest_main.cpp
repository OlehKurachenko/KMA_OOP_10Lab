//
// Created by oleh on 4/15/18.
//

#include "Sequence.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    Sequence<int> a;
    a.pushBack(2);
    a.pushBack(4);
    for (size_t i(0); i < a.size(); ++i)
        cout << a[i] << ' ';
    cout << endl;

    Sequence<long long> b(20);
    for (size_t i(0); i < 40; ++i)
        b.pushBack(56 + i);

    assert(b.size() == 40);
    assert(b.requiredCapacity() == 20);

    for (size_t i(0); i < 40; ++i)
        assert(b[i] == 56 + i);

    for (size_t i(0); i < 5; ++i)
        b.removeFront();

    for (size_t i(0); i < 35; ++i)
        assert(b[i] == 56 + i + 5);

    b.setMinCapacity(1000);

    for (size_t i(0); i < 35; ++i)
        assert(b[i] == 56 + i + 5);

    Sequence<bool> t(100);

    assert(t.empty());

    b.clear();

    assert(b.empty());

    assert(b.requiredCapacity() == 1000);

    for (size_t i(0); i < 10; ++i)
        b.pushBack(3);


    for (size_t i(0); i < 20; i += 2)
        b.push(4, i);


    for (size_t i(0); i < 20; ++i)
        assert(b[i] == (i % 2 == 0) ? 4 : 3);

    assert(b.contains(3));
    assert(!b.contains(5));

    for (size_t i(0); i < 10; ++i)
        b.remove(i);

    assert(!b.contains(4));

    try {
        b.remove(100);
    } catch (Sequence<long long>::BadIndex &badIndex){
        cerr << "Exception: " << badIndex._exceptionText << endl;
    }
}
