#include <stdio.h>
#include <stdint.h>
#include "libs/data_structures/vector/vector.h"
#include "libs/data_structures/matrix/matrix.h"
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

void test_atVector_notEmptyVector() {
    vector v = (vector) {(int[]) {8, 8, 4, 8}, 4, 4};

    assert (*atVector(&v, 2) == 4);
}

void test_atVector_requestToLastElement() {
    vector v = (vector) {(int[]) {1, 2, 3, 4}, 4, 4};

    assert(*atVector(&v, 3) == 4);
}

void test_back_oneElementInVector() {
    vector v = (vector) {(int[]) {1}, 1, 1};
    assert(*back(&v) == 1);
}

void test_front_oneElementInVector() {
    vector v = (vector) {(int[]) {1}, 1, 1};
    assert(*front(&v) == 1);
}

void test() {
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_notEmptyVector();
    test_atVector_notEmptyVector();
    test_atVector_requestToLastElement();
    test_back_oneElementInVector();
    test_front_oneElementInVector();
}

int main() {
    test();
    matrix m = getMemMatrix(3,3);
    inputMatrix(m);
    printf("%d", isSymmetricMatrix(m));
//    swapColumns(m,0,1);
//    outputMatrix(m);
    return 0;
}
