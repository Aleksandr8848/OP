#include <stdio.h>
#include <stdint.h>
#include "libs/data_structures/matrix/matrix.h"

void swapRowsWithMaxAndMinElements(matrix m) {
    position maxPos = getMaxValuePos(m);
    position minPos = getMinValuePos(m);

    swapRows(m, maxPos.rowIndex, minPos.rowIndex);
}

void test_swapRowsWithMaxAndMinElements() {
    matrix m = createMatrixFromArray((int[]) {
            1, 2, 3,
            4, 5, 9,
            6, 7, 8
    }, 3, 3);
    swapRowsWithMaxAndMinElements(m);
    matrix x = createMatrixFromArray((int[]) {
            4, 5, 9,
            6, 7, 8,
            1, 2, 3
    }, 3, 3);

    assert(twoMatricesEqual(m, x));
    freeMemMatrix(m);
    freeMemMatrix(x);
}

int getMax(int *a, int n) {
    int max = a[0];
    for (int i = 0; i < n; ++i) {
        if (a[i] > a[max])
            max = a[i];
    }
    return max;
}

void sortRowsByMinElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}

void test_sortRowsByMinElement(){
    matrix m = createMatrixFromArray((int[]) {
            4, 5, 9,
            6, 7, 8,
            1, 2, 3
    }, 3, 3);

    sortRowsByMinElement(m);
    matrix x = createMatrixFromArray((int[]) {
            1, 2, 3,
            4, 5, 9,
            6, 7, 8
    }, 3, 3);
    assert(twoMatricesEqual(m, x));
    freeMemMatrix(m);
    freeMemMatrix(x);
}

int getMin(int *a, int n){
    int min = a[0];
    for (int i = 0; i < n; ++i) {
        if (a[i] < a[min])
            min = a[i];
    }
    return min;
}
void sortColsByMinElement(matrix m){
    insertionSortColsMatrixByColCriteria(m,getMin);
}
void test_sortColsByMinElement(){
    matrix m = createMatrixFromArray((int[]) {
            4, 5, 9,
            6, 1, 8,
            7, 2, 3
    }, 3, 3);

    sortColsByMinElement(m);
    matrix x = createMatrixFromArray((int[]) {
            5, 9, 4,
            1, 8, 6,
            2, 3, 7
    }, 3, 3);
    assert(twoMatricesEqual(m, x));
    freeMemMatrix(m);
    freeMemMatrix(x);
}

void getSquareOfMatrixIfSymmetric(matrix *m){
    if(!isSymmetricMatrix(*m))
        return;

    matrix res = mulMatrices(*m,*m);
    *m = res;
}

void test_getSquareOfMatrixIfSymmetric(){
    matrix m = createMatrixFromArray((int[]) {
            4, 3, 1,
            3, 1, 2,
            1, 2, 3
    }, 3, 3);

    getSquareOfMatrixIfSymmetric(&m);
    matrix x = createMatrixFromArray((int[]) {
            26, 17, 13,
            17, 14, 11,
            13, 11, 14
    }, 3, 3);
    assert(twoMatricesEqual(m, x));
    freeMemMatrix(m);
    freeMemMatrix(x);
}

void test() {
    test_swapRowsWithMaxAndMinElements;
    test_sortRowsByMinElement;
    test_sortColsByMinElement;
    test_getSquareOfMatrixIfSymmetric;
}

int main() {
    test();
    return 0;
}
