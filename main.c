#include <stdio.h>
#include <stdint.h>
#include "libs/data_structures/vector/vector.h"

void test_pushBack_emptyVector() {
    vector v = createVector(0);
    pushBack(&v, 1);

    assert(v.size == 1);
}

void test_pushBack_fullVector() {
    vector v = createVector(3);
    v.size = 3;
    pushBack(&v, 1);

    assert(v.size == 4);
    assert(v.capacity == 6);
}

void test_popBack_notEmptyVector() {
    vector v = createVector(3);
    pushBack(&v, 10);
    assert (v.size == 1);

    popBack(&v);
    assert (v.size == 0);
    assert (v.capacity == 3);
}

void test() {
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_notEmptyVector();
}

int main() {
test();
    return 0;
}
